# -*- coding: utf-8 -*-
from __future__ import annotations
import os, re, json, uuid, csv, traceback, datetime as dt
from pathlib import Path
from typing import Dict, List, Any, Tuple, Union

import pandas as pd
from dotenv import load_dotenv, find_dotenv

# ========== 配置 ==========
IN_XLSX        = r"F:\Knowledge-Augmented-Codegen\ProblemInfoCrawler/data.xlsx"  # Excel 路径
SHEET          = 0                                           # 表索引或名称
OUT_DIR        = "subtasks"                                  # 输出目录
MAX_SUBTASKS   = 4                                           # 子任务上限（建议 1~3）

LINK_COL       = "Link"
DIFF_COL       = "Difficulty"
DESC_COL       = "Description"
INDEX_COL      = "Index"

LANG_COLS = {
    "c": "C",
    "cpp": "C++",
    "java": "Java",
    "javascript": "JavaScript",
    "python": "Python",
}

# LLM 模型
GEMINI_MODEL_FALLBACK     = "gemini-2.5-flash"
GEMINI_TRANSPORT_FALLBACK = "rest"

PROGRESS_STEP = 1

SKIP_IF_JSON_EXISTS = True
# ==========================

# ---- LLM（Gemini） ----
try:
    import google.generativeai as genai
except Exception:
    genai = None

# ---- 受控词 ----
from controlled_vocab import (
    validate_structures_actions,
    ALLOWED_STRUCTURES, ALLOWED_ACTIONS
)

# ========== 环境 ==========
def _load_env_robust():
    ok = load_dotenv(find_dotenv(usecwd=True), override=True)   # 先尝试从 cwd
    if not ok:                                                 # 再从模块目录
        mod_env = Path(__file__).resolve().parent / ".env"
        if mod_env.exists():
            ok = load_dotenv(mod_env, override=True)
    if not ok:                                                 # 最后再全局找
        load_dotenv(find_dotenv(), override=True)

from pathlib import Path as _P
_load_env_robust()

API_KEY    = os.getenv("GEMINI_API_KEY")
if not API_KEY:
    raise RuntimeError("GEMINI_API_KEY missing in .env or environment")

TRANSPORT  = os.getenv("GEMINI_TRANSPORT", GEMINI_TRANSPORT_FALLBACK)
MODEL_NAME = os.getenv("GEMINI_MODEL", GEMINI_MODEL_FALLBACK)

if not genai:
    raise RuntimeError("google-generativeai not installed. Run: pip install google-generativeai")

genai.configure(api_key=API_KEY, transport=TRANSPORT)

# ========== 工具 ==========
def to_slug(link_or_text: str) -> str:
    s = (link_or_text or "").strip().lower()
    m = re.search(r"/problems/([^/]+)/?", s)
    if m: return m.group(1)
    slug = re.sub(r"[^a-z0-9\-]+", "-", s)[:80].strip("-")
    return slug or ("problem-" + uuid.uuid4().hex[:8])

def split_desc(desc: str) -> Tuple[str, str, str]:
    text = desc or ""
    ex_iter = list(re.finditer(
        r"(?:^|\n)\s*Example\s*\d*\s*:\s*(.*?)(?=(?:\n\s*Example\s*\d*\s*:)|(?:\n\s*Constraints\s*:)|\Z)",
        text, flags=re.S|re.I
    ))
    ex_full = ex_iter[0].group(0) if ex_iter else ""
    ex_body = re.sub(r"^\s*Example\s*\d*\s*:\s*", "", ex_full, flags=re.I).strip() if ex_full else ""

    cons_m = re.search(r"(?:^|\n)\s*Constraints\s*:\s*(.*)$", text, flags=re.S|re.I)
    cons_full = cons_m.group(0) if cons_m else ""
    cons_body = re.sub(r"^\s*Constraints\s*:\s*", "", cons_full, flags=re.I).strip() if cons_full else ""

    main = text
    if cons_full: main = main.replace(cons_full, "")
    for m in ex_iter: main = main.replace(m.group(0), "")
    return main.strip(), ex_body, cons_body

