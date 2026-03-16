from __future__ import annotations
import os, re, json, csv, uuid, time, math, collections
from pathlib import Path
from typing import List, Dict, Any, Tuple, Set

import pandas as pd

# ========= 预加载 .env =========
def _load_env_prio():
    candidates = [
        Path.cwd() / ".env",
        Path(__file__).resolve().parent / ".env",
        Path(__file__).resolve().parents[1] / ".env",
    ]
    for p in candidates:
        if p.exists():
            try:
                for line in p.read_text(encoding="utf-8").splitlines():
                    line = line.strip()
                    if not line or line.startswith("#") or "=" not in line:
                        continue
                    k, v = line.split("=", 1)
                    k = k.strip()
                    v = v.strip().strip('"').strip("'")
                    os.environ.setdefault(k, v)
            except Exception:
                pass

_load_env_prio()

if not os.getenv("GEMINI_API_KEY"):
    raise RuntimeError(
        "GEMINI_API_KEY missing. 请在 .env 中加入：\n"
        "  GEMINI_API_KEY=xxxxxxxxxxxxxxxx\n"
        "（建议放在 CWD 或脚本同目录，确保 import faiss_hnsw_pipeline 前即可读到）"
    )

import requests
from requests.adapters import HTTPAdapter
from urllib3.util.retry import Retry
import numpy as np
import faiss

import faiss_hnsw_pipeline as kb

_GEMINI_API_KEY = os.getenv("GEMINI_API_KEY")
_EMB_MODEL = "models/text-embedding-004"
_EMB_URL   = f"https://generativelanguage.googleapis.com/v1beta/models/text-embedding-004:embedContent?key={_GEMINI_API_KEY}"

_VERIFY = not (os.getenv("GEMINI_INSECURE_SKIP_VERIFY", "").strip() in ("1", "true", "True"))

HTTP_PROXY  = os.getenv("HTTP_PROXY")  or "http://127.0.0.1:10809"
HTTPS_PROXY = os.getenv("HTTPS_PROXY") or "http://127.0.0.1:10809"

_SESSION = requests.Session()
_SESSION.trust_env = True
_SESSION.proxies.update({"http": HTTP_PROXY, "https": HTTPS_PROXY})

_RETRY = Retry(
    total=5, connect=5, read=5, backoff_factor=0.6,
    status_forcelist=(429, 500, 502, 503, 504),
    allowed_methods=frozenset(["POST"]),
)
_ADAPTER = HTTPAdapter(max_retries=_RETRY, pool_connections=10, pool_maxsize=10)
_SESSION.mount("https://", _ADAPTER)
_SESSION.mount("http://", _ADAPTER)

_DEFAULT_HEADERS = {"Content-Type": "application/json","Accept": "application/json","Connection": "close"}

def _embed_once_rest(text: str, timeout: float = 40.0) -> np.ndarray:
    payload = {"model": _EMB_MODEL, "content": {"parts": [{"text": text}]}, "taskType": "RETRIEVAL_QUERY"}
    r = _SESSION.post(_EMB_URL, json=payload, headers=_DEFAULT_HEADERS, timeout=timeout, verify=_VERIFY)
    r.raise_for_status()
    data = r.json()
    vals = None
    if "embedding" in data and "values" in data["embedding"]:
        vals = data["embedding"]["values"]
    elif "embeddings" in data and data["embeddings"]:
        first = data["embeddings"][0]
        if isinstance(first, dict) and "values" in first:
            vals = first["values"]
    if vals is None:
        preview = str(data)[:300]
        raise RuntimeError(f"Unexpected embedding payload. Preview: {preview}")
    v = np.asarray(vals, dtype=np.float32).reshape(1, -1)
    n = np.linalg.norm(v, axis=1, keepdims=True) + 1e-12
    return v / n

def _embed_query_rest(text: str, tries: int = 4, base_sleep: float = 1.0) -> np.ndarray:
    last = None
    for i in range(tries):
        try:
            return _embed_once_rest(text, timeout=40.0)
        except Exception as e:
            last = e
            time.sleep(base_sleep * (2 ** i))
    raise last

kb.embed_query = _embed_query_rest

