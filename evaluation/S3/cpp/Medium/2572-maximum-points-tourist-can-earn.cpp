// Source: https://leetcode.com/problems/maximum-points-tourist-can-earn/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers, n and k, along with two 2D integer arrays, stayScore and travelScore.
//
// A tourist is visiting a country with n cities, where each city is directly connected to every other city. The tourist's journey consists of exactly k 0-indexed days, and they can choose any city as their starting point.
//
// Each day, the tourist has two choices:
//
//
// 	Stay in the current city: If the tourist stays in their current city curr during day i, they will earn stayScore[i][curr] points.
// 	Move to another city: If the tourist moves from their current city curr to city dest, they will earn travelScore[curr][dest] points.
//
//
// Return the maximum possible points the tourist can earn.
//
// Example:
// Input: n = 2, k = 1, stayScore = [[2,3]], travelScore = [[0,2],[1,0]]
//
// Output: 3
//
// Explanation:
//
// The tourist earns the maximum number of points by starting in city 1 and staying in that city.
//
// Constraints:
// 1 <= n <= 200
// 	1 <= k <= 200
// 	n == travelScore.length == travelScore[i].length == stayScore[i].length
// 	k == stayScore.length
// 	1 <= stayScore[i][j] <= 100
// 	0 <= travelScore[i][j] <= 100
// 	travelScore[i][i] == 0
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Sparse Table (array, sparse-table, dp-2d)
//   • When to use: Use when you need to answer range queries, especially Range Minimum/Maximum Queries, on an immutable array very quickly. It is ideal for scenarios where the data does not change and query performance is critical.
//   • Idea: Sparse Table is a data structure that precomputes answers for all range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like Range Minimum/Maximum Queries on a static array, with O(N log N) precomputation.
//   • Invariants: st[k][i] holds the result for the segment starting at index i with length 2^k.; For any k > 0, st[k][i] combines the results of two adjacent segments of length 2^(k-1).
//   • Tips: Precompute log2 values to find the largest power of two in O(1).; Best suited for idempotent operations like minimum, maximum, or GCD.
//   • Pitfalls: Does not support array updates; any modification invalidates the structure.; Inefficient for non-idempotent operations like range sum or XOR in O(1).
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting items, each with a weight and value, to maximize total value within a limited capacity, where each item can be chosen multiple times. It is suitable for problems exhibiting optimal substructure and overlapping subproblems.
//   • Idea: The Knapsack Problem involves selecting items to maximize total value within a fixed capacity. The complete knapsack variant, where items can be taken multiple times, is typically solved using dynamic programming in O(nW) time and O(W) space.
//   • Invariants: For 2D DP `f[i][j]`, it represents the maximum value obtainable using only the first `i` items with a total weight not exceeding `j`.; For 1D DP `dp[j]`, after processing item `i`, it stores the maximum value obtainable with a total weight not exceeding `j`, considering all items up to `i`.
//   • Tips: For the complete knapsack, iterate capacity `j` forwards (from `w_i` to `W`) when using 1D DP to allow multiple selections of the current item.; The 1D DP array `dp[j]` stores the maximum value achievable for exactly capacity `j`.
//   • Pitfalls: Confusing 0-1 knapsack with complete knapsack, especially in the 1D DP iteration direction for capacity.; Incorrectly initializing the DP array, leading to incorrect base cases or propagation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxScore(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore) {
        vector<vector<int>> dp(k + 1, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            dp[0][i] = stayScore[0][i];
        }
        for (int i = 1; i <= k; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[i][j] = stayScore[i][j];
                for (int l = 0; l < n; ++l) {
                    if (l != j) {
                        dp[i][j] = max(dp[i][j], dp[i - 1][l] + travelScore[l][j]);
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, dp[k][i]);
        }
        return ans;         
    }
};
