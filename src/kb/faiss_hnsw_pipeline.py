# -*- coding: utf-8 -*-
import os, re, json, time, hashlib, math
from typing import List, Dict, Any, Tuple, Optional
from datetime import datetime

import numpy as np
import faiss
import google.generativeai as genai
from dotenv import load_dotenv, find_dotenv
from pathlib import Path

CARDS_PATH   = r"F:\Knowledge-Augmented-Codegen\knowledge_base/cards.jsonl"
INDEX_PATH   = r"F:\Knowledge-Augmented-Codegen\knowledge_base/kb_hnsw.faiss"
META_PATH    = r"F:\Knowledge-Augmented-Codegen\knowledge_base/kb_hnsw_meta.json"

EMB_MODEL    = "models/text-embedding-004"
BATCH_SIZE   = 32
SLEEP_S      = 0.15
MAX_EMB_RETRY= 4

# HNSW 参数
HNSW_M           = 32
HNSW_EF_CONSTR   = 200    # 建索引宽度
HNSW_EF_SEARCH   = 256    # 查询宽度
TOPN_FOR_RERANK  = 64     # 初选召回数

# ========= 控制台日志 =========
def log(msg: str):
    print(datetime.now().strftime("%H:%M:%S"), msg, flush=True)

# ========= 环境初始化 =========
def _load_env_prio() -> None:
    try:
        found = find_dotenv(usecwd=True)
        if found:
            load_dotenv(found, override=False)
    except Exception:
        pass

    candidates = [
        Path.cwd() / ".env",
        Path(__file__).resolve().parent / ".env",
        Path(__file__).resolve().parents[1] / ".env",
        Path(r"F:/Codegen/.env"),
    ]
    for p in candidates:
        if p.exists():
            try:
                for line in p.read_text(encoding="utf-8").splitlines():
                    s = line.strip()
                    if not s or s.startswith("#") or "=" not in s:
                        continue
                    k, v = s.split("=", 1)
                    k = k.strip()
                    v = v.strip().strip('"').strip("'")
                    os.environ.setdefault(k, v)
            except Exception:
                pass

_load_env_prio()

API_KEY = os.getenv("GEMINI_API_KEY") or os.getenv("GOOGLE_API_KEY")
if not API_KEY:
    raise RuntimeError(
        "未找到 GEMINI_API_KEY（或 GOOGLE_API_KEY）。\n"
        "请配置到环境变量或 .env 文件后再运行。"
    )
genai.configure(api_key=API_KEY)

STOPWORDS = set(["a","an","the","for","to","of","in","on","and","or","with","by","from","as","at","is","are","be"])

def _first_sentence_en(s: str, max_chars=180) -> str:
    s=(s or "").strip()
    return re.split(r"[.!?]\s+", s, maxsplit=1)[0][:max_chars] if s else ""

def _clean_tokens(xs, top=6):
    out=[]
    for x in xs or []:
        t=re.sub(r"\W+"," ",str(x)).strip().lower()
        if t and t not in STOPWORDS:
            out.append(t)
        if len(out)>=top: break
    return out

# ========= 检索文本拼接 =========
def compose_retrieval_text(card: Dict[str, Any], max_chars=900) -> str:
    title  = (card.get("title") or "").strip()
    structs= [s.strip() for s in (card.get("structures") or []) if s]
    acts   = [a.strip() for a in (card.get("action") or []) if a]
    sigs   = _clean_tokens(card.get("signals", []), top=6)
    when   = _first_sentence_en(card.get("when_to_use") or "", 120)
    invs   = [i.strip() for i in (card.get("invariants") or []) if i][:2]

    parts = []
    if title:   parts.append(f"[TITLE] {title}. {title}.")   # 2x 强调
    if acts:    parts.append(f"[ACTION] {'; '.join(acts)}.")
    if structs: parts.append(f"[STRUCT] {'; '.join(structs)}.")
    if sigs:    parts.append(f"[SIGNALS] {', '.join(sigs)}.")
    if when:    parts.append(f"[WHEN] {when}.")
    if invs:    parts.append(f"[INVAR] {'; '.join(invs)}.")

    text = " ".join(parts)
    text = re.sub(r"\s+", " ", text).strip()
    return text[:max_chars]

# ========= IO =========
def read_cards(path: str) -> List[Dict[str, Any]]:
    rows = []
    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            line=line.strip()
            if line:
                rows.append(json.loads(line))
    return rows

