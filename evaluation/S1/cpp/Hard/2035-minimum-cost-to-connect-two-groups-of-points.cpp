// Source: https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/   |   Difficulty: Hard
//
// Problem Description:
// You are given two groups of points where the first group has size1 points, the second group has size2 points, and size1 >= size2.
//
// The cost of the connection between any two points are given in an size1 x size2 matrix where cost[i][j] is the cost of connecting point i of the first group and point j of the second group. The groups are connected if each point in both groups is connected to one or more points in the opposite group. In other words, each point in the first group must be connected to at least one point in the second group, and each point in the second group must be connected to at least one point in the first group.
//
// Return the minimum cost it takes to connect the two groups.
//
// Example:
// Input: cost = [[15, 96], [36, 2]]
// Output: 17
// Explanation: The optimal way of connecting the groups is:
// 1--A
// 2--B
// This results in a total cost of 17.
//
// Constraints:
// size1 == cost.length
// 	size2 == cost[i].length
// 	1 <= size1, size2 <= 12
// 	size1 >= size2
// 	0 <= cost[i][j] <= 100
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        const int m = cost.size();
        const int n = cost[0].size();
        const int FULL_MASK = (1 << n) - 1;
        vector<int> minCostToConnectSecondGroup(n, INT_MAX);
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                minCostToConnectSecondGroup[j] = min(minCostToConnectSecondGroup[j], cost[i][j]);
            }
        }

        vector<vector<int>> dp(m + 1, vector<int>(1 << n, INT_MAX));
        dp[0][0] = 0;

        for (int i = 0; i < m; ++i) {
            for (int mask = 0; mask <= FULL_MASK; ++mask) {
                if (dp[i][mask] == INT_MAX) continue;

                // Option 1: Connect point i in the first group to all points in the second group
                int newCost = dp[i][mask];
                for (int j = 0; j < n; ++j) {
                    newCost += cost[i][j];
                }
                dp[i + 1][FULL_MASK] = min(dp[i + 1][FULL_MASK], newCost);

                // Option 2: Connect point i in the first group to a subset of points in the second group
                for (int submask = mask; ; submask = (submask - 1) & mask) {
                    int subCost = dp[i][mask];
                    for (int j = 0; j < n; ++j) {
                        if ((submask & (1 << j)) == 0) {
                            subCost += cost[i][j];
                        }
                    }
                    dp[i + 1][submask] = min(dp[i + 1][submask], subCost);
                    if (submask == 0) break;
                }
            }
        }

        int result = INT_MAX;
        for (int mask = 0; mask <= FULL_MASK; ++mask) {
            if (dp[m][mask] == INT_MAX) continue;

            int totalCost = dp[m][mask];
            for (int j = 0; j < n; ++j) {
                if ((mask & (1 << j)) == 0) {
                    totalCost += minCostToConnectSecondGroup[j];
                }
            }
            result = min(result, totalCost);
        }
        return result;
    }
};
