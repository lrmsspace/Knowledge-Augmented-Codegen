"""
'structures' 和 'action' 的受控词汇表，以及别名映射和辅助功能，以规范和验证知识条目。
"""

from __future__ import annotations

import re
from typing import Dict, Iterable, List, Sequence, Set, Tuple

# -----------------------------
# Canonical controlled vocab
# -----------------------------

# structures = data shapes (NOT algorithms)
ALLOWED_STRUCTURES: Set[str] = frozenset([
    "array",
    "string",
    "matrix",
    "interval",
    "linked-list",
    "tree",
    "graph",
    "trie",
    "heap",
    "stack",
    "queue",
    "deque",
    "bitset",
    "geometry",
    "number",
    "ds",  # generic data-structure topic bucket
])

# action = algorithmic intent / technique
ALLOWED_ACTIONS: Set[str] = frozenset([
    # window / selection / search
    "two-pointers",
    "sliding-window",
    "min-window",
    "max-window",
    "heap-select",
    "quickselect",
    "binary-search",
    "binary-search-answer",

    # prefix / difference / counting
    "prefix-sum",
    "prefix-xor",
    "difference-array",
    "counting",
    "coordinate-compress",

    # order maintenance
    "monotonic-stack",
    "monotonic-queue",
    "ordered-set",

    # graph / connectivity / shortest path
    "bfs",
    "multi-source-bfs",
    "01-bfs",
    "dfs",
    "topo",
    "dijkstra",
    "bellman-ford",
    "floyd-warshall",
    "mst-kruskal",
    "mst-prim",
    "union-find",
    "scc",
    "biconnected-components",
    "eulerian-circuit",

    # tree
    "tree-dp",
    "lca",
    "binary-lifting",
    "rerooting",

    # dynamic programming
    "dp-1d",
    "dp-2d",
    "interval-dp",
    "digit-dp",
    "bitmask-dp",
    "knapsack",
    "lis",

    # string algorithms
    "kmp",
    "z-function",
    "rolling-hash",
    "aho-corasick",
    "trie-match",
    "suffix-array",

    # greedy / sweep
    "greedy",
    "sweep-line",
    "interval-scheduling",

    # data structures (ops)
    "segment-tree",
    "bit-fenwick",
    "sparse-table",
    "disjoint-sparse-table",

    # math / number theory
    "gcd",
    "sieve",
    "mod-exp",
    "matrix-exp",

    # general paradigms
    "divide-and-conquer",
    "recursion",
    "backtracking",
    "enumeration",
    "simulation",
    "hashing",

    # sorting family
    "merge-sort",
    "counting-sort",
    "radix-sort",
    "bucket-sort",
    "shell-sort",

    # randomized / sampling
    "reservoir-sampling",
    "rejection-sampling",
    "randomized",

    # extra selection
    "heap-select",  # duplicated above for clarity; set removes dup
    "quickselect",  # duplicated above

    # newly added domains
    "probability-statistics",
    "game-theory",
])

# -----------------------------
# Alias mappings (normalize to canonical)
# -----------------------------

STRUCTURE_ALIASES: Dict[str, str] = {
    # variants -> canonical
    "binary tree": "tree",
    "bst": "tree",
    "binary-search-tree": "tree",
    "grid": "matrix",
    "board": "matrix",
    "doubly-linked-list": "linked-list",
    "dll": "linked-list",
}