# ===================== 配置 =====================
SUBTASK_DIR          = r"F:\Knowledge-Augmented-Codegen\src\rag\subtasks"
PER_SUBTASK_TOPK     = 3
GLOBAL_CAP           = 12

TOPK_INIT            = 16
MMR_KEEP             = 8
MMR_LAMBDA           = 0.55
EF_SEARCH            = 256

SKIP_CODE_IF_EXISTS = True
SKIP_HITS_IF_EXISTS = True

LANG_COLS = {"c":"C","cpp":"C++","java":"Java","javascript":"JavaScript","python":"Python"}
EXT = {"c": ".c", "cpp": ".cpp", "java": ".java", "javascript": ".js", "python": ".py"}

OUT_CODE = Path(r"F:\Codegen_suggestion\S3"); OUT_CODE.mkdir(parents=True, exist_ok=True)
OUT_HITS = Path(r"F:\Codegen_suggestion\S3_kb_hits"); OUT_HITS.mkdir(parents=True, exist_ok=True)

ASSIGN_XLSX = r"F:\Codegen\ProblemInfoCrawler\ablation_plan.xlsx"

from controlled_vocab import STRUCTURE_ALIASES, ACTION_ALIASES

# ===================== 工具函数 =====================
def _line_comment(prefix: str, body: str) -> str:
    lines = body.splitlines()
    commented = [(prefix + l) if l else prefix.rstrip() for l in lines]
    return "\n".join(commented) + "\n\n"

def lang_comment_wrap(lang: str, body: str) -> str:
    if lang == "python":
        return _line_comment("# ", body)
    return _line_comment("// ", body)

def l2norm(v: np.ndarray) -> np.ndarray:
    v = v.astype("float32")
    n = np.linalg.norm(v, axis=1, keepdims=True) + 1e-12
    return v / n

def sanitize_slug(link_or_text: str) -> str:
    s = (link_or_text or "").strip().lower()
    m = re.search(r"/problems/([^/]+)/?", s)
    if m:
        slug = m.group(1)
    else:
        slug = re.sub(r"[^a-z0-9\-]+", "-", s)[:80].strip("-") or ("problem-" + uuid.uuid4().hex[:8])
    return slug

def _first_n_sentences(text: str, n: int = 3) -> str:
    s = (text or "").strip()
    if not s:
        return ""
    parts = re.split(r"(?<=[\.!?])\s+|\n+", s)
    parts = [p.strip() for p in parts if p.strip()]
    return " ".join(parts[:n])

def _extract_desc_blocks(desc: str) -> Tuple[str, str, str]:
    text = desc or ""
    ex_iter = list(re.finditer(
        r"(?:^|\n)\s*Example\s*\d*\s*:\s*(.*?)(?=(?:\n\s*Example\s*\d*\s*:)|(?:\n\s*Constraints\s*:)|\Z)",
        text, flags=re.S | re.I
    ))
    first_example_full = ex_iter[0].group(0) if ex_iter else ""
    first_example_body = ""
    if first_example_full:
        first_example_body = re.sub(r"^\s*Example\s*\d*\s*:\s*", "", first_example_full, flags=re.I).strip()

    cons_m = re.search(r"(?:^|\n)\s*Constraints\s*:\s*(.*)$", text, flags=re.S | re.I)
    constraints_full = cons_m.group(0) if cons_m else ""
    constraints_body = ""
    if constraints_full:
        constraints_body = re.sub(r"^\s*Constraints\s*:\s*", "", constraints_full, flags=re.I).strip()

    main = text
    if constraints_full:
        main = main.replace(constraints_full, "")
    for m in ex_iter:
        main = main.replace(m.group(0), "")
    main = main.strip()
    return (main, first_example_body, constraints_body)

def _predict_code_path(lang: str, slug: str, difficulty: str, index_val: str) -> Path:
    safe_diff = re.sub(r"[^\w\-]+", "_", (difficulty or "Unknown")).strip("_") or "Unknown"
    subdir = OUT_CODE / lang / safe_diff
    idx_prefix = (str(index_val).strip() + "-") if str(index_val).strip() else ""
    filename = f"{idx_prefix}{slug}{EXT[lang]}"
    return subdir / filename

