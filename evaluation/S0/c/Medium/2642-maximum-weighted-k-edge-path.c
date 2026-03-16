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

int maxWeight(int n, int** edges, int edgesSize, int* edgesColSize, int k, int t) {
    int dp[301][301][601];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int l = 0; l <= t; l++) {
                dp[i][j][l] = -1;
            }
        }
    }
    dp[0][0][0] = 0;

    for (int e = 0; e < edgesSize; e++) {
        int u = edges[e][0];
        int v = edges[e][1];
        int w = edges[e][2];
        for (int j = k - 1; j >= 0; j--) {
            for (int l = 0; l <= t - w - 1; l++) {
                if (dp[u][j][l] != -1) {
                    int newWeight = dp[u][j][l] + w;
                    if (newWeight < t) {
                        if (dp[v][j + 1][newWeight] < newWeight) {
                            dp[v][j + 1][newWeight] = newWeight;
                        }
                    }
                }
            }
        }
    }

    int maxWeight = -1;
    for (int i = 0; i < n; i++) {
        for (int l = 0; l < t; l++) {
            if (dp[i][k][l] > maxWeight) {
                maxWeight = dp[i][k][l];
            }
        }
    }

    return maxWeight;       
}