def ensure_dir_of(path: str):
    d = os.path.dirname(path)
    if d and not os.path.exists(d):
        os.makedirs(d, exist_ok=True)

def load_meta() -> Dict[str, Any]:
    if not os.path.exists(META_PATH):
        return {
            "model": EMB_MODEL,
            "dim": None,
            "created_at": datetime.utcnow().isoformat()+"Z",
            "id_map": {},        # faiss_id(str) -> card_id(str)
            "card_hash": {},     # card_id(str) -> fingerprint(decision surface)
            "infos": {}          # faiss_id(str) -> 决策信息（见下）
        }
    return json.load(open(META_PATH, "r", encoding="utf-8"))

def save_meta(meta: Dict[str, Any]):
    ensure_dir_of(META_PATH)
    json.dump(meta, open(META_PATH, "w", encoding="utf-8"), ensure_ascii=False)


def _decision_fingerprint(card: Dict[str,Any]) -> str:
    payload = {
        "title": card.get("title",""),
        "structures": card.get("structures",[]),
        "action": card.get("action",[]),
        "level": card.get("level",""),
        "min_required_signals": card.get("min_required_signals",2),
        "assumption": card.get("assumption",{}),
        "signals": [str(s).strip().lower() for s in (card.get("signals") or [])][:8],
        "when_to_use": _first_sentence_en(card.get("when_to_use") or "", 120),
        "invariants": (card.get("invariants") or [])[:2],
    }
    s = json.dumps(payload, sort_keys=True, ensure_ascii=False)
    return hashlib.sha256(s.encode("utf-8")).hexdigest()

def _embed_batch(texts: List[str]) -> np.ndarray:
    vecs=[]
    for t in texts:
        # 单条调用；可替换为未来提供的多条接口
        r = genai.embed_content(model=EMB_MODEL, content=t)
        v = np.asarray(r["embedding"], dtype="float32")
        vecs.append(v)
        if SLEEP_S: time.sleep(SLEEP_S)
    return np.vstack(vecs)

def embed_texts_batch(texts: List[str], batch_size: int = BATCH_SIZE) -> np.ndarray:
    if not texts:
        return np.zeros((0, 0), dtype="float32")

    outs = [None] * len(texts)
    # 将索引+文本打包，便于失败重试时保序
    pending = list(enumerate(texts))
    attempt = 0
    while pending and attempt < MAX_EMB_RETRY:
        attempt += 1
        new_pending=[]
        for i in range(0, len(pending), batch_size):
            chunk = pending[i:i+batch_size]
            idxs  = [ix for ix,_ in chunk]
            tks   = [tx for _,tx in chunk]
            try:
                X = _embed_batch(tks)
                if X.ndim != 2:
                    raise ValueError("embedding returns wrong shape")
                for j, ix in enumerate(idxs):
                    outs[ix] = X[j]
            except Exception as e:
                log(f"[warn] embed batch failed (attempt {attempt}): {e!r}")
                new_pending.extend(chunk)
                # 指数退避
                time.sleep( (2 ** attempt) * 0.4 + (0.2 * (attempt)) )
        pending = new_pending

    dim = None
    for v in outs:
        if isinstance(v, np.ndarray):
            dim = v.shape[0]
            break
    if dim is None:
        dim = 768
        log("[ERROR] All embeddings failed; falling back to zero vectors with dim=768. Please check network / API status.")

    for k, v in enumerate(outs):
        if v is None:
            log(f"[warn] embedding fallback to zeros at idx={k}")
            outs[k] = np.zeros((dim,), dtype="float32")

    return np.vstack(outs)

def strid_to_int64(s: str) -> np.int64:
    h = hashlib.blake2b(s.encode("utf-8"), digest_size=8).digest()
    val = int.from_bytes(h, "big", signed=False) & ((1<<63)-1)
    return np.int64(val)

# ========= HNSW 索引 =========
def create_hnsw_index(dim: int) -> faiss.Index:
    try:
        base = faiss.IndexHNSWFlat(dim, HNSW_M, faiss.METRIC_INNER_PRODUCT)
    except TypeError:
        base = faiss.IndexHNSWFlat(dim, HNSW_M)
        base.metric_type = faiss.METRIC_INNER_PRODUCT
    base.hnsw.efConstruction = HNSW_EF_CONSTR
    base.hnsw.efSearch = HNSW_EF_SEARCH
    return faiss.IndexIDMap2(base)

