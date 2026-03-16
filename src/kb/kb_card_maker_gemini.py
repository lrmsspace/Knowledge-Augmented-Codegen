# 知识卡生成

import os
import re
import json
import time
import random
from typing import Dict, Any, List

import requests
from requests.adapters import HTTPAdapter
from urllib3.util.retry import Retry
from dotenv import load_dotenv; load_dotenv()

from controlled_vocab import validate_structures_actions, ALLOWED_STRUCTURES, ALLOWED_ACTIONS

# ============ 配置 ============
SEGMENTS_PATH = r"F:\Knowledge-Augmented-Codegen\knowledge_base/segments.jsonl"
CARDS_PATH    = r"F:\Knowledge-Augmented-Codegen\knowledge_base/cards.jsonl"

MODEL_NAME    = "models/gemini-2.5-flash"
API_BASE      = "https://generativelanguage.googleapis.com/v1beta"
GEN_URL       = f"{API_BASE}/{MODEL_NAME}:generateContent"

MAX_OUTPUT_TOKENS = 8192
TIMEOUT_S         = 120        # 请求超时
MAX_RETRY         = 5          # 业务层重试次数
BACKOFF_BASE      = 2.0

SLEEP_BETWEEN     = 3
SRC_MAX_TOKENS    = 4800       # 最大词数

# 生成项长度约束
WTU_MAX_WORDS     = 40
WTU_MAX_SENTENCES = 2
DESC_MAX_SENTENCES= 3
INV_MIN, INV_MAX  = 2, 4
SIG_MIN, SIG_MAX  = 6, 15
TIPS_MIN, TIPS_MAX = 3, 6
PITS_MIN, PITS_MAX = 3, 6

SESSION = requests.Session()
RETRY = Retry(
    total=3,
    backoff_factor=1.2,
    status_forcelist=[429, 500, 502, 503, 504],
    allowed_methods=["POST"],
    raise_on_status=False,
)
SESSION.mount("https://", HTTPAdapter(max_retries=RETRY))

def log(msg: str):
    print(time.strftime("[%H:%M:%S]"), msg, flush=True)

CARD_SCHEMA = {
  "type": "object",
  "properties": {
    "id": {"type": "string"},
    "title": {"type": "string"},
    "structures": {"type": "array", "items": {"type": "string"}},
    "action": {"type": "array", "items": {"type": "string"}},

    "signals": {"type": "array", "items": {"type": "string"}, "minItems": SIG_MIN, "maxItems": SIG_MAX},
    "when_to_use": {"type": "string"},
    "description": {"type": "string"},
    "tips": {"type": "array", "items": {"type": "string"}, "minItems": TIPS_MIN, "maxItems": TIPS_MAX},
    "pitfalls": {"type": "array", "items": {"type": "string"}, "minItems": PITS_MIN, "maxItems": PITS_MAX},

    "level": {"type": "string", "enum": ["basic","standard","advanced"]},
    "min_required_signals": {"type": "integer"},

    "assumption": {
      "type": "object",
      "properties": {
        "index_base": {"type": "string", "enum": ["0","1","any"]},
        "requires_sorted_input": {"type": "boolean"},
        "mutates_input": {"type": "boolean"},
        "memory_ownership": {"type": "string", "enum": ["caller","callee","global","any"]},
        "graph_weight_type": {"type": "string", "enum": ["unweighted","01","non-negative","any"]},
        "recursion_depth_sensitive": {"type": "boolean"},
        "language_dependency": {"type": "string"},
        "other": {"type": "array", "items": {"type": "string"}}
      },
      "required": ["index_base","requires_sorted_input","mutates_input","memory_ownership",
                   "graph_weight_type","recursion_depth_sensitive","language_dependency","other"]
    },

    "invariants": {"type": "array", "items": {"type": "string"}, "minItems": INV_MIN, "maxItems": INV_MAX}
  },
  "required": [
    "id","title","structures","action",
    "signals","when_to_use","description","tips","pitfalls",
    "level","min_required_signals","assumption","invariants"
  ]
}