def _predict_hits_md_path(lang: str, slug: str, difficulty: str, index_val: str) -> Path:
    safe_diff = re.sub(r"[^\w\-]+", "_", (difficulty or "Unknown")).strip("_") or "Unknown"
    subdir = OUT_HITS / lang / safe_diff
    idx_prefix = (str(index_val).strip() + "-") if str(index_val).strip() else ""
    filename = f"{idx_prefix}{slug}.md"
    return subdir / filename

# ===================== 子任务 → 查询文本 =====================
def _expand_aliases(tokens, aliases):
    out = []
    for t in tokens or []:
        t = str(t).strip().lower()
        out.append(t)
        if t in aliases:
            out.append(aliases[t])
    seen=set(); uniq=[]
    for x in out:
        if x and x not in seen:
            uniq.append(x); seen.add(x)
    return uniq

def subtask_to_query_text(st: Dict[str,Any]) -> str:
    intent  = str(st.get("intent","")).strip()
    structs = [s.lower() for s in (st.get("structures") or [])]
    acts    = [a.lower() for a in (st.get("actions") or [])]
    cues    = [str(x).lower() for x in (st.get("cues") or [])]
    cons    = [str(x).lower() for x in (st.get("constraints") or [])]

    structs_exp = _expand_aliases(structs, STRUCTURE_ALIASES)
    acts_exp    = _expand_aliases(acts, ACTION_ALIASES)

    parts = []
    parts += [intent] * 2
    parts += acts_exp * 2
    parts += structs_exp
    parts += cues
    parts += cons
    return " ".join([p for p in parts if p]).strip()

# ===================== 载入索引/知识卡 =====================
def load_index_meta() -> Tuple[faiss.Index, Dict[str, Any]]:
    index = faiss.read_index(kb.INDEX_PATH)
    try:
        index.index.hnsw.efSearch = EF_SEARCH
    except Exception:
        pass
    meta = kb.load_meta()
    return index, meta

_CARDS_BY_ID: Dict[str, Dict[str, Any]] = None

def _load_cards_map() -> Dict[str, Dict[str, Any]]:
    global _CARDS_BY_ID
    if _CARDS_BY_ID is not None:
        return _CARDS_BY_ID
    card_path = getattr(kb, "CARDS_PATH", None)
    mapping: Dict[str, Dict[str, Any]] = {}
    if card_path and Path(card_path).exists():
        with open(card_path, "r", encoding="utf-8") as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue
                try:
                    obj = json.loads(line)
                    cid = str(obj.get("id") or "")
                    if cid:
                        mapping[cid] = obj
                except Exception:
                    continue
    _CARDS_BY_ID = mapping
    return _CARDS_BY_ID

def _read_full_card_by_id(card_id: str) -> Dict[str, Any]:
    cmap = _load_cards_map()
    return cmap.get(card_id, {}) if cmap else {}

# ===================== 构建 + token 化 =====================
TOKEN_FIELDS = ("signals","invariants","tips","pitfalls","title","structures","action","when_to_use","description")
MIN_TOKEN_LEN = 2
IDF_SMOOTH = 1.0          # idf = log( (N+1) / (df+IDF_SMOOTH) ) + 1
IDF_MIN_DF_FRAC = 0.001   # 过滤极少见噪声

_GLOBAL_IDF: Dict[str, float] = None

_WORD_RE = re.compile(r"[a-zA-Z][a-zA-Z\-\+_]*")

def _tok(s: str) -> List[str]:
    if not s: return []
    toks = [t.lower() for t in _WORD_RE.findall(s)]
    return [t for t in toks if len(t) >= MIN_TOKEN_LEN]

def _collect_card_tokens_for_idf(card: Dict[str,Any]) -> Set[str]:
    bag = set()
    for k in TOKEN_FIELDS:
        v = card.get(k)
        if isinstance(v, str):
            for t in _tok(v):
                bag.add(t)
        elif isinstance(v, list):
            for x in v:
                for t in _tok(str(x)):
                    bag.add(t)
    return bag

