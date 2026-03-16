# -*- coding: utf-8 -*-

import os
import json
from collections import Counter, defaultdict
from typing import Any, Dict, List

import pandas as pd

# ====== 路径配置 ======
CARDS_PATH = r"F:/Codegen/output_new/cards.jsonl"
OUT_XLSX   = r"F:/Codegen/output_new/cards_audit.xlsx"

def read_jsonl(path: str) -> List[Dict[str, Any]]:
    """读取 JSONL 文件，每行一个 JSON 对象；忽略坏行。"""
    rows = []
    if not os.path.exists(path):
        raise FileNotFoundError(f"cards file not found: {path}")
    with open(path, "r", encoding="utf-8", errors="ignore") as f:
        for i, line in enumerate(f, 1):
            s = line.strip()
            if not s:
                continue
            try:
                rows.append(json.loads(s))
            except Exception as e:
                # 记录坏行但不中断
                print(f"[warn] bad json line {i}: {e!r}")
    return rows

def list_to_joined(v, sep="; "):
    if isinstance(v, list):
        return sep.join([str(x) for x in v])
    return "" if v is None else str(v)

def count_len(v):
    return len(v) if isinstance(v, list) else 0

def safe_get(d: Dict[str, Any], key: str, default=None):
    return d.get(key, default)

def norm_bool(x) -> bool:
    return bool(x) if isinstance(x, (bool, int)) else False

# ====== 主处理 ======
def build_cards_dataframe(cards: List[Dict[str, Any]]) -> pd.DataFrame:
    rows = []
    for c in cards:
        # 基本字段
        row = {
            "id":              safe_get(c, "id", ""),
            "title":           safe_get(c, "title", ""),
            "level":           safe_get(c, "level", ""),
            "min_required_signals": safe_get(c, "min_required_signals", None),
            "when_to_use":     safe_get(c, "when_to_use", ""),
            "description":     safe_get(c, "description", ""),
        }

        # 数组字段（structures / action / signals / tips / pitfalls / invariants）
        for fld in ("structures", "action", "signals", "tips", "pitfalls", "invariants"):
            arr = safe_get(c, fld, [])
            row[f"{fld}"] = list_to_joined(arr)              # 拼接
            row[f"{fld}_count"] = count_len(arr)             # 数量

        # assumption 展开
        ass = safe_get(c, "assumption", {}) or {}
        row["ass_index_base"] = ass.get("index_base", "any")
        row["ass_requires_sorted_input"] = norm_bool(ass.get("requires_sorted_input", False))
        row["ass_mutates_input"] = norm_bool(ass.get("mutates_input", False))
        row["ass_memory_ownership"] = ass.get("memory_ownership", "any")
        row["ass_graph_weight_type"] = ass.get("graph_weight_type", "any")
        row["ass_recursion_depth_sensitive"] = norm_bool(ass.get("recursion_depth_sensitive", False))
        row["ass_language_dependency"] = ass.get("language_dependency", "any")
        row["ass_other"] = list_to_joined(ass.get("other", []))

        rows.append(row)

    df = pd.DataFrame(rows)

    preferred_cols = [
        "id","title","level","min_required_signals",
        "structures","structures_count",
        "action","action_count",
        "signals","signals_count",
        "when_to_use","description",
        "tips","tips_count",
        "pitfalls","pitfalls_count",
        "invariants","invariants_count",
        "ass_index_base","ass_requires_sorted_input","ass_mutates_input",
        "ass_memory_ownership","ass_graph_weight_type","ass_recursion_depth_sensitive",
        "ass_language_dependency","ass_other",
    ]
    cols = [c for c in preferred_cols if c in df.columns] + [c for c in df.columns if c not in preferred_cols]
    df = df[cols]
    return df

def build_summary_dataframe(df_cards: pd.DataFrame) -> pd.DataFrame:
    lines = []

    def add_section(title: str):
        lines.append({"Metric": f"=== {title} ===", "Value": ""})

    def add_kv(k: str, v: Any):
        lines.append({"Metric": k, "Value": v})

    # 1) 基本
    add_section("Basic")
    n = len(df_cards)
    add_kv("Total cards", n)

    # 2) level 分布
    add_section("Level distribution")
    if "level" in df_cards.columns:
        for lvl, cnt in df_cards["level"].value_counts(dropna=False).items():
            add_kv(f"level == {lvl}", int(cnt))

    # 3) min_required_signals 分布
    add_section("min_required_signals distribution")
    if "min_required_signals" in df_cards.columns:
        for val, cnt in df_cards["min_required_signals"].value_counts(dropna=False).sort_index().items():
            add_kv(f"min_required_signals == {val}", int(cnt))

    # 4) 数组字段的均值/极值
    add_section("List fields statistics")
    for fld in ("structures_count","action_count","signals_count","tips_count","pitfalls_count","invariants_count"):
        if fld in df_cards.columns and n > 0:
            add_kv(f"{fld} mean", round(float(df_cards[fld].mean()), 3))
            add_kv(f"{fld} min",  int(df_cards[fld].min()))
            add_kv(f"{fld} max",  int(df_cards[fld].max()))

    # 5) structures / action 的频次
    def explode_and_count(series: pd.Series) -> Counter:
        cnt = Counter()
        for s in series.dropna():
            items = [x.strip() for x in str(s).split(";") if str(x).strip()]
            cnt.update(items)
        return cnt

    add_section("Structures histogram")
    if "structures" in df_cards.columns:
        scnt = explode_and_count(df_cards["structures"])
        for k, v in scnt.most_common():
            add_kv(f"structures::{k}", int(v))

    add_section("Action histogram")
    if "action" in df_cards.columns:
        acnt = explode_and_count(df_cards["action"])
        for k, v in acnt.most_common():
            add_kv(f"action::{k}", int(v))

    # 6) assumption
    add_section("Assumption booleans")
    for fld in ("ass_requires_sorted_input","ass_mutates_input","ass_recursion_depth_sensitive"):
        if fld in df_cards.columns:
            true_cnt = int(df_cards[fld].sum())
            add_kv(f"{fld} == True", true_cnt)

    # 7) language_dependency 非 any 的比例/计数
    add_section("Assumption language_dependency")
    if "ass_language_dependency" in df_cards.columns:
        non_any = df_cards["ass_language_dependency"].fillna("any").astype(str) != "any"
        add_kv("language_dependency != any (count)", int(non_any.sum()))
        add_kv("language_dependency != any (ratio)", round(float(non_any.mean()), 4))

    df_sum = pd.DataFrame(lines)
    return df_sum

def main():
    # 读取 cards
    cards = read_jsonl(CARDS_PATH)
    if not cards:
        raise RuntimeError(f"No cards found in {CARDS_PATH}")

    # 明细表
    df_cards = build_cards_dataframe(cards)
    # 汇总表
    df_summary = build_summary_dataframe(df_cards)

    out_dir = os.path.dirname(OUT_XLSX)
    if out_dir and not os.path.exists(out_dir):
        os.makedirs(out_dir, exist_ok=True)

    with pd.ExcelWriter(OUT_XLSX, engine="openpyxl") as writer:
        df_cards.to_excel(writer, index=False, sheet_name="cards")
        df_summary.to_excel(writer, index=False, sheet_name="summary")

    print(f"[ok] wrote Excel -> {OUT_XLSX}")
    print(f"  sheets: cards({len(df_cards)}) + summary({len(df_summary)})")

if __name__ == "__main__":
    main()
