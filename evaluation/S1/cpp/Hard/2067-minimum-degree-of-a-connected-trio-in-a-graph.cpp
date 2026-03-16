// Source: https://leetcode.com/problems/minimum-degree-of-a-connected-trio-in-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph. You are given an integer n which is the number of nodes in the graph and an array edges, where each edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi.
//
// A connected trio is a set of three nodes where there is an edge between every pair of them.
//
// The degree of a connected trio is the number of edges where one endpoint is in the trio, and the other is not.
//
// Return the minimum degree of a connected trio in the graph, or -1 if the graph has no connected trios.
//
// Example:
// Input: n = 6, edges = [[1,2],[1,3],[3,2],[4,1],[5,2],[3,6]]
// Output: 3
// Explanation: There is exactly one trio, which is [1,2,3]. The edges that form its degree are bolded in the figure above.
//
// Constraints:
// 2 <= n <= 400
// 	edges[i].length == 2
// 	1 <= edges.length <= n * (n-1) / 2
// 	1 <= ui, vi <= n
// 	ui != vi
// 	There are no repeated edges.
//
// Helpful references (internal KB):
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Minimum Enclosing Circle (geometry, number, simulation)
//   • When to use: When you need to find the smallest circle that contains all given points in a 2D plane, often with a requirement for expected linear time complexity.
//   • Idea: This algorithm iteratively constructs the Minimum Enclosing Circle (MEC) by considering points one by one, potentially updating the circle if a new point lies outside. It achieves an expected linear time complexity, O(N), through randomization.
//   • Invariants: The current circle C is the MEC for the subset of points processed so far.; If C is defined by 1 point p_i, it is the MEC of points processed so far that passes through p_i.
//   • Tips: Randomly shuffle input points to achieve expected linear time complexity.; The Minimum Enclosing Circle is always defined by 2 or 3 points on its boundary.
//   • Pitfalls: A naive implementation without randomization can lead to O(N^3) worst-case time complexity.; Floating-point precision issues can arise in geometric calculations, requiring careful handling.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<unordered_set<int>> graph(n + 1);
        vector<int> degree(n + 1, 0);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            graph[u].insert(v);
            graph[v].insert(u);
            degree[u]++;
            degree[v]++;
        }

        int minDegree = INT_MAX;
        for (int u = 1; u <= n; ++u) {
            for (int v : graph[u]) {
                if (v > u) {
                    for (int w : graph[v]) {
                        if (w > v && graph[u].count(w)) {
                            int trioDegree = degree[u] + degree[v] + degree[w] - 6;
                            minDegree = min(minDegree, trioDegree);
                        }
                    }
                }
            }
        }

        return (minDegree == INT_MAX) ? -1 : minDegree;         
    }
};
