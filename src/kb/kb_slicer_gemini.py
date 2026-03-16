import os
import re
import json
import time
import argparse
from typing import List, Dict, Any, Tuple

import requests
import pandas as pd

from controlled_vocab import ALLOWED_STRUCTURES, ALLOWED_ACTIONS, validate_structures_actions
from dotenv import load_dotenv; load_dotenv()  # 自动读取 .env

# ----------------- config -----------------
INPUT_PATH   = r"F:\Knowledge-Augmented-Codegen\knowledge_base/cp_algorithms.xlsx"
SHEET_NAME   = "Sheet1"
ID_COL       = "id"
TITLE_COL    = "title"
CONTENT_COL  = "content"

MODEL_NAME   = "models/gemini-2.5-flash"
OUT_PLAN     = r"F:\Knowledge-Augmented-Codegen\knowledge_base/plans.jsonl"
OUT_SEGMENTS = r"F:\Knowledge-Augmented-Codegen\knowledge_base/segments.jsonl"
MAX_ROWS     = 0
SLEEP_S      = 0.0
APPEND_MODE  = False

HARDCODED_API_KEY = ""

# ====== JSON Schema（让模型结构化输出）======
SEGMENTATION_SCHEMA = {
  "type": "object",
  "properties": {
    "doc_title": {"type": "string"},
    "segments": {
      "type": "array",
      "items": {
        "type": "object",
        "properties": {
          "seg_id": {"type": "integer"},
          "spans": {
            "type": "array",
            "items": {
              "type": "object",
              "properties": {
                "start": {"type": "integer"},
                "end":   {"type": "integer"}
              },
              "required": ["start","end"]
            }
          },
          "keep": {"type": "boolean"},
          "structures": {"type": "array", "items": {"type": "string"}},
          "action": {"type": "array", "items": {"type": "string"}},
          "title_suggestion": {"type": "string"},
          "reason": {"type": "string"}
        },
        "required": ["seg_id","spans","keep","structures","action"]
      }
    }
  },
  "required": ["doc_title","segments"]
}

SYSTEM_PROMPT = f"""
You segment long algorithm articles into reusable knowledge segments for a coding knowledge base.

Card-worthiness rule: a segment is “card-worthy” only if it includes
(1) when-to-use / preconditions,
(2) core idea / invariants / main loop,
(3) efficiency / complexity hints (e.g., O-notation or 'sort-dominant').

Segments may MERGE non-adjacent spans if they belong to the same technique variant.
Use ONLY the allowed vocab:
- structures (≤2): {", ".join(sorted(ALLOWED_STRUCTURES))}
- action (1–3): {", ".join(sorted(ALLOWED_ACTIONS))}

Return JSON only, complying with the provided JSON schema.
No code, no I/O examples, no problem titles or online-judge names.
""".strip()

def build_user_prompt(title: str, full_text: str) -> str:
    return f"""DOC_TITLE: {title}
FULL_TEXT_LENGTH: {len(full_text)}
FULL_TEXT (cleaned, no code blocks, no I/O examples):
{full_text}

TASK:
1) Decide how many segments to produce (typically 1–4) that meet the card-worthiness rule.
2) For each segment, output: seg_id, spans=[{{start,end}}...], keep (true/false),
   structures (≤2), action (1–3), title_suggestion, reason (≤30 words).
3) Merge across boundaries when needed to keep one technique together.
4) Mark keep=false for pure background/proofs/applications.

Return JSON with keys: doc_title, segments[]. Nothing else.
""".strip()

# --------- 日志、写文件、读表 ---------
def log(msg: str):
    print(time.strftime("[%H:%M:%S] "), msg, flush=True)

def write_jsonl(path: str, rows: List[Dict[str, Any]], append: bool):
    d = os.path.dirname(path)
    if d and not os.path.exists(d):
        os.makedirs(d, exist_ok=True)
    mode = "a" if append else "w"
    with open(path, mode, encoding="utf-8") as f:
        for r in rows:
            f.write(json.dumps(r, ensure_ascii=False) + "\n")
            append = True

def load_table() -> pd.DataFrame:
    if INPUT_PATH.lower().endswith((".xlsx", ".xls")):
        df = pd.read_excel(INPUT_PATH, sheet_name=SHEET_NAME)
    else:
        df = pd.read_csv(INPUT_PATH)
    return df

