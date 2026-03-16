// Source: https://leetcode.com/problems/paint-house-iii/   |   Difficulty: Hard
//
// Problem Description:
// There is a row of m houses in a small city, each house must be painted with one of the n colors (labeled from 1 to n), some houses that have been painted last summer should not be painted again.
//
// A neighborhood is a maximal group of continuous houses that are painted with the same color.
//
//
// 	For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods [{1}, {2,2}, {3,3}, {2}, {1,1}].
//
//
// Given an array houses, an m x n matrix cost and an integer target where:
//
//
// 	houses[i]: is the color of the house i, and 0 if the house is not painted yet.
// 	cost[i][j]: is the cost of paint the house i with the color j + 1.
//
//
// Return the minimum cost of painting all the remaining houses in such a way that there are exactly target neighborhoods. If it is not possible, return -1.
//
// Example:
// Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
// Output: 9
// Explanation: Paint houses of this way [1,2,2,1,1]
// This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
// Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.
//
// Constraints:
// m == houses.length == cost.length
// 	n == cost[i].length
// 	1 <= m <= 100
// 	1 <= n <= 20
// 	1 <= target <= m
// 	0 <= houses[i] <= n
// 	1 <= cost[i][j] <= 104
//
// Helpful references (internal KB):
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - Finding the nearest pair of points (geometry, array, divide-and-conquer)
//   • When to use: Use this algorithm to efficiently find the pair of points with the minimum Euclidean distance among a given set of N points in a 2D plane. It is particularly effective for large datasets where an O(N^2) approach is too slow.
//   • Idea: This divide-and-conquer algorithm finds the closest pair of points in a 2D plane by recursively splitting the set of points and merging results. It achieves an optimal time complexity of O(N log N).
//   • Invariants: At the start of any recursive call, the input point set is sorted by X-coordinate.; The returned minimum distance 'd' for a subproblem is the true minimum distance among its points.
//   • Tips: Initial sorting by X-coordinate is crucial for efficient division of the point set.; Handle base cases (e.g., 2 or 3 points) with a simple brute-force distance calculation.
//   • Pitfalls: Forgetting to sort points by Y-coordinate within the central strip can degrade performance to O(N^2).; Incorrectly defining the strip width or comparison range in the merge step can lead to incorrect results.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minCost(int[] houses, int[][] cost, int m, int n, int target) {
        final int INF = Integer.MAX_VALUE / 2;
        int[][][] dp = new int[m + 1][n + 1][target + 1];
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= target; k++) {
                    dp[i][j][k] = INF;
                }
            }
        }
        dp[0][0][0] = 0;

        for (int i = 1; i <= m; i++) {
            int houseColor = houses[i - 1];
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= target; k++) {
                    if (houseColor != 0 && houseColor != j) {
                        continue;
                    }
                    int paintCost = (houseColor == 0) ? cost[i - 1][j - 1] : 0;
                    for (int pj = 1; pj <= n; pj++) {
                        if (pj == j) {
                            dp[i][j][k] = Math.min(dp[i][j][k], dp[i - 1][pj][k] + paintCost);
                        } else {
                            dp[i][j][k] = Math.min(dp[i][j][k], dp[i - 1][pj][k - 1] + paintCost);
                        }
                    }
                }
            }
        }

        int minCost = INF;
        for (int j = 1; j <= n; j++) {
            minCost = Math.min(minCost, dp[m][j][target]);
        }

        return (minCost == INF) ? -1 : minCost;         
    }
}