def build_global_idf() -> Dict[str,float]:
    global _GLOBAL_IDF
    if _GLOBAL_IDF is not None:
        return _GLOBAL_IDF
    cmap = _load_cards_map()
    if not cmap:
        _GLOBAL_IDF = {}
        return _GLOBAL_IDF
    N = len(cmap)
    df = collections.Counter()
    for c in cmap.values():
        toks = _collect_card_tokens_for_idf(c)
        for t in toks:
            df[t] += 1
    # 过滤过稀噪声
    min_df = max(1, int(N * IDF_MIN_DF_FRAC))
    idf = {}
    for t, d in df.items():
        if d >= min_df:
            idf[t] = math.log((N + 1.0) / (d + IDF_SMOOTH)) + 1.0
    _GLOBAL_IDF = idf
    return _GLOBAL_IDF

def query_tokens_from_subtasks(subtasks: List[Dict[str,Any]]) -> Set[str]:
    parts: List[str] = []
    for st in subtasks:
        parts.append(str(st.get("intent","")))
        for k in ("actions","structures","cues","constraints"):
            vs = st.get(k) or []
            parts.extend([str(x) for x in vs])
    bag = set()
    for t in _tok(" ".join(parts)):
        bag.add(t)
    return bag

def card_tokens(card: Dict[str,Any]) -> Set[str]:
    bag = set()
    for k in ("signals","invariants","tips","pitfalls","title","structures","action","when_to_use","description"):
        v = card.get(k)
        if isinstance(v, str):
            bag.update(_tok(v))
        elif isinstance(v, list):
            for x in v:
                bag.update(_tok(str(x)))
    return bag

def coverage_weight(tokens: Set[str], q_tokens: Set[str], idf: Dict[str,float]) -> float:
    if not tokens or not q_tokens: return 0.0
    w = 0.0
    for t in (tokens & q_tokens):
        w += idf.get(t, 0.0)
    return w

# ===================== MMR =====================
def mmr(q: np.ndarray, docs: np.ndarray, ids: List[int], k=8, lambda_=0.55) -> List[int]:
    sims = (docs @ q.reshape(-1, 1)).ravel()
    chosen = [int(np.argmax(sims))]
    remain = set(range(len(ids))) - set(chosen)
    while len(chosen) < min(k, len(ids)):
        best, best_score = -1, -1e9
        for c in remain:
            rel = sims[c]
            red = max((docs[c] @ docs[chosen].T).max(), 0.0)
            score = lambda_ * rel - (1 - lambda_) * red
            if score > best_score:
                best, best_score = c, score
        chosen.append(best); remain.remove(best)
    return [ids[i] for i in chosen]

# ===================== 子任务级检索（S3：不做 MMR/再排序） =====================
def retrieve_kb_for_subtask(index: faiss.Index, meta: Dict[str, Any],
                             subtask: Dict[str,Any], target_lang: str,
                             topn:int,
                             require_sorted: bool | None = None,
                             allow_demote_incompatible: bool = False) -> List[Dict[str, Any]]:
    query_text = subtask_to_query_text(subtask)
    query = kb.compose_query(query_text, constraints=subtask.get("constraints", []))
    qvec  = kb.embed_query(query)  # [1, d] L2 归一化
    D, I  = index.search(qvec.astype("float32"), TOPK_INIT)

    pool = []
    for faiss_id in I[0]:
        if faiss_id < 0:
            continue
        key = str(int(faiss_id))
        info = (meta["infos"].get(key, {}) or {}).copy()
        card_id = meta["id_map"].get(key)

        full = _read_full_card_by_id(card_id) if card_id else {}
        for k in ("title","structures","action","level","min_required_signals","assumption",
                  "signals","when_to_use","description","invariants","tips","pitfalls"):
            if k not in info:
                info[k] = full.get(k, info.get(k))

        cos = 0.0; vec=None
        try:
            v = index.reconstruct(int(faiss_id))
            v = v / (np.linalg.norm(v) + 1e-12)
            vec = v; cos = float(v @ qvec.reshape(-1))
        except Exception:
            pass

        pool.append({"faiss_id": int(faiss_id), "info": info, "cos": cos, "vec": vec, "card_id": card_id})

    if not pool:
        return []

    filtered = []
    ql = query_text.lower()
    for c in pool:
        ass = c["info"].get("assumption", {})
        dep = str((ass or {}).get("language_dependency", "any")).lower()
        lang_ok = (dep in ("any", "", None) or dep == target_lang or dep == f"{target_lang}-only")
        if require_sorted is None:
            sort_ok = True
        else:
            sort_ok = bool((ass or {}).get("requires_sorted_input", False)) == require_sorted
        if lang_ok and sort_ok:
            filtered.append(c)
        elif allow_demote_incompatible:
            c["cos"] *= 0.85
            filtered.append(c)

    if not filtered:
        return []

    out = []
    for c in filtered[:topn]:
        info = c["info"]
        out.append({
            "faiss_id": c["faiss_id"],
            "card_id": c.get("card_id"),
            "title": info.get("title", ""),
            "structures": info.get("structures", []),
            "action": info.get("action", []),
            "when_to_use": info.get("when_to_use", ""),
            "description": info.get("description", ""),
            "invariants": info.get("invariants", [])[:3],
            "tips": info.get("tips", [])[:3],
            "pitfalls": info.get("pitfalls", [])[:3],
            "signals": info.get("signals", [])[:8],
            "level": info.get("level",""),
            "min_required_signals": info.get("min_required_signals", 2),
            "assumption": info.get("assumption", {}),
            "cos": c.get("cos", 0.0),
            "score": c.get("cos", 0.0),
        })
    return out