def pick_col(df: pd.DataFrame, name: str | None) -> str | None:
    if name is None:
        return None
    norm = df.columns.str.lower().str.replace(" ", "", regex=False)
    target = name.lower().replace(" ", "")
    if target in set(norm):
        return df.columns[list(norm).index(target)]
    raise KeyError(f"Column '{name}' not found. Available: {df.columns.tolist()}")

def clean_text(text: str) -> str:
    text = re.sub(r"```.*?```", "", text, flags=re.S)  # fenced code
    text = re.sub(r"(?:Sample Input|Sample Output|Example)[:\s].*", "", text)
    text = text.replace("\r", "").strip()
    return text

def extract_segment_text(full_text: str, seg: Dict[str, Any]) -> str:
    parts = [full_text[s:e] for s, e in seg["spans"]]
    return ("\n\n".join(parts)).strip()

def normalize_and_filter_segments(plan: dict, full_text: str):
    n = len(full_text)
    segments = []
    for seg in plan.get("segments", []):
        spans = []
        for se in seg.get("spans", []):
            if isinstance(se, dict):
                s, e = se.get("start"), se.get("end")
            else:
                try: s, e = se
                except Exception: continue
            try:
                s, e = int(s), int(e)
            except Exception:
                continue
            s = max(0, min(n, s)); e = max(0, min(n, e))
            if e > s: spans.append([s, e])
        spans.sort()
        chk = validate_structures_actions(seg.get("structures", []), seg.get("action", []))
        segments.append({
            "seg_id": seg.get("seg_id"),
            "spans": spans,
            "keep": bool(seg.get("keep")),
            "structures": chk["structures"],
            "action": chk["action"],
            "vocab_ok": chk["ok"],
            "title_suggestion": seg.get("title_suggestion","").strip(),
            "reason": seg.get("reason","").strip()
        })
    return [s for s in segments if s["keep"] and s["spans"] and s["vocab_ok"]]

def ensure_api_key() -> str:
    key = os.getenv("GEMINI_API_KEY") or HARDCODED_API_KEY
    if not key:
        raise RuntimeError("Set GEMINI_API_KEY environment variable or fill HARDCODED_API_KEY.")
    return key

FULL_SCHEMA = SEGMENTATION_SCHEMA

MIN_SCHEMA = {
  "type": "object",
  "properties": {
    "doc_title": {"type": "string"},
    "segments": {
      "type": "array",
      "items": {
        "type": "object",
        "properties": {
          "seg_id": {"type": "integer"},
          "spans": {
            "type": "array",
            "items": {
              "type": "object",
              "properties": {"start": {"type":"integer"}, "end":{"type":"integer"}},
              "required": ["start","end"]
            }
          },
          "keep": {"type": "boolean"},
          "structures": {"type": "array", "items": {"type": "string"}},
          "action": {"type": "array", "items": {"type": "string"}}
        },
        "required": ["seg_id","spans","keep","structures","action"]
      }
    }
  },
  "required": ["doc_title","segments"]
}

def _call_gemini_once(prompt_text: str, api_key: str, schema: dict, timeout=60) -> dict:
    url = f"https://generativelanguage.googleapis.com/v1beta/{MODEL_NAME}:generateContent?key={api_key}"
    payload = {
        "contents": [{"parts": [{"text": prompt_text}]}],
        # 用 systemInstruction 传规则
        "systemInstruction": {"role": "system", "parts": [{"text": SYSTEM_PROMPT}]},
        "generationConfig": {
            "temperature": 0.2,
            "topP": 0.9,
            "maxOutputTokens": 8192,              # ▲▲ 提高上限
            "responseMimeType": "application/json",
            "responseSchema": schema
        }
    }
    r = requests.post(url, json=payload, timeout=timeout)
    r.raise_for_status()
    data = r.json()
    cand = (data.get("candidates") or [{}])[0]
    parts = ((cand.get("content") or {}).get("parts")) or []
    if parts and "text" in parts[0]:
        return json.loads(parts[0]["text"])
    fr = cand.get("finishReason")
    raise ValueError(f"NO_TEXT_PARTS finishReason={fr} shape={str(data)[:400]}")

