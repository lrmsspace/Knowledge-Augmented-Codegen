# Source: https://leetcode.com/problems/paint-house-iii/   |   Difficulty: Hard
#
# Problem Description:
# There is a row of m houses in a small city, each house must be painted with one of the n colors (labeled from 1 to n), some houses that have been painted last summer should not be painted again.
#
# A neighborhood is a maximal group of continuous houses that are painted with the same color.
#
#
# 	For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods [{1}, {2,2}, {3,3}, {2}, {1,1}].
#
#
# Given an array houses, an m x n matrix cost and an integer target where:
#
#
# 	houses[i]: is the color of the house i, and 0 if the house is not painted yet.
# 	cost[i][j]: is the cost of paint the house i with the color j + 1.
#
#
# Return the minimum cost of painting all the remaining houses in such a way that there are exactly target neighborhoods. If it is not possible, return -1.
#
# Example:
# Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
# Output: 9
# Explanation: Paint houses of this way [1,2,2,1,1]
# This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
# Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.
#
# Constraints:
# m == houses.length == cost.length
# 	n == cost[i].length
# 	1 <= m <= 100
# 	1 <= n <= 20
# 	1 <= target <= m
# 	0 <= houses[i] <= n
# 	1 <= cost[i][j] <= 104
#
# Helpful references (internal KB):
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
#   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
#   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
#   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
#   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
#   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minCost(self, houses, cost, m, n, target):
        """
        :type houses: List[int]
        :type cost: List[List[int]]
        :type m: int
        :type n: int
        :type target: int
        :rtype: int
        """
        # dp[i][j][k]: the minimum cost to paint first i houses with j neighborhoods, where the i-th house is painted with color k
        dp = [[[float('inf')] * (n + 1) for _ in range(target + 1)] for _ in range(m + 1)]

        # Base case: no houses, no cost, no neighborhoods
        dp[0][0][0] = 0

        for i in range(1, m + 1):
            for j in range(1, target + 1):
                for k in range(1, n + 1):
                    if houses[i - 1] != 0 and houses[i - 1] != k:
                        continue  # Skip if the house is already painted with a different color

                    cost_to_paint = cost[i - 1][k - 1] if houses[i - 1] == 0 else 0

                    # Case when the current house continues the same neighborhood
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k] + cost_to_paint)

                    # Case when the current house starts a new neighborhood
                    for prev_color in range(1, n + 1):
                        if prev_color != k:
                            dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j - 1][prev_color] + cost_to_paint)

        # Find the minimum cost among all colors for exactly target neighborhoods
        min_cost = min(dp[m][target])
        return min_cost if min_cost != float('inf') else -1