ASSUMPTION_DEFAULT = {
    "index_base": "any",
    "requires_sorted_input": False,
    "mutates_input": False,
    "memory_ownership": "any",
    "graph_weight_type": "any",
    "recursion_depth_sensitive": False,
    "language_dependency": "any",
    "other": []
}

SYSTEM_PROMPT = f"""
You are an "Algorithm Knowledge Card Generator". Output JSON ONLY for RAG retrieval and guarded code generation.

Hard constraints:
- DO NOT modify LOCKED fields: id, title, structures, action.
- English only; no specific problem titles/platforms/sample I/O/code.
- signals: {SIG_MIN}–{SIG_MAX} short phrases; tips/pitfalls: {TIPS_MIN}–{TIPS_MAX} each.
- when_to_use: 1–2 short sentences; target ≤{WTU_MAX_WORDS} words (whitespace-based).
- description: 1–2 short sentences (core idea + complexity class), no code.
- invariants: {INV_MIN}–{INV_MAX} loop/structure invariants (one per line, testable, not duplicated with tips/pitfalls).

level (implementation complexity; NOT problem difficulty):
- basic: linear scan / single pass / simple containers (prefix-sum, two-pointers, sliding-window)
- standard: templated patterns / light structures (binary-search, merge-intervals, bfs, topo, union-find, heap-select, lis via greedy/binary-search)
- advanced: heavy structures / multi-component (bit-fenwick, segment-tree, kmp, 01-bfs with details, multi-dim/optimized knapsack)
If multiple actions map to different levels, choose the higher one; if unsure, pick the most common practice.

min_required_signals (activation threshold):
- First categorize signals by specificity: rare (strongly specific, e.g., "monotonic stack", "KMP"), medium (generic but informative), common (broad words like "array", "subarray", "sum").
- Map to threshold: rare→1, medium→2, common→3.
- Final threshold = the SECOND-SMALLEST of the three values (robust to a single rare hit).
- Output ONLY the final integer (do NOT output the categorized lists).

assumption (formal preconditions/default contracts; use defaults unless the text explicitly states otherwise):
{json.dumps(ASSUMPTION_DEFAULT, ensure_ascii=False)}

Return exactly ONE JSON object with fields in this exact order:
id, title, structures, action, signals, when_to_use, description, tips, pitfalls,
level, min_required_signals, assumption, invariants

Controlled vocabulary:
- structures: {", ".join(sorted(ALLOWED_STRUCTURES))}
- action: {", ".join(sorted(ALLOWED_ACTIONS))}
""".strip()

def build_user_prompt(seg: Dict[str, Any]) -> str:
    card_id = f"{int(seg['doc_id'])}_{int(seg.get('seg_id') or 0)}"
    src = (seg.get("text") or "").strip()
    toks = re.split(r"\s+", src)
    if len(toks) > SRC_MAX_TOKENS:
        src = " ".join(toks[:SRC_MAX_TOKENS])

    provided_structs = ", ".join(seg["structures"])
    provided_actions = ", ".join(seg["action"])

    return f"""
LOCKED:
- id = {card_id}
- title = {seg['doc_title']}
- structures = [{provided_structs}]
- action = [{provided_actions}]

SOURCE_EXCERPT (clean prose, textbook/blog fragment allowed):
{src}

TASK:
Produce exactly ONE JSON object. Field order must be:
id, title, structures, action, signals, when_to_use, description, tips, pitfalls,
level, min_required_signals, assumption, invariants
""".strip()

# ============ I/O ============
def read_jsonl(path: str) -> List[Dict[str, Any]]:
    rows=[]
    if not os.path.exists(path): return rows
    with open(path, "r", encoding="utf-8", errors="ignore") as f:
        for line in f:
            s=line.strip()
            if not s: continue
            try:
                rows.append(json.loads(s))
            except Exception:
                pass
    return rows

def write_jsonl(path: str, rows: List[Dict[str, Any]]):
    d=os.path.dirname(path)
    if d and not os.path.exists(d): os.makedirs(d, exist_ok=True)
    with open(path, "a", encoding="utf-8") as f:
        for r in rows:
            f.write(json.dumps(r, ensure_ascii=False) + "\n")

# ============ 校验 ============
def count_sentences_rough(s: str) -> int:
    if not isinstance(s, str) or not s.strip(): return 0
    return len(re.findall(r"[。．.!?！？]+", s)) or 1

