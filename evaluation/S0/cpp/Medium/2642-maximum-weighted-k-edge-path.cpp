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

class Solution {
public:
    int maxWeight(int n, vector<vector<int>>& edges, int k, int t) {
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
        }

        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        dp[0][0] = 0;

        for (int edgeCount = 1; edgeCount <= k; ++edgeCount) {
            for (int u = 0; u < n; ++u) {
                if (dp[u][edgeCount - 1] == -1) continue;
                for (const auto& [v, w] : graph[u]) {
                    int newWeight = dp[u][edgeCount - 1] + w;
                    if (newWeight < t) {
                        dp[v][edgeCount] = max(dp[v][edgeCount], newWeight);
                    }
                }
            }
        }

        int maxWeight = -1;
        for (int u = 0; u < n; ++u) {
            maxWeight = max(maxWeight, dp[u][k]);
        }

        return maxWeight;           
    }
};