ACTION_ALIASES: Dict[str, str] = {
    # spacing / punctuation variants
    "binary indexed tree": "bit-fenwick",
    "fenwick": "bit-fenwick",
    "bit": "bit-fenwick",  # common shorthand

    "topological sort": "topo",
    "topological-sort": "topo",
    "kth": "heap-select",
    "top k": "heap-select",
    "top-k": "heap-select",
    "window": "sliding-window",
    "minimum window": "min-window",
    "maximum window": "max-window",
    "disjoint set": "union-find",
    "dsu": "union-find",
    "strongly connected component": "scc",
    "strongly-connected-components": "scc",
    "biconnected component": "biconnected-components",
    "eulerian cycle": "eulerian-circuit",
    "line sweep": "sweep-line",
    "shortest path": "dijkstra",  # default alias; refine via preconditions if needed
    "bellman ford": "bellman-ford",
    "floyd warshall": "floyd-warshall",
    "kruskal": "mst-kruskal",
    "prim": "mst-prim",
    "ordered map": "ordered-set",
    "ordered set": "ordered-set",
    "coordinate compression": "coordinate-compress",

    # string
    "string matching": "kmp",  # generic alias → refine by signals later
    "suffix array": "suffix-array",
    "aho corasick": "aho-corasick",
    "z function": "z-function",
    "k m p": "kmp",
    "rolling hash": "rolling-hash",

    # DP / paradigms
    "memoization": "dp-1d",          # default bucket; refine if 2D
    "dynamic programming": "dp-1d",  # default bucket; refine per context

    # probability / game theory
    "probability": "probability-statistics",
    "expected value": "probability-statistics",
    "expectation": "probability-statistics",
    "linearity of expectation": "probability-statistics",
    "bayes": "probability-statistics",
    "markov chain": "probability-statistics",
    "distribution": "probability-statistics",

    "game theory": "game-theory",
    "grundy": "game-theory",
    "sprague-grundy": "game-theory",
    "nim": "game-theory",
    "mex": "game-theory",
    "minimax": "game-theory",
    "zero-sum": "game-theory",
}

# -----------------------------
# Helpers
# -----------------------------

_KEBAB_RE = re.compile(r"[^a-z0-9]+")

def to_kebab(s: str) -> str:
    """Normalize token to lowercase kebab-case (alnum + single hyphen)."""
    s = s.strip().lower()
    s = _KEBAB_RE.sub("-", s).strip("-")
    s = re.sub("-{2,}", "-", s)
    return s

def normalize_token(token: str, aliases: Dict[str, str], allowed: Set[str]) -> Tuple[str, bool]:
    """
    Return (canonical, is_valid). Applies kebab-case, alias mapping, and membership check.
    """
    t = to_kebab(token)
    if t in allowed:
        return t, True
    if t in aliases:
        canon = aliases[t]
        return canon, canon in allowed
    return t, False

def normalize_tokens(tokens: Iterable[str],
                     aliases: Dict[str, str],
                     allowed: Set[str],
                     drop_unknown: bool = True) -> Tuple[List[str], List[str]]:
    """
    Normalize a list of tokens. Returns (canonical_list, unknown_tokens).
    Unknown tokens are kebab-cased originals that failed to map to allowed set.
    If drop_unknown=True, they are removed from the canonical list.
    """
    seen: Set[str] = set()
    canonical: List[str] = []
    unknown: List[str] = []
    for tok in tokens:
        canon, ok = normalize_token(tok, aliases, allowed)
        if ok:
            if canon not in seen:
                canonical.append(canon)
                seen.add(canon)
        else:
            unknown.append(canon)  # canon here is kebab-cased original
            if not drop_unknown and canon not in seen:
                canonical.append(canon)
                seen.add(canon)
    return canonical, unknown

def validate_structures_actions(structures: Sequence[str], action: Sequence[str]) -> Dict[str, object]:
    """
    Validate and normalize `structures` and `action` fields of a knowledge card.
    Returns a dict with normalized fields and any errors.
    """
    norm_struct, unk_struct = normalize_tokens(structures, STRUCTURE_ALIASES, ALLOWED_STRUCTURES)
    norm_action, unk_action = normalize_tokens(action, ACTION_ALIASES, ALLOWED_ACTIONS)

    errors: List[str] = []
    if not norm_struct:
        errors.append("structures is empty or contains no allowed tokens")
    if not norm_action:
        errors.append("action is empty or contains no allowed tokens")

    return {
        "structures": norm_struct,
        "action": norm_action,
        "unknown_structures": unk_struct,
        "unknown_actions": unk_action,
        "errors": errors,
        "ok": len(errors) == 0
    }

if __name__ == "__main__":
    # quick self-test / demo
    demo = validate_structures_actions(
        structures=["Grid", "BST", "Doubly-Linked-List"],
        action=["Line Sweep", "Kth", "Strongly Connected Component", "Memoization"]
    )
    from pprint import pprint
    pprint(demo)