def post_validate(card: Dict[str, Any],
                  locked_structs: List[str], locked_actions: List[str]) -> List[str]:
    errs=[]

    if not isinstance(card.get("id"), str) or not re.fullmatch(r"\d+_\d+", card["id"]):
        errs.append("id must be 'docId_segId' string")
    if not isinstance(card.get("title"), str):
        errs.append("title must be string")

    if card.get("structures") != locked_structs:
        errs.append("structures must equal provided tokens"); card["structures"]=locked_structs[:]
    if card.get("action") != locked_actions:
        errs.append("action must equal provided tokens"); card["action"]=locked_actions[:]
    chk = validate_structures_actions(card.get("structures", []), card.get("action", []))
    if not chk["ok"]:
        errs.append("structures/action not in allowed vocab")

    for k, lo, hi in (("signals",SIG_MIN,SIG_MAX),
                      ("tips",TIPS_MIN,TIPS_MAX),
                      ("pitfalls",PITS_MIN,PITS_MAX),
                      ("invariants",INV_MIN,INV_MAX)):
        arr = card.get(k)
        if not isinstance(arr, list) or not all(isinstance(x,str) and x.strip() for x in arr):
            errs.append(f"{k} must be array of non-empty strings")
        else:
            if not (lo <= len(arr) <= hi):
                errs.append(f"{k} length {len(arr)} not in [{lo},{hi}]")

    wtu = card.get("when_to_use","")
    if not isinstance(wtu, str) or not wtu.strip():
        errs.append("when_to_use must be non-empty")
    else:
        if len(wtu.split()) > WTU_MAX_WORDS:
            errs.append("when_to_use too long")
        if count_sentences_rough(wtu) > WTU_MAX_SENTENCES:
            errs.append("when_to_use too many sentences")

    desc = card.get("description","")
    if not isinstance(desc, str) or not desc.strip():
        errs.append("description must be non-empty")
    else:
        if count_sentences_rough(desc) > DESC_MAX_SENTENCES:
            errs.append("description too many sentences")

    if card.get("level") not in ("basic","standard","advanced"):
        errs.append("level invalid")
    if card.get("min_required_signals") not in (1,2,3):
        errs.append("min_required_signals invalid")

    ass = card.get("assumption", {})
    if not isinstance(ass, dict):
        ass = {}
    merged = {**ASSUMPTION_DEFAULT, **ass}
    card["assumption"] = merged

    def dedup_str_list(xs: List[str]) -> List[str]:
        seen=set(); out=[]
        for s in xs:
            s2=(s or "").strip()
            if not s2: continue
            if s2 in seen: continue
            seen.add(s2); out.append(s2)
        return out

    for k in ("signals","tips","pitfalls","invariants"):
        if isinstance(card.get(k), list):
            card[k] = dedup_str_list(card[k])

    return errs

# ============ 调用生成接口 ============
def request_gemini_json(prompt_text: str, schema: dict) -> dict:
    """调用 Gemini 接口"""
    api_key = os.getenv("GEMINI_API_KEY") or ""
    assert api_key, "请设置 GEMINI_API_KEY 环境变量"

    payload = {
        "contents": [{"role": "user", "parts": [{"text": prompt_text}]}],
        "systemInstruction": {"role": "system", "parts": [{"text": SYSTEM_PROMPT}]} ,
        "generationConfig": {
            "temperature": 0.2,
            "topP": 0.9,
            "maxOutputTokens": MAX_OUTPUT_TOKENS,
            "responseMimeType": "application/json",
            "responseSchema": schema
        }
    }
    params = {"key": api_key}

    for k in range(1, MAX_RETRY+1):
        try:
            t0 = time.time()
            r = SESSION.post(GEN_URL, params=params, json=payload, timeout=TIMEOUT_S)
            dt = time.time() - t0
            log(f"  http {r.status_code} in {dt:.1f}s")
            if r.status_code == 400:
                # 400 多为 schema 或字段问题，打印片段便于定位
                try:
                    log(f"  server says 400 body: {r.text[:800]}")
                except Exception:
                    pass
            if r.status_code >= 500:
                raise RuntimeError(f"server {r.status_code}")
            r.raise_for_status()

            data = r.json()
            cand = (data.get("candidates") or [{}])[0]
            parts = ((cand.get("content") or {}).get("parts")) or []
            if parts and "text" in parts[0]:
                return json.loads(parts[0]["text"])

            txt = parts[0].get("text","") if parts else ""
            m = re.search(r"\{.*\}\s*$", txt, re.S)
            if m:
                return json.loads(m.group(0))
            raise ValueError(f"no JSON text; finishReason={cand.get('finishReason')}")
        except Exception as e:
            if k == MAX_RETRY:
                log(f"  !! give up: {e!r}")
                raise
            backoff = BACKOFF_BASE * (2 ** (k-1)) + random.uniform(0, 0.8)
            log(f"  warn: {e!r} -> retry {k}/{MAX_RETRY} after {backoff:.1f}s")
            time.sleep(backoff)