def gemini_generate_json(prompt_text: str, api_key: str, tries=5, base=2, timeout=60) -> dict:
    # 第一阶段：FULL_SCHEMA
    for k in range(1, tries + 1):
        try:
            log(f"[phase1] try {k}/{tries} calling {MODEL_NAME} ...")
            t0 = time.time()
            data = _call_gemini_once(prompt_text, api_key, schema=FULL_SCHEMA, timeout=timeout)
            log(f"[phase1] ok in {time.time()-t0:.1f}s")
            return data
        except Exception as e:
            msg = repr(e)
            log(f"[phase1] error: {msg}")
            # 出现 MAX_TOKENS/NO_TEXT_PARTS，切到 phase2
            if ("MAX_TOKENS" in msg) or ("NO_TEXT_PARTS" in msg) or ("Unexpected response shape" in msg):
                log("[phase1] switching to MIN_SCHEMA ...")
                break
            if k == tries:
                raise
            sleep = base * (2 ** (k - 1)) + (0.2 * k)
            log(f"[phase1] retry after {sleep:.1f}s ...")
            time.sleep(sleep)

    # 第二阶段：MIN_SCHEMA
    for k in range(1, tries + 1):
        try:
            log(f"[phase2] try {k}/{tries} (MIN_SCHEMA) calling {MODEL_NAME} ...")
            t0 = time.time()
            data = _call_gemini_once(prompt_text, api_key, schema=MIN_SCHEMA, timeout=timeout)
            log(f"[phase2] ok in {time.time()-t0:.1f}s")
            return data
        except Exception as e:
            log(f"[phase2] error: {e!r}")
            if k == tries:
                raise
            sleep = base * (2 ** (k - 1)) + (0.2 * k)
            log(f"[phase2] retry after {sleep:.1f}s ...")
            time.sleep(sleep)


def llm_segment_article(title: str, raw_text: str, api_key: str) -> Tuple[Dict[str, Any], str]:
    full_text = clean_text(raw_text)
    user = build_user_prompt(title or "Untitled", full_text)
    plan = gemini_generate_json(user, api_key)
    return plan, full_text

# ----------------- main -----------------
def main():
    # 清空输出
    if not APPEND_MODE:
        for p in (OUT_PLAN, OUT_SEGMENTS):
            d = os.path.dirname(p)
            if d and not os.path.exists(d):
                os.makedirs(d, exist_ok=True)
            open(p, "w", encoding="utf-8").close()

    api_key = ensure_api_key()
    df = load_table()

    id_col = pick_col(df, ID_COL) if ID_COL else None
    title_col = pick_col(df, TITLE_COL)
    content_col = pick_col(df, CONTENT_COL)

    if MAX_ROWS and MAX_ROWS > 0:
        df = df.head(MAX_ROWS)

    total = 0
    log(f"Loaded {len(df)} rows; start processing ...")
    for idx, row in df.iterrows():
        title = str(row[title_col]) if pd.notna(row[title_col]) else ""
        content = str(row[content_col]) if pd.notna(row[content_col]) else ""
        if not content.strip():
            continue
        doc_id = int(row[id_col]) if (id_col and pd.notna(row[id_col])) else int(idx)

        log(f"[{doc_id}] start: {title[:40]!r}")
        try:
            plan, full_text = llm_segment_article(title, content, api_key)
        except Exception as e:
            log(f"[{doc_id}] LLM error: {e!r}")
            continue

        # 记录原始计划
        write_jsonl(OUT_PLAN, [{
            "doc_id": doc_id, "doc_title": title, "plan": plan
        }], append=True)

        # 规范化 + 提取保留切片
        keepers = normalize_and_filter_segments(plan, full_text)
        flat_rows = []
        for seg in keepers:
            seg_text = extract_segment_text(full_text, seg)
            flat_rows.append({
                "doc_id": doc_id,
                "doc_title": title,
                "seg_id": int(seg["seg_id"]) if seg["seg_id"] is not None else None,
                "structures": seg["structures"],
                "action": seg["action"],
                "spans": seg["spans"],
                "title_suggestion": seg["title_suggestion"],
                "reason": seg["reason"],
                "text": seg_text
            })

        if flat_rows:
            write_jsonl(OUT_SEGMENTS, flat_rows, append=True)
            log(f"[{doc_id}] kept {len(flat_rows)} seg(s)")
        else:
            log(f"[{doc_id}] no kept segments")

        total += 1
        if SLEEP_S > 0:
            time.sleep(SLEEP_S)

    log(f"Done. Processed {total} rows.")

if __name__ == "__main__":
    try:
        import sys
        sys.stdout.reconfigure(line_buffering=True)
    except Exception:
        pass
    main()