def load_or_create_index(dim: int) -> faiss.Index:
    if os.path.exists(INDEX_PATH):
        idx = faiss.read_index(INDEX_PATH)
        try:
            idx.index.hnsw.efSearch = HNSW_EF_SEARCH
        except Exception:
            pass
        return idx
    else:
        return create_hnsw_index(dim)

def save_index(index: faiss.Index):
    ensure_dir_of(INDEX_PATH)
    faiss.write_index(index, INDEX_PATH)

# ========= upsert =========
def upsert_cards(cards_path: str) -> Tuple[int, int]:
    cards = read_cards(cards_path)
    if not cards:
        raise RuntimeError(f"No cards in {cards_path}")

    meta = load_meta()

    current_ids = {c["id"] for c in cards if "id" in c}
    meta_ids    = set(meta["card_hash"].keys())
    deleted_ids = sorted(list(meta_ids - current_ids))
    if deleted_ids:
        log(f"[WARN] {len(deleted_ids)} card(s) were removed from source. Consider a full rebuild to purge them.")

    to_add_texts, to_add_ids, to_add_card_ids = [], [], []
    to_add_cards = []
    log(f"Loaded {len(cards)} cards")
    for c in cards:
        cid = c["id"]
        rid_text = compose_retrieval_text(c)
        rid_hash = _decision_fingerprint(c)
        existed = meta["card_hash"].get(cid)

        if existed is None:
            to_add_texts.append(rid_text)
            to_add_ids.append(strid_to_int64(cid))
            to_add_card_ids.append(cid)
            to_add_cards.append(c)
            meta["card_hash"][cid] = rid_hash
        elif existed != rid_hash:
            log(f"[WARN] Card decision-surface changed, suggest rebuild: {cid}")

    if not to_add_texts:
        log("No new cards to add.")
        return (0, len(cards))

    # 嵌入 -> L2 归一化
    log(f"Embedding {len(to_add_texts)} new cards …")
    X = embed_texts_batch(to_add_texts, batch_size=BATCH_SIZE)
    if X.ndim != 2:
        raise RuntimeError("Embedding returns non-2D array.")
    d = X.shape[1]
    faiss.normalize_L2(X)

    # 建/载索引 & add_with_ids
    index = load_or_create_index(d)
    try:
        index.index.hnsw.efConstruction = HNSW_EF_CONSTR
        index.index.hnsw.efSearch = HNSW_EF_SEARCH
    except Exception:
        pass

    ids64 = np.array(to_add_ids, dtype="int64")
    index.add_with_ids(X, ids64)

    # 更新元数据
    for fid, cid, text, c in zip(ids64, to_add_card_ids, to_add_texts, to_add_cards):
        meta["id_map"][str(int(fid))] = cid
        meta["infos"][str(int(fid))] = {
            "title": c.get("title",""),
            "structures": c.get("structures", []),
            "action": c.get("action", []),
            "level": c.get("level",""),
            "min_required_signals": c.get("min_required_signals", 2),
            "assumption": c.get("assumption", {}),
            "signals": (c.get("signals", [])[:8] if isinstance(c.get("signals"), list) else []),
            "retrieval_text": text
        }
        if meta["dim"] is None:
            meta["dim"] = d

    save_index(index)
    save_meta(meta)
    log(f"Added {len(to_add_texts)} vectors → {INDEX_PATH}; meta → {META_PATH}")
    return (len(to_add_texts), len(cards) - len(to_add_texts))

# ========= 查询编排 =========
def compose_query(problem_text: str,
                  constraints: Optional[List[str]] = None,
                  language: Optional[str] = None) -> str:
    summary = " ".join(re.split(r"\s+", (problem_text or "").strip())[:160])
    parts = [summary]
    if constraints:
        parts.append("constraints: " + ", ".join(constraints[:6]))
    if language:
        parts.append(f"language: {language}")
    return ". ".join(parts)

def embed_query(text: str) -> np.ndarray:
    v = embed_texts_batch([text])[0]
    nrm = np.linalg.norm(v)
    if nrm > 0: v = v / nrm
    return v.reshape(1, -1)

# ========= 命中阈值 / 前置过滤 / 重排打分 =========
def _assumption_ok(ass: Dict[str,Any], language: Optional[str], require_sorted: Optional[bool]) -> bool:
    if not isinstance(ass, dict): return True
    lang = (language or "").lower()
    dep  = str(ass.get("language_dependency","any")).lower()
    lang_ok = (dep in ("any", "", None) or (lang and dep == lang) or (lang and dep == f"{lang}-only") )
    sort_ok = True if require_sorted is None else (bool(ass.get("requires_sorted_input", False)) == require_sorted)
    return lang_ok and sort_ok

