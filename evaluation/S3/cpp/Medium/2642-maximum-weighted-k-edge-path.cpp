// Source: https://leetcode.com/problems/maximum-weighted-k-edge-path/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n and a Directed Acyclic Graph (DAG) with n nodes labeled from 0 to n - 1. This is represented by a 2D array edges, where edges[i] = [ui, vi, wi] indicates a directed edge from node ui to vi with weight wi.
//
// You are also given two integers, k and t.
//
// Your task is to determine the maximum possible sum of edge weights for any path in the graph such that:
//
//
// 	The path contains exactly k edges.
// 	The total sum of edge weights in the path is strictly less than t.
//
//
// Return the maximum possible sum of weights for such a path. If no such path exists, return -1.
//
// Example:
// Input: n = 3, edges = [[0,1,1],[1,2,2]], k = 2, t = 4
//
// Output: 3
//
// Explanation:
//
//
//
//
// 	The only path with k = 2 edges is 0 -> 1 -> 2 with weight 1 + 2 = 3 < t.
// 	Thus, the maximum possible sum of weights less than t is 3.
//
// Constraints:
// 1 <= n <= 300
// 	0 <= edges.length <= 300
// 	edges[i] = [ui, vi, wi]
// 	0 <= ui, vi < n
// 	ui != vi
// 	1 <= wi <= 10
// 	0 <= k <= 300
// 	1 <= t <= 600
// 	The input graph is guaranteed to be a DAG.
// 	There are no duplicate edges.
//
// Helpful references (internal KB):
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxWeight(int n, vector<vector<int>>& edges, int k, int t) {
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
        }

        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        for (int i = 0; i < n; ++i) {
            dp[i][0] = 0;
        }

        for (int j = 1; j <= k; ++j) {
            for (int u = 0; u < n; ++u) {
                for (int v : graph[u]) {
                    if (dp[v][j - 1] != -1 && dp[v][j - 1] + edges[u][2] < t) {
                        dp[u][j] = max(dp[u][j], dp[v][j - 1] + edges[u][2]);
                    }
                }
            }
        }

        int max_sum = -1;
        for (int i = 0; i < n; ++i) {
            max_sum = max(max_sum, dp[i][k]);
        }

        return max_sum;         
    }
};