# ===================== 二次筛 =====================
PRIMARY_MIN_COS      = 0.38   # 主卡余弦下限
PRIMARY_MIN_COVER    = 0.85   # 主卡覆盖权重下限
ALIGN_MIN_OVERLAP    = 1      # 动作/结构至少命中 1 个
INJECT_CAP           = 3      # 最终注入不超过3张
LAMBDA_COS           = 0.35   # 目标函数中 cos 的权重
EPS_GAIN             = 1e-6   # 边际增益太小则停止

def _align_overlap(card: Dict[str,Any], q_actions: Set[str], q_structs: Set[str]) -> int:
    a = set([str(x).lower() for x in (card.get("action") or [])])
    s = set([str(x).lower() for x in (card.get("structures") or [])])
    return len((a & q_actions) | (s & q_structs))

def _primary_gate(card: Dict[str,Any], cov_w: float, align_hits: int) -> bool:
    if float(card.get("cos",0.0)) < PRIMARY_MIN_COS: return False
    if cov_w < PRIMARY_MIN_COVER: return False
    if align_hits < ALIGN_MIN_OVERLAP: return False
    return True

def dedup_by_title(items: List[Dict[str,Any]]) -> List[Dict[str,Any]]:
    pick = {}
    for it in items:
        title = (it.get("title") or "").strip().lower()
        lvl = {"basic":2, "standard":1, "advanced":0}.get((it.get("level","") or "").lower(), 1)
        tup = (float(it.get("score",0.0)), lvl,
               len(it.get("invariants") or []),
               float(it.get("cos",0.0)))
        if title not in pick or tup > pick[title][0]:
            pick[title] = (tup, it)
    return [v[1] for v in pick.values()]

def select_cards_submodular(merged_hits: List[Dict[str,Any]],
                            subtasks: List[Dict[str,Any]]) -> List[Dict[str,Any]]:
    if not merged_hits: return []

    idf = build_global_idf()
    q_tokens = query_tokens_from_subtasks(subtasks)
    q_actions, q_structs = set(), set()
    for st in subtasks:
        q_actions.update([str(x).lower() for x in (st.get("actions") or [])])
        q_structs.update([str(x).lower() for x in (st.get("structures") or [])])

    prep = []
    for c in merged_hits:
        toks = card_tokens(c)
        cov = coverage_weight(toks, q_tokens, idf)
        align = _align_overlap(c, q_actions, q_structs)
        prep.append((c, toks, cov, align))

    prep.sort(key=lambda x: x[0].get("score",0.0), reverse=True)
    primary = prep[0]
    if not _primary_gate(primary[0], primary[2], primary[3]):
        return []

    selected = [primary]
    covered: Set[str] = (primary[1] & q_tokens).copy()
    best_val = LAMBDA_COS * float(primary[0].get("cos",0.0)) + sum([idf.get(t,0.0) for t in covered])

    for _ in range(INJECT_CAP - 1):
        best_gain, best_item = 0.0, None
        for (c, toks, cov, align) in prep:
            if any(c is s[0] for s in selected):
                continue
            new_tokens = (toks & q_tokens) - covered
            gain_cover = sum([idf.get(t,0.0) for t in new_tokens])
            gain = gain_cover + LAMBDA_COS * float(c.get("cos",0.0))
            if gain > best_gain + EPS_GAIN:
                best_gain, best_item = gain, (c, toks, cov, align)
        if best_item is None:
            break
        selected.append(best_item)
        covered |= (best_item[1] & q_tokens)
        best_val += best_gain
        if len(selected) >= INJECT_CAP:
            break

    return [s[0] for s in selected]