def _count_signal_hits(card_signals: List[str], query_text: str) -> int:
    if not card_signals: return 0
    ql = query_text.lower()
    count=0
    for s in card_signals[:8]:
        t=str(s).lower().strip()
        if t and t in ql:
            count += 1
    return count

def _bonus_score(hit: Dict[str,Any], query_lower: str, small_scale_hint: bool, signal_hits: int) -> float:
    s=0.0
    acts = " ".join((hit.get("action") or [])).lower()
    if any(k in query_lower for k in ["binary search","two pointers","sliding window","kmp","segment tree","fenwick","union find","topo","bfs","dijkstra"]):
        if any(k in acts for k in ["binary-search","two-pointers","sliding-window","kmp","segment-tree","bit-fenwick","union-find","topo","bfs","dijkstra"]):
            s += 0.10

    structs=" ".join((hit.get("structures") or [])).lower()
    if any(k in query_lower for k in ["array","string","graph","tree","heap","interval","matrix","trie"]):
        if any(k in structs for k in ["array","string","graph","tree","heap","interval","matrix","trie"]):
            s += 0.05

    if (hit.get("level")=="advanced") and small_scale_hint:
        s -= 0.10

    mrs = int(hit.get("min_required_signals", 2) or 2)
    if signal_hits < mrs:
        s -= 0.10

    return s

def _looks_small_scale(query_lower: str) -> bool:
    keys = ["single pass","linear scan","small n","n<=","once","just check","count chars","frequency","two numbers","sort then scan"]
    return any(k in query_lower for k in keys)

# ========= 查询 =========
def search(query_text: str,
           k: int = 5,
           ef_search: Optional[int] = None,
           language: Optional[str] = None,
           require_sorted: Optional[bool] = None,
           filter_level_in: Optional[List[str]] = None,
           topn: int = TOPN_FOR_RERANK) -> List[Dict[str, Any]]:

    if not (os.path.exists(INDEX_PATH) and os.path.exists(META_PATH)):
        raise RuntimeError("Index/Meta not found. Run upsert_cards() first.")
    # 载索引
    index = faiss.read_index(INDEX_PATH)
    if ef_search:
        try:
            index.index.hnsw.efSearch = ef_search
        except Exception:
            pass

    # 嵌入查询向量
    q = embed_query(query_text)

    # 初检召回
    sims, ids = index.search(q, max(k, topn))
    meta = load_meta()

    raw_hits=[]
    for s, i in zip(sims[0], ids[0]):
        if i == -1: continue
        key = str(int(i))
        rid = meta["id_map"].get(key)
        info = meta["infos"].get(key, {})
        raw_hits.append({
            "score": float(s), "faiss_id": int(i), "id": rid, **info
        })

    # 前置过滤
    f_hits=[]
    for h in raw_hits:
        if filter_level_in and h.get("level") not in set(filter_level_in):
            continue
        ass = h.get("assumption", {})
        if not _assumption_ok(ass, language, require_sorted):
            # 不直接丢弃：也可选择“降权保留”，这里选择丢弃更干净
            continue
        f_hits.append(h)

    # 轻量重排
    ql = query_text.lower()
    small_hint = _looks_small_scale(ql)
    for h in f_hits:
        signal_hits = _count_signal_hits(h.get("signals") or [], ql)
        h["score"] = h["score"] + _bonus_score(h, ql, small_hint, signal_hits)

    f_hits.sort(key=lambda x: x["score"], reverse=True)
    return f_hits[:k]

# ========= demo =========
if __name__ == "__main__":
    added, skipped = upsert_cards(CARDS_PATH)
    log(f"upsert -> added={added}, skipped={skipped}")

    demo_q = compose_query(
        "Compute a^n mod M efficiently for very large n; exponentiation by squaring; avoid overflow.",
        constraints=["n up to 1e18"],
        language="python",
    )
    log("Searching …")
    results = search(
        demo_q,
        k=5,
        ef_search=256,
        language="c",
        require_sorted=None,
        filter_level_in=None,
        topn=TOPN_FOR_RERANK
    )
    print("Top hits:")
    for r in results:
        print(f"  {r['score']:.3f}  {r['id']}  | {r.get('title')}  | level={r.get('level')}  | action={r.get('action')}")
