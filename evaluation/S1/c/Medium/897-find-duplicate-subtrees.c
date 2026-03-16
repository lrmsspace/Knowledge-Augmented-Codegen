// Source: https://leetcode.com/problems/find-duplicate-subtrees/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return all duplicate subtrees.
//
// For each kind of duplicate subtrees, you only need to return the root node of any one of them.
//
// Two trees are duplicate if they have the same structure with the same node values.
//
// Example:
// Input: root = [1,2,3,4,null,2,4,null,null,4]
// Output: [[2,4],[4]]
//
// Constraints:
// The number of the nodes in the tree will be in the range [1, 5000]
// 	-200 <= Node.val <= 200
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
//   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
//   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
//   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
//   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
//   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
#include <stdlib.h>
#include <string.h>

enum { BUCKETS = 10007 };
struct Entry { int val; int left; int right; int id; struct Entry* next; };

typedef struct Ctx {
    struct Entry **buckets;
    int capacity; /* capacity for id-based arrays */
    int *counts;
    struct TreeNode **firstNode;
    int nextId;
    struct TreeNode **results;
    int resCap;
    int resSize;
} Ctx;

static int hash_key(int val, int left, int right) {
    unsigned int h = (unsigned int)(val + 1000);
    h = h * 1000003u + (unsigned int)left;
    h = h * 1009u + (unsigned int)right;
    return (int)(h % BUCKETS);
}

static void ensure_id_cap(Ctx *ctx, int id) {
    if (id < ctx->capacity) return;
    int newCap = ctx->capacity * 2;
    if (newCap == 0) newCap = 1024;
    while (id >= newCap) newCap *= 2;
    ctx->counts = (int*)realloc(ctx->counts, newCap * sizeof(int));
    memset(ctx->counts + ctx->capacity, 0, (newCap - ctx->capacity) * sizeof(int));
    ctx->firstNode = (struct TreeNode**)realloc(ctx->firstNode, newCap * sizeof(struct TreeNode*));
    memset(ctx->firstNode + ctx->capacity, 0, (newCap - ctx->capacity) * sizeof(struct TreeNode*));
    ctx->capacity = newCap;
}

static int lookup_add(Ctx *ctx, int val, int left, int right) {
    int h = hash_key(val, left, right);
    struct Entry *e = ctx->buckets[h];
    while (e) {
        if (e->val == val && e->left == left && e->right == right) return e->id;
        e = e->next;
    }
    struct Entry *ne = (struct Entry*)malloc(sizeof(struct Entry));
    if (!ne) return 0;
    ne->val = val; ne->left = left; ne->right = right; ne->id = ctx->nextId++;
    ne->next = ctx->buckets[h]; ctx->buckets[h] = ne;
    ensure_id_cap(ctx, ne->id);
    return ne->id;
}

static int dfs(Ctx *ctx, struct TreeNode *node) {
    if (!node) return 0;
    int L = dfs(ctx, node->left);
    int R = dfs(ctx, node->right);
    int id = lookup_add(ctx, node->val, L, R);
    if (id >= ctx->capacity) ensure_id_cap(ctx, id);
    ctx->counts[id]++;
    if (ctx->counts[id] == 1) ctx->firstNode[id] = node;
    else if (ctx->counts[id] == 2) {
        if (ctx->resSize >= ctx->resCap) {
            int newCap = ctx->resCap == 0 ? 16 : ctx->resCap * 2;
            struct TreeNode **tmp = (struct TreeNode**)realloc(ctx->results, newCap * sizeof(struct TreeNode*));
            if (!tmp) return id; /* allocation failure, but continue gracefully */
            ctx->results = tmp; ctx->resCap = newCap;
        }
        ctx->results[ctx->resSize++] = ctx->firstNode[id];
    }
    return id;
}
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** findDuplicateSubtrees(struct TreeNode* root, int* returnSize) {
    if (!returnSize) return NULL;

    Ctx ctx_s = {0};
    Ctx *ctx = &ctx_s;
    ctx->buckets = (struct Entry**)calloc(BUCKETS, sizeof(struct Entry*));
    if (!ctx->buckets) return NULL;
    ctx->capacity = 1024;
    ctx->counts = (int*)calloc(ctx->capacity, sizeof(int));
    ctx->firstNode = (struct TreeNode**)calloc(ctx->capacity, sizeof(struct TreeNode*));
    if (!ctx->counts || !ctx->firstNode) {
        free(ctx->buckets); free(ctx->counts); free(ctx->firstNode); return NULL;
    }
    ctx->nextId = 1;
    ctx->results = NULL; ctx->resCap = 0; ctx->resSize = 0;

    dfs(ctx, root);

    /* free hash map entries */
    for (int i = 0; i < BUCKETS; ++i) {
        struct Entry *e = ctx->buckets[i];
        while (e) { struct Entry *t = e->next; free(e); e = t; }
    }
    free(ctx->buckets);
    free(ctx->counts);
    free(ctx->firstNode);

    *returnSize = ctx->resSize;
    return ctx->results;
}