def build_fix_prompt(bad_card: Dict[str, Any], errors: List[str],
                     locked_structs: List[str], locked_actions: List[str]) -> str:
    """构造修复提示"""
    return f"""
Your previous JSON violated constraints. Fix with MINIMAL edits.
DO NOT change LOCKED fields: id/title/structures/action.
Keep the same schema and field order; return JSON only.
Errors: {errors}
LOCKED structures: {locked_structs}
LOCKED action: {locked_actions}
""".strip()

# ============ 主流程 ============
def generate_card_for_segment(seg: Dict[str, Any]) -> Dict[str, Any]:
    prompt = build_user_prompt(seg)
    card = request_gemini_json(prompt, CARD_SCHEMA)

    card["id"] = f"{int(seg['doc_id'])}_{int(seg.get('seg_id') or 0)}"
    card["title"] = seg["doc_title"]
    locked_structs = seg["structures"]
    locked_actions = seg["action"]
    card["structures"] = locked_structs[:]
    card["action"] = locked_actions[:]

    errs = post_validate(card, locked_structs, locked_actions)
    if errs:
        log(f"  post-validate errors: {errs}")
        fix_prompt = build_fix_prompt(card, errs, locked_structs, locked_actions)
        fixed = request_gemini_json(fix_prompt, CARD_SCHEMA)
        fixed["id"] = card["id"]; fixed["title"] = card["title"]
        fixed["structures"] = locked_structs[:]; fixed["action"] = locked_actions[:]
        errs2 = post_validate(fixed, locked_structs, locked_actions)
        if errs2:
            log(f"  fix still has errors (keep original): {errs2}")
            return card
        return fixed

    return card

def main():
    """批量读取分段并生成卡片，支持断点续跑"""
    done_ids = set()
    if os.path.exists(CARDS_PATH):
        for obj in read_jsonl(CARDS_PATH):
            cid = obj.get("id")
            if isinstance(cid, str): done_ids.add(cid)

    segs = read_jsonl(SEGMENTS_PATH)
    if not segs:
        raise RuntimeError(f"No segments found at {SEGMENTS_PATH}")

    log(f"Loaded {len(segs)} segments; done_ids={len(done_ids)}; start building cards ...")

    written = 0
    for i, seg in enumerate(segs, 1):
        seg["doc_id"] = int(seg["doc_id"])
        seg["seg_id"] = int(seg.get("seg_id") or 0)
        card_id = f"{seg['doc_id']}_{seg['seg_id']}"

        if card_id in done_ids:
            log(f"[{i}/{len(segs)}] skip {card_id} (already exists)")
            continue

        title = seg.get("doc_title","")
        log(f"[{i}/{len(segs)}] start {card_id} — {title[:80]!r}")

        try:
            card = generate_card_for_segment(seg)
            write_jsonl(CARDS_PATH, [card])
            written += 1
            log(f"[{i}/{len(segs)}] ok -> wrote {card_id}")
        except Exception as e:
            log(f"[{i}/{len(segs)}] FAIL {card_id}: {e!r}")

        time.sleep(SLEEP_BETWEEN)

    log(f"Done. Wrote {written} new card(s) -> {CARDS_PATH}")

if __name__ == "__main__":
    main()
