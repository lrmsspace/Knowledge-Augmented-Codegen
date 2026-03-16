// Source: https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted tree with n nodes, numbered from 0 to n - 1. It is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi.​
//
// Additionally, you are given a 2D integer array queries, where queries[j] = [src1j, src2j, destj].
//
// Return an array answer of length equal to queries.length, where answer[j] is the minimum total weight of a subtree such that it is possible to reach destj from both src1j and src2j using edges in this subtree.
//
// A subtree here is any connected subset of nodes and edges of the original tree forming a valid tree.
//
// Example:
// Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], queries = [[2,3,4],[0,2,5]]
//
// Output: [12,11]
//
// Explanation:
//
// The blue edges represent one of the subtrees that yield the optimal answer.
//
//
//
//
// 	
// 	answer[0]: The total weight of the selected subtree that ensures a path from src1 = 2 and src2 = 3 to dest = 4 is 3 + 5 + 4 = 12.
// 	
// 	
// 	answer[1]: The total weight of the selected subtree that ensures a path from src1 = 0 and src2 = 2 to dest = 5 is 2 + 3 + 6 = 11.
//
// Constraints:
// 3 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ui, vi < n
// 	1 <= wi <= 104
// 	1 <= queries.length <= 105
// 	queries[j].length == 3
// 	0 <= src1j, src2j, destj < n
// 	src1j, src2j, and destj are pairwise distinct.
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
//   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
//   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
//   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
//   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
//   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
// - Second Best Minimum Spanning Tree (graph, tree, mst-kruskal, lca, binary-lifting, enumeration)
//   • When to use: When you need to find a spanning tree with the second smallest total edge weight, typically after finding the primary Minimum Spanning Tree.
//   • Idea: This algorithm finds the second best Minimum Spanning Tree by iterating through non-MST edges, adding each to the MST to form a cycle, and then removing the maximum weight edge on that cycle (excluding the added edge). It leverages Kruskal's for the initial MST and LCA with binary lifting for efficient path maximum queries, achieving an overall time complexity of O(E log E + E log V).
//   • Invariants: The initial MST is always a valid spanning tree with minimum total weight.; For any non-MST edge (u, v) added, a unique cycle is formed in the current graph.
//   • Tips: Precompute LCA and maximum edge weights on paths using binary lifting for efficiency.; The initial MST can be found using Kruskal's or Prim's algorithm.
//   • Pitfalls: Incorrectly identifying the maximum weight edge on the cycle when adding a non-MST edge.; Forgetting to exclude the newly added edge itself when finding the maximum edge on the cycle.
// - Heavy-light decomposition (tree, segment-tree, lca, dfs)
//   • When to use: When you need to perform path queries or updates on a tree efficiently, often involving operations like sum, min, max, or XOR on edges/nodes along a path. It transforms tree paths into linear segments for data structure application.
//   • Idea: Heavy-light decomposition partitions a tree into disjoint heavy paths and light edges, allowing tree path operations to be performed efficiently using data structures like segment trees. It typically achieves O(log^2 N) or O(log N) complexity per query/update after O(N log N) or O(N) preprocessing.
//   • Invariants: Each node belongs to exactly one heavy path.; Moving from a node to its parent via a light edge reduces the subtree size by at least half.
//   • Tips: Perform two DFS traversals: one for subtree sizes and parent pointers, another for heavy/light edges and path IDs.; Map tree nodes to a 1D array for segment tree operations based on their position in heavy paths.
//   • Pitfalls: Incorrectly identifying heavy edges (largest subtree size) during the first DFS.; Off-by-one errors when mapping nodes to segment tree indices or handling path boundaries.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        const int n = static_cast<int>(edges.size()) + 1;
        vector<vector<pair<int, int>>> g(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        const int LOG = 17 + (n > 1 ? static_cast<int>(log2(n)) : 0); // enough for n <= 1e5
        vector<int> depth(n, 0);
        vector<long long> dist(n, 0);
        vector<vector<int>> up(LOG, vector<int>(n, 0));

        // DFS to fill depth, dist, and immediate parent.
        stack<int> st;
        vector<int> parent(n, -1);
        st.push(0);
        parent[0] = 0;
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            for (auto [v, w] : g[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                dist[v] = dist[u] + w;
                st.push(v);
            }
        }

        for (int v = 0; v < n; ++v) up[0][v] = parent[v];
        for (int k = 1; k < LOG; ++k) {
            for (int v = 0; v < n; ++v) {
                up[k][v] = up[k - 1][up[k - 1][v]];
            }
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);
            int diff = depth[u] - depth[v];
            for (int k = 0; diff; ++k, diff >>= 1) {
                if (diff & 1) u = up[k][u];
            }
            if (u == v) return u;
            for (int k = LOG - 1; k >= 0; --k) {
                if (up[k][u] != up[k][v]) {
                    u = up[k][u];
                    v = up[k][v];
                }
            }
            return up[0][u];
        };

        auto dist_between = [&](int u, int v) {
            int a = lca(u, v);
            return dist[u] + dist[v] - 2LL * dist[a];
        };

        vector<int> ans;
        ans.reserve(queries.size());
        for (const auto& q : queries) {
            int a = q[0], b = q[1], c = q[2];
            long long total = dist_between(a, b) + dist_between(a, c) + dist_between(b, c);
            ans.push_back(static_cast<int>(total / 2)); // Steiner tree weight for 3 nodes in a tree.
        }
        return ans;
    }
};