def _norm_kebab(s: str) -> str:
    return re.sub(r"[^a-z0-9]+","-", str(s).lower()).strip("-")

def _json_has_subtasks(fp: Path) -> bool:
    try:
        obj = json.loads(fp.read_text(encoding="utf-8"))
        sts = obj.get("subtasks") or []
        return isinstance(sts, list) and len(sts) > 0
    except Exception:
        return False

# ========== Prompt ==========
def build_prompt_for_decomposition(problem_desc: str, max_subtasks: int) -> str:
    structures_list = ", ".join(sorted(ALLOWED_STRUCTURES))
    actions_list = ", ".join(sorted(ALLOWED_ACTIONS))
    return (
        f"You are an algorithmic task planner. Decompose the coding problem into as FEW subtasks as necessary (between 1 and {max_subtasks}).\n"
        "Each subtask must be directly actionable.\n"
        "Output ONLY JSON (no markdown, no commentary) with this schema:\n"
        "{\n"
        '  "subtasks":[\n'
        "    {\n"
        '      "intent":"string(max 160 chars)",\n'
        '      "structures":["string"],  // choose ONLY from: [' + structures_list + ']\n'
        '      "actions":["string"],     // choose ONLY from: [' + actions_list + ']\n'
        '      "cues":["string"],\n'
        '      "constraints":["string"]\n'
        "    }\n"
        "  ]\n"
        "}\n"
        "Rules:\n"
        "- structures/actions MUST be chosen from the allowed lists above (kebab-case);\n"
        "- provide at least ONE structure AND ONE action per subtask;\n"
        "- cues are short triggers from the statement; constraints are short hard requirements;\n"
        "- no explanations or code.\n\n"
        "PROBLEM:\n" + problem_desc.strip()[:3500]
    )

def _autofill_when_empty(st: dict, desc: str) -> dict:
    """若校验后 structures/actions 为空，则按题面/线索轻量填一个受控组合。"""
    s = list(st.get("structures") or [])
    a = list(st.get("actions") or [])
    txt = (desc + " " + " ".join(st.get("cues") or [])).lower()

    if not s:
        if "heap" in txt or "global min" in txt or "k-way" in txt or "merge" in txt:
            s.append("heap")
        elif "tree" in txt:
            s.append("tree")
        elif "graph" in txt:
            s.append("graph")
        else:
            s.append("array")

    if not a:
        if "kth" in txt or "global min" in txt or "heap" in txt or "k-way" in txt or "merge" in txt:
            a.append("heap-select")
        elif "two pointer" in txt or "pointer" in txt:
            a.append("two-pointers")
        elif "binary search" in txt:
            a.append("binary-search")
        elif "dp" in txt or "dynamic programming" in txt or "sequence" in txt or "iteratively construct" in txt:
            a.append("dp-1d")
        else:
            a.append("dp-1d")

    st["structures"] = s
    st["actions"] = a
    return st