def global_resort_and_cap(items: List[Dict[str,Any]], cap: int = 6) -> List[Dict[str,Any]]:
    items = sorted(items, key=lambda x: (x.get("score",0.0), x.get("cos",0.0)), reverse=True)
    return items[:cap]

def _should_zero_inject_after_all(hits: List[Dict[str,Any]]) -> bool:
    return len(hits) == 0

# ===================== Notes =====================
NOTES_BY_LANG = {
    "c": [
        "Keep the given function signature unchanged.",
        "Use the C standard library only; no external packages.",
        "Do not change input/output formats or return value semantics.",
        "Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.",
        "If you introduce any helper functions, include their full implementations in this file; no hidden helpers."
    ],
    "cpp": [
      "Keep the given function signature unchanged.",
      "Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.",
      "Do not change input/output formats or return value semantics.",
      "Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).",
      "If you introduce any helper functions, include their full implementations in this file; no hidden helpers."
    ],
    "java": [
        "Keep the given method signatures unchanged.",
        "Use only Java standard library (`java.*`); no external dependencies.",
        "Do not change input/output formats or return value semantics.",
        "Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.",
        "If you introduce any helper functions, include their full implementations in this file; no hidden helpers."
    ],
    "javascript": [
      "Keep the given function signature unchanged.",
      "Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.",
      "Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.",
      "Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.",
      "If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases."
    ],
    "python": [
      "Keep the given function signature unchanged.",
      "Use only the Python standard library; no third-party packages.",
      "Do not change input/output formats or return value semantics as defined by the template/problem.",
      "Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.",
      "If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers."
    ]
}

def build_header(desc: str, kb_items: List[Dict[str, Any]], link: str, difficulty: str, lang: str) -> str:
    main_text, first_ex_body, constraints_body = _extract_desc_blocks(desc)

    lines: List[str] = []
    lines.append(f"Source: {link or 'N/A'}   |   Difficulty: {difficulty or 'N/A'}")
    lines.append("")
    lines.append("Problem Description:")
    lines.append(main_text.strip())
    if first_ex_body:
        lines.append("")
        lines.append("Example:")
        lines.append(first_ex_body)
    if constraints_body:
        lines.append("")
        lines.append("Constraints:")
        lines.append(constraints_body)

    lines.append("")
    lines.append("Helpful references (internal KB):")
    if kb_items:
        for it in kb_items:
            tags = []
            tags += it.get("structures", []) if isinstance(it.get("structures"), list) else []
            tags += it.get("action", []) if isinstance(it.get("action"), list) else []
            tag_line = (", ".join(tags[:8])) if tags else ""
            title = it.get("title", "") or (it.get("card_id") or "")
            lines.append(f"- {title} ({tag_line})")

            if it.get("when_to_use"):
                lines.append(f"  • When to use: {it['when_to_use']}")
            idea = _first_n_sentences(it.get("description",""), n=2)
            if idea:
                lines.append(f"  • Idea: {idea}")
            invs = [str(x) for x in (it.get("invariants") or [])][:2]
            if invs:
                lines.append("  • Invariants: " + "; ".join(invs))
            tips = [str(x) for x in (it.get("tips") or [])][:2]
            if tips:
                lines.append("  • Tips: " + "; ".join(tips))
            pits = [str(x) for x in (it.get("pitfalls") or [])][:2]
            if pits:
                lines.append("  • Pitfalls: " + "; ".join(pits))
    else:
        lines.append("- N/A")

    lines.append("")
    lines.append("Notes:")
    for note in NOTES_BY_LANG.get(lang, NOTES_BY_LANG["java"]):
        lines.append(f"- {note}")

    return "\n".join(lines)

