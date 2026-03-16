// Source: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.
//
// Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
//
// The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.
//
// You are given a 2D integer array queries. For each queries[i] = [ui, vi], determine the number of ways to assign weights to edges in the path such that the cost of the path between ui and vi is odd.
//
// Return an array answer, where answer[i] is the number of valid assignments for queries[i].
//
// Since the answer may be large, apply modulo 109 + 7 to each answer[i].
//
// Note: For each query, disregard all edges not in the path between node ui and vi.
//
// Example:
// Input: edges = [[1,2]], queries = [[1,1],[1,2]]
//
// Output: [0,1]
//
// Explanation:
//
//
// 	Query [1,1]: The path from Node 1 to itself consists of no edges, so the cost is 0. Thus, the number of valid assignments is 0.
// 	Query [1,2]: The path from Node 1 to Node 2 consists of one edge (1 → 2). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi]
// 	1 <= queries.length <= 105
// 	queries[i] == [ui, vi]
// 	1 <= ui, vi <= n
// 	edges represents a valid tree.
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: Use when you need to perform O(1) range queries on a static array for an associative operation, after an O(N log N) preprocessing step.
//   • Idea: A data structure that precomputes answers for all possible range queries using an associative operation on a static array. It achieves O(1) query time and O(N log N) build time by storing prefix-like sums within logarithmically sized blocks.
//   • Invariants: For each level k, the array is partitioned into 2^k segments.; Within each segment, table[k][j] stores the result of the associative operation from j to the segment's midpoint (or midpoint to j).
//   • Tips: Ensure the operation is associative (e.g., min, max, sum, gcd, bitwise operations).; Preprocessing takes O(N log N) time and space.
//   • Pitfalls: Not suitable for mutable arrays; updates require rebuilding the table.; Requires O(N log N) memory, which can be substantial for very large N.
// - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
//   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
//   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
//   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
//   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
//   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Step 1: Build the tree from the edges array
    int n = edgesSize + 1; // Number of nodes is edges + 1
    int* children[n];
    int childrenCount[n];
    for (int i = 0; i < n; i++) {
        childrenCount[i] = 0;
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0] - 1; // Convert to 0-based index
        int v = edges[i][1] - 1; // Convert to 0-based index
        children[u][childrenCount[u]++] = v;
        children[v][childrenCount[v]++] = u;
    }

    // Step 2: Precompute the depth and parent for each node using DFS
    int parent[n];
    int depth[n];
    parent[0] = -1; // Root node has no parent
    depth[0] = 0;

    void dfs(int u, int p) {
        for (int i = 0; i < childrenCount[u]; i++) {
            int v = children[u][i];
            if (v != p) { // Avoid going back to parent
                parent[v] = u;
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
        }
    }
    dfs(0, -1);

    // Step 3: Process each query to determine the number of valid assignments
    int mod = 1000000007;
    int* answer = (int*)malloc(queriesSize * sizeof(int));
    for (int i = 0; i < queriesSize; i++) {
        int u = queries[i][0] - 1; // Convert to 0-based index
        int v = queries[i][1] - 1; // Convert to 0-based index

        // Find LCA of u and v
        int lca(int a, int b) {
            if (depth[a] < depth[b]) {
                int temp = a;
                a = b;
                b = temp;
            }
            while (depth[a] > depth[b]) {
                a = parent[a];
            }
            while (a != b) {
                a = parent[a];
                b = parent[b];
            }
            return a;   
        }
        int ancestor = lca(u, v);
        // Calculate the number of edges in the path from u to v
        int pathLength = depth[u] + depth[v] - 2 * depth[ancestor];
        // The number of ways to assign weights to make the path cost odd is 2^(pathLength - 1)
        if (pathLength == 0) {
            answer[i] = 0; // No edges in the path, cost is 0 (even)
        } else {
            long long ways = 1;
            for (int j = 0; j < pathLength - 1; j++) {
                ways = (ways * 2) % mod;
            }
            answer[i] = (int)ways;
        }
    }
    *returnSize = queriesSize;
    return answer;
}