def gen_subtasks_with_gemini_strict(desc: str, max_subtasks: int) -> List[Dict[str, Any]]:
    schema = {
        "type": "object",
        "properties": {
            "subtasks": {
                "type": "array",
                "items": {
                    "type": "object",
                    "properties": {
                        "intent": {"type": "string", "maxLength": 160},
                        "structures": {
                            "type": "array",
                            "items": {"type": "string", "enum": sorted(list(ALLOWED_STRUCTURES))},
                            "minItems": 1, "maxItems": 3
                        },
                        "actions": {
                            "type": "array",
                            "items": {"type": "string", "enum": sorted(list(ALLOWED_ACTIONS))},
                            "minItems": 1, "maxItems": 3
                        },
                        "cues":       {"type": "array", "items": {"type": "string"}, "maxItems": 10},
                        "constraints":{"type": "array", "items": {"type": "string"}, "maxItems": 10}
                    },
                    "required": ["intent","structures","actions","cues","constraints"],
                    "additionalProperties": False
                },
                "minItems": 1,
                "maxItems": max(1, max_subtasks)
            }
        },
        "required": ["subtasks"],
        "additionalProperties": False
    }

    def _make_model(use_schema: bool):
        if use_schema:
            return genai.GenerativeModel(
                MODEL_NAME,
                generation_config={
                    "response_mime_type": "application/json",
                    "response_schema": schema,
                }
            )
        return genai.GenerativeModel(MODEL_NAME)

    def _read_text_and_finish_reason(resp):
        text = getattr(resp, "text", None)
        if not text:
            cand0 = (getattr(resp, "candidates", None) or [None])[0]
            if cand0 and getattr(cand0, "content", None) and getattr(cand0.content, "parts", None):
                text = "".join(getattr(p, "text", "") for p in cand0.content.parts if hasattr(p, "text"))
        fr = None
        if getattr(resp, "candidates", None):
            fr = getattr(resp.candidates[0], "finish_reason", None)
        return (text or "").strip(), fr

    def _one_call(model, problem_txt: str, max_tokens: int) -> Dict[str, Any]:
        prompt = build_prompt_for_decomposition(problem_txt, max_subtasks=max_subtasks)
        resp = model.generate_content(
            prompt,
            generation_config={
                "temperature": 0.2,
                "max_output_tokens": max_tokens,
                "candidate_count": 1,
            }
        )
        text, fr = _read_text_and_finish_reason(resp)
        if not text:
            raise RuntimeError(f"empty_response_or_no_parts: finish_reason={fr}")

        try:
            return json.loads(text)
        except Exception:
            s, e = text.find("{"), text.rfind("}")
            if s != -1 and e != -1 and e > s:
                return json.loads(text[s:e+1])
            raise RuntimeError(f"no_json_found: preview={text[:160].replace(chr(10),' ')}; finish_reason={fr}")

    stages = [
        {"use_schema": True,  "desc": desc[:3200], "tokens": 4096},
        {"use_schema": False, "desc": desc[:1800], "tokens": 6144},
        {"use_schema": False, "desc": desc[:1000], "tokens": 8192},
    ]
    last_err = None
    for st in stages:
        try:
            model = _make_model(st["use_schema"])
            js = _one_call(model, st["desc"], st["tokens"])
            sts = js.get("subtasks") or []
            out: List[Dict[str, Any]] = []
            for it in sts[:max_subtasks]:
                intent = str(it.get("intent","")).strip()[:200]
                structures = [str(x) for x in (it.get("structures") or [])][:6]
                actions    = [str(x) for x in (it.get("actions") or [])][:8]
                cues       = [str(x) for x in (it.get("cues") or [])][:10]
                cons       = [str(x) for x in (it.get("constraints") or [])][:10]
                v = validate_structures_actions(structures, actions)
                st_fixed = {
                    "intent": intent,
                    "structures": v.get("structures", []),
                    "actions":    v.get("action", []),
                    "cues":       [_norm_kebab(x) for x in cues if str(x).strip()][:10],
                    "constraints":[_norm_kebab(x) for x in cons if str(x).strip()][:10],
                }
                if not st_fixed["structures"] or not st_fixed["actions"]:
                    st_fixed = _autofill_when_empty(st_fixed, desc)
                out.append(st_fixed)
            if not out:
                raise RuntimeError("empty_subtasks_after_parse")
            return out
        except Exception as e:
            last_err = e
            continue
    raise RuntimeError(f"gemini_strict_failed: {last_err}")

# ========== Excel 读取 ==========
def iter_rows_from_excel(xlsx: str, sheet: Union[int,str],
                         link_col="Link", diff_col="Difficulty", desc_col="Description", index_col="Index",
                         lang_cols=None):
    df = pd.read_excel(xlsx, sheet_name=sheet)
    df.rename(columns=lambda x: str(x).strip(), inplace=True)
    lang_cols = lang_cols or {"c":"C", "cpp":"C++", "java":"Java", "javascript":"JavaScript", "python":"Python"}
    for _, r in df.iterrows():
        desc = str(r.get(desc_col, "") or "")
        if not desc.strip():
            continue
        yield {
            "link": str(r.get(link_col,"") or ""),
            "difficulty": str(r.get(diff_col,"") or ""),
            "description": desc,
            "index": str(r.get(index_col, "") or ""),
            "templates": {k: str(r.get(v,"") or "") for k,v in lang_cols.items() if str(r.get(v,"") or "").strip()}
        }