# ===================== 写文件 =====================
def write_code_file(lang: str, slug: str, header: str, template: str, difficulty: str, index_val: str) -> str:
    safe_diff = re.sub(r"[^\w\-]+", "_", (difficulty or "Unknown")).strip("_") or "Unknown"
    subdir = OUT_CODE / lang / safe_diff
    subdir.mkdir(parents=True, exist_ok=True)
    idx_prefix = (str(index_val).strip() + "-") if str(index_val).strip() else ""
    filename = f"{idx_prefix}{slug}{EXT[lang]}"
    path = subdir / filename
    content = lang_comment_wrap(lang, header) + (template or "").rstrip() + "\n"
    path.write_text(content, encoding="utf-8")
    return str(path)

def write_hits_files(slug: str, lang: str, link: str, difficulty: str, kb_items: List[Dict[str, Any]], hits_writer: csv.writer, index_val: str):
    safe_diff = re.sub(r"[^\w\-]+", "_", (difficulty or "Unknown")).strip("_") or "Unknown"
    subdir = OUT_HITS / lang / safe_diff
    subdir.mkdir(parents=True, exist_ok=True)
    idx_prefix = (str(index_val).strip() + "-") if str(index_val).strip() else ""
    filename = f"{idx_prefix}{slug}.md"
    md_path = subdir / filename

    md_lines = [f"# KB Hits for {slug} [{lang}]",
                f"- Difficulty: {difficulty or 'N/A'}",
                f"- Link: {link or 'N/A'}", ""]
    for i, it in enumerate(kb_items, 1):
        title = it.get("title", "") or (it.get("card_id", "") or f"FAISS-{it.get('faiss_id','')}")
        tags  = []
        tags += it.get("structures", []) if isinstance(it.get("structures"), list) else []
        tags += it.get("action", []) if isinstance(it.get("action"), list) else []
        md_lines.append(f"**{i}. {title}** — tags: {', '.join(tags[:8])}")
    md_path.write_text("\n".join(md_lines), encoding="utf-8")

    titles = "; ".join([(it.get("title", "") or (it.get("card_id") or "")) for it in kb_items])
    hits_writer.writerow([str(index_val or ""), slug, lang, difficulty, link, titles])

def _normalize_assign_language(x: str) -> str:
    s = (x or "").strip()
    if not s:
        return ""
    low = s.lower()
    if low in ("c", "cpp", "c++", "java", "javascript", "js", "python", "py"):
        if low == "c++": return "cpp"
        if low == "js": return "javascript"
        if low == "py": return "python"
        return low
    mapping = {"C":"c","C++":"cpp","Java":"java","JavaScript":"javascript","Python":"python"}
    return mapping.get(s, mapping.get(s.strip(), ""))

# ===================== 主流程 =====================
def main():
    index, meta = load_index_meta()

    if not Path(ASSIGN_XLSX).exists():
        raise FileNotFoundError(f"分配清单不存在：{ASSIGN_XLSX}")
    df = pd.read_excel(ASSIGN_XLSX)
    if "slug" not in df.columns or "language" not in df.columns:
        raise RuntimeError("分配清单必须包含列：slug, language")
    df["slug"] = df["slug"].astype(str).str.strip().str.lower()
    df["language"] = df["language"].astype(str).map(_normalize_assign_language)
    slug2lang: Dict[str,str] = dict(zip(df["slug"], df["language"]))

    subd = Path(SUBTASK_DIR)
    if not subd.exists():
        raise FileNotFoundError(f"Subtasks 目录不存在：{SUBTASK_DIR}")

    json_files = sorted([p for p in subd.glob("*.json") if p.name != "_manifest.jsonl"])
    if not json_files:
        print("⚠️ subtasks 目录为空"); return

    LOG_DIR = Path("logs"); LOG_DIR.mkdir(exist_ok=True)
    log_path = LOG_DIR / "selection_log.csv"
    new_log = not log_path.exists()

    csv_path = OUT_HITS / "summary_hits.csv"
    csv_exists = csv_path.exists()
    fcsv = open(csv_path, "a" if csv_exists else "w", newline="", encoding="utf-8")
    with fcsv, open(log_path, "a", newline="", encoding="utf-8") as flog:
        writer = csv.writer(fcsv)
        logw = csv.writer(flog)

        if not csv_exists:
            writer.writerow(["index", "slug", "lang", "difficulty", "link", "top_hits_titles"])

        if new_log:
            logw.writerow([
                "ts", "slug", "index", "lang", "difficulty", "link",
                "subtask_idx", "subtask_intent",
                "faiss_id", "card_id", "title",
                "cosine", "final_score", "level", "min_required_signals"
            ])

        for jf in json_files:
            obj = json.loads(jf.read_text("utf-8"))
            slug = obj.get("slug","") or sanitize_slug(obj.get("link","") or obj.get("description","")[:64])
            link = obj.get("link","")
            difficulty = obj.get("difficulty","")
            index_val = obj.get("index","")
            desc_full = obj.get("description_full","") or obj.get("description","")
            templates = obj.get("templates",{}) or {}
            subtasks = obj.get("subtasks",[]) or []

            if not subtasks:
                print(f"⚠️ {slug} 无子任务，跳过")
                continue

            # 只跑分配到的语言
            slug_key = str(slug).strip().lower()
            assigned_lang = slug2lang.get(slug_key, "")
            if not assigned_lang:
                print(f"⚠️ {slug} 未在分配清单中出现，跳过")
                continue
            if assigned_lang not in LANG_COLS:
                print(f"⚠️ {slug} 分配语言不支持：{assigned_lang}，跳过")
                continue

            lang = assigned_lang
            template = templates.get(lang, "")
            if not str(template).strip():
                print(f"⚠️ {slug} 缺少模板：{lang}，跳过")
                continue

            code_path = _predict_code_path(lang, slug, difficulty, index_val)
            if SKIP_CODE_IF_EXISTS and code_path.exists():
                print(f"⏭  {lang.upper()} -> {code_path} 已存在，跳过生成")
                continue

            # S3：保留子任务分解 + 初始检索 + 兼容性硬过滤；不做任何后续选择机制  #
            injected: List[Dict[str,Any]] = []
            seen_ids = set()
            for st_idx, st in enumerate(subtasks, 1):
                hits = retrieve_kb_for_subtask(index, meta, st, target_lang=lang,
                                               topn=PER_SUBTASK_TOPK,
                                               require_sorted=None,
                                               allow_demote_incompatible=False)

                for h in hits:
                    logw.writerow([
                        time.strftime("%Y-%m-%d %H:%M:%S"),
                        slug, str(index_val), lang, difficulty, link,
                        st_idx, str(st.get("intent","")),
                        h.get("faiss_id",""), h.get("card_id",""), h.get("title",""),
                        f"{h.get('cos', 0.0):.6f}",
                        f"{h.get('score', 0.0):.6f}",
                        h.get("level",""), h.get("min_required_signals", 2)
                    ])

                for h in hits:
                    key = h["faiss_id"]
                    if key not in seen_ids:
                        injected.append(h)
                        seen_ids.add(key)
                    if len(injected) >= 3:
                        break
                if len(injected) >= 3:
                    break

            merged_hits = injected[:3]

            header = build_header(desc_full, merged_hits, link, difficulty, lang=lang)

            outpath = write_code_file(lang, slug, header, template, difficulty, index_val)

            md_path = _predict_hits_md_path(lang, slug, difficulty, index_val)
            if SKIP_HITS_IF_EXISTS and md_path.exists():
                titles = "; ".join([(it.get("title", "") or (it.get("card_id") or "")) for it in merged_hits])
                writer.writerow([str(index_val or ""), slug, lang, difficulty, link, titles])
                print(f"✅ {lang.upper()} -> {outpath}  | injected={len(merged_hits)}")
            else:
                write_hits_files(slug, lang, link, difficulty, merged_hits, writer, index_val)
                print(f"✅ {lang.upper()} -> {outpath}  | subtasks={len(subtasks)}  per_subtask_topk={PER_SUBTASK_TOPK}  injected={len(merged_hits)}")

    print(f"\n📄 KB hits summary -> {csv_path}")

if __name__ == "__main__":
    main()
