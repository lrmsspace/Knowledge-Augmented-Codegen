import re
from pathlib import Path
import pandas as pd
#挑选消融实验的实验样本

INPUT_XLSX  = r"F:\Knowledge-Augmented-Codegen\ProblemInfoCrawler\data.xlsx"
OUTPUT_XLSX = r"F:\Knowledge-Augmented-Codegen\ProblemInfoCrawler\ablation_plan.xlsx"

LANG_ORDER = ["C", "C++", "Java", "JavaScript", "Python"]

# 按难度分层配额（654/1319/640）
QUOTAS = {
    "Easy":   {"C": 131, "C++": 131, "Java": 131, "JavaScript": 130, "Python": 131},
    "Medium": {"C": 263, "C++": 264, "Java": 264, "JavaScript": 264, "Python": 264},
    "Hard":   {"C": 128, "C++": 128, "Java": 128, "JavaScript": 128, "Python": 128},
}

def _norm(s) -> str:
    return re.sub(r"\s+", "", str(s)).lower()

def find_col(df: pd.DataFrame, candidates):
    cols_norm = {_norm(c): c for c in df.columns}
    for cand in candidates:
        key = _norm(cand)
        if key in cols_norm:
            return cols_norm[key]
    for c in df.columns:
        cn = _norm(c)
        for cand in candidates:
            if _norm(cand) in cn:
                return c
    return None

def normalize_difficulty(x: str) -> str:
    if pd.isna(x):
        return ""
    s = str(x).strip()
    s_low = s.lower()
    if s_low == "easy": return "Easy"
    if s_low == "medium": return "Medium"
    if s_low == "hard": return "Hard"
    return s

def extract_slug(url: str) -> str:
    if pd.isna(url):
        return ""
    s = str(url).strip()
    m = re.search(r"leetcode\.com/problems/([^/]+)/?", s)
    return m.group(1) if m else ""

def round_robin_assign(df_group: pd.DataFrame, diff: str) -> pd.Series:
    quotas = QUOTAS[diff].copy()
    used = {k: 0 for k in quotas}

    assigned = []
    ptr = 0
    for _ in range(len(df_group)):
        tries = 0
        while tries < len(LANG_ORDER) and used[LANG_ORDER[ptr]] >= quotas[LANG_ORDER[ptr]]:
            ptr = (ptr + 1) % len(LANG_ORDER)
            tries += 1
        if tries >= len(LANG_ORDER):
            raise RuntimeError(f"[{diff}] 配额已满但仍有未分配样本，请检查 QUOTAS 与输入数量。")

        lang = LANG_ORDER[ptr]
        assigned.append(lang)
        used[lang] += 1
        ptr = (ptr + 1) % len(LANG_ORDER)

    for lang, q in quotas.items():
        if used[lang] != q:
            raise RuntimeError(f"[{diff}] 语言 {lang} 分配数 {used[lang]} != 配额 {q}。")

    return pd.Series(assigned, index=df_group.index, name="language")

def main():
    infile = Path(INPUT_XLSX)
    if not infile.exists():
        raise FileNotFoundError(f"找不到输入文件：{infile}")

    df = pd.read_excel(infile)

    idx_col  = find_col(df, ["Index"])
    url_col  = find_col(df, ["Link", "URL", "Url"])
    diff_col = find_col(df, ["Difficulty"])
    desc_col = find_col(df, ["Description", "Desc"])

    if any(x is None for x in [idx_col, url_col, diff_col, desc_col]):
        raise ValueError(
            f"缺少必要列。需要 Index/Link/Difficulty/Description。\n"
            f"当前列：{list(df.columns)}"
        )

    c_col   = find_col(df, ["C"])
    cpp_col = find_col(df, ["C++", "Cpp"])
    java_col= find_col(df, ["Java"])
    js_col  = find_col(df, ["JavaScript", "Javascript", "JS"])
    py_col  = find_col(df, ["Python", "Py"])

    if any(x is None for x in [c_col, cpp_col, java_col, js_col, py_col]):
        raise ValueError(
            f"缺少语言模板列。需要 C/C++/Java/JavaScript/Python。\n当前列：{list(df.columns)}"
        )

    TEMPLATE_COL_BY_LANG = {
        "C": c_col,
        "C++": cpp_col,
        "Java": java_col,
        "JavaScript": js_col,
        "Python": py_col,
    }

    out = pd.DataFrame()
    out["index"] = df[idx_col]
    out["url"] = df[url_col]
    out["difficulty"] = df[diff_col].apply(normalize_difficulty)
    out["description"] = df[desc_col]
    out["slug"] = out["url"].apply(extract_slug)

    bad_diff = out[~out["difficulty"].isin(QUOTAS.keys())]
    if len(bad_diff) > 0:
        sample = bad_diff.head(5)[["index", "difficulty", "url"]].to_dict(orient="records")
        raise ValueError(f"发现非法 difficulty。示例：{sample}")

    bad_slug = out[out["slug"] == ""]
    if len(bad_slug) > 0:
        sample = bad_slug.head(5)[["index", "url"]].to_dict(orient="records")
        raise ValueError(f"发现无法解析 slug 的 URL。示例：{sample}")

    counts = out["difficulty"].value_counts().to_dict()
    expected = {d: sum(QUOTAS[d].values()) for d in QUOTAS}
    if counts != expected:
        raise ValueError(f"难度数量与预期不一致。\n实际：{counts}\n预期：{expected}")

    out["language"] = ""
    for diff in ("Easy", "Medium", "Hard"):
        grp = out[out["difficulty"] == diff].sort_values("index", kind="mergesort")
        out.loc[grp.index, "language"] = round_robin_assign(grp, diff)

    def pick_template(row):
        lang = row["language"]
        tpl_col = TEMPLATE_COL_BY_LANG[lang]
        tpl = df.at[row.name, tpl_col]
        return tpl

    out["template"] = out.apply(pick_template, axis=1)

    bad_tpl = out[out["template"].isna() | (out["template"].astype(str).str.strip() == "")]
    if len(bad_tpl) > 0:
        sample = bad_tpl.head(5)[["index", "difficulty", "language", "url"]].to_dict(orient="records")
        raise ValueError(f"存在分配语言后取到空 template 的行（前 5 条）：{sample}")

    plan = out[["index", "slug", "difficulty", "language", "url", "description", "template"]] \
        .sort_values("index", kind="mergesort")

    stats_rows = []
    for diff in ("Easy", "Medium", "Hard"):
        sub = plan[plan["difficulty"] == diff]
        for lang in LANG_ORDER:
            stats_rows.append({
                "difficulty": diff,
                "language": lang,
                "count": int((sub["language"] == lang).sum()),
                "quota": QUOTAS[diff][lang],
            })
    stats = pd.DataFrame(stats_rows)

    outfile = Path(OUTPUT_XLSX)
    outfile.parent.mkdir(parents=True, exist_ok=True)
    with pd.ExcelWriter(outfile, engine="openpyxl") as writer:
        plan.to_excel(writer, index=False, sheet_name="plan")
        stats.to_excel(writer, index=False, sheet_name="stats")

    print(f"✅ 已生成：{outfile}")
    print("plan：index/slug/difficulty/language/url/description/template")
    print("stats：配额核对")


if __name__ == "__main__":
    main()