# ========== 主流程 ==========
def main():
    outd = Path(OUT_DIR); outd.mkdir(parents=True, exist_ok=True)
    log_fp = (outd / "_run.log").open("a", encoding="utf-8")
    report_path = outd / "_run_report.csv"
    manifest_fp = (outd / "_manifest.jsonl").open("w", encoding="utf-8")

    def log(line: str):
        ts = dt.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        msg = f"[{ts}] {line}"; print(msg); log_fp.write(msg + "\n"); log_fp.flush()

    if not Path(IN_XLSX).exists():
        raise FileNotFoundError(f"Excel 文件不存在：{IN_XLSX}")

    df = pd.read_excel(IN_XLSX, sheet_name=SHEET)
    df.rename(columns=lambda x: str(x).strip(), inplace=True)
    total = len(df)

    with report_path.open("w", newline="", encoding="utf-8") as fcsv:
        writer = csv.writer(fcsv)
        writer.writerow(["row_idx","index","slug","difficulty","link","status","error","subtask_count","model"])

        done = 0
        for i, r in df.iterrows():
            desc = str(r.get(DESC_COL, "") or "")
            if not desc.strip():
                continue
            link = str(r.get(LINK_COL, "") or "")
            difficulty = str(r.get(DIFF_COL, "") or "")
            index_val = str(r.get(INDEX_COL, "") or "")
            templates = {k: str(r.get(v,"") or "") for k,v in LANG_COLS.items() if str(r.get(v,"") or "").strip()}
            slug = to_slug(link if link else desc[:64])

            json_fp = outd / f"{slug}.json"
            if SKIP_IF_JSON_EXISTS and json_fp.exists() and _json_has_subtasks(json_fp):
                writer.writerow([i, index_val, slug, difficulty, link, "skip-exists", "", 0, MODEL_NAME])
                log(f"[{done}/{total}] ⏭ {slug}  skip-exists")
                continue

            try:
                main_text, example_text, constraints_text = split_desc(desc)
                subtasks = gen_subtasks_with_gemini_strict(desc, max_subtasks=MAX_SUBTASKS)

                obj = {
                    "slug": slug,
                    "link": link,
                    "difficulty": difficulty,
                    "index": index_val,
                    "description_full": desc,
                    "description": main_text,
                    "example": example_text,
                    "constraints_text": constraints_text,
                    "templates": templates,
                    "subtasks": subtasks
                }
                (outd / f"{slug}.json").write_text(json.dumps(obj, ensure_ascii=False, indent=2), encoding="utf-8")
                manifest_fp.write(json.dumps({"slug": slug, "difficulty": difficulty, "index": index_val, "link": link}, ensure_ascii=False) + "\n")

                writer.writerow([i, index_val, slug, difficulty, link, "ok", "", len(subtasks), MODEL_NAME])
                done += 1
                if done % PROGRESS_STEP == 0:
                    log(f"[{done}/{total}] ✅ {slug}  source=gemini  subtasks={len(subtasks)}")

            except Exception as e:
                err_text = f"{type(e).__name__}: {e}"
                writer.writerow([i, index_val, slug, difficulty, link, "fail", err_text, 0, MODEL_NAME])
                log(f"[{done+1}/{total}] ❌ {slug}  {err_text}")
                log(traceback.format_exc())

    manifest_fp.close(); log_fp.close()
    print(f"\n📄 Manifest : {outd/'_manifest.jsonl'}")
    print(f"📑 Report   : {report_path}")
    print(f"🗒️ Log      : {outd/'/_run.log'}")

if __name__ == "__main__":
    main()
