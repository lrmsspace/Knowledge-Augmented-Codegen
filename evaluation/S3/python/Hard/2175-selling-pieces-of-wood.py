# Source: https://leetcode.com/problems/selling-pieces-of-wood/   |   Difficulty: Hard
#
# Problem Description:
# You are given two integers m and n that represent the height and width of a rectangular piece of wood. You are also given a 2D integer array prices, where prices[i] = [hi, wi, pricei] indicates you can sell a rectangular piece of wood of height hi and width wi for pricei dollars.
#
# To cut a piece of wood, you must make a vertical or horizontal cut across the entire height or width of the piece to split it into two smaller pieces. After cutting a piece of wood into some number of smaller pieces, you can sell pieces according to prices. You may sell multiple pieces of the same shape, and you do not have to sell all the shapes. The grain of the wood makes a difference, so you cannot rotate a piece to swap its height and width.
#
# Return the maximum money you can earn after cutting an m x n piece of wood.
#
# Note that you can cut the piece of wood as many times as you want.
#
# Example:
# Input: m = 3, n = 5, prices = [[1,4,2],[2,2,7],[2,1,3]]
# Output: 19
# Explanation: The diagram above shows a possible scenario. It consists of:
# - 2 pieces of wood shaped 2 x 2, selling for a price of 2 * 7 = 14.
# - 1 piece of wood shaped 2 x 1, selling for a price of 1 * 3 = 3.
# - 1 piece of wood shaped 1 x 4, selling for a price of 1 * 2 = 2.
# This obtains a total of 14 + 3 + 2 = 19 money earned.
# It can be shown that 19 is the maximum amount of money that can be earned.
#
# Constraints:
# 1 <= m, n <= 200
# 	1 <= prices.length <= 2 * 104
# 	prices[i].length == 3
# 	1 <= hi <= m
# 	1 <= wi <= n
# 	1 <= pricei <= 106
# 	All the shapes of wood (hi, wi) are pairwise distinct.
#
# Helpful references (internal KB):
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Knapsack Problem (array, knapsack, dp-1d, enumeration)
#   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
#   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
#   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
#   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
#   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def sellingWood(self, m, n, prices):
        """
        :type m: int
        :type n: int
        :type prices: List[List[int]]
        :rtype: int
        """
        # Step 1: Create a price map for quick lookup
        price_map = {(h, w): p for h, w, p in prices}
        
        # Step 2: Initialize a DP table
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        
        # Step 3: Fill the DP table
        for height in range(1, m + 1):
            for width in range(1, n + 1):
                # Check if we can sell this piece directly
                if (height, width) in price_map:
                    dp[height][width] = price_map[(height, width)]
                
                # Try cutting horizontally
                for cut in range(1, height):
                    dp[height][width] = max(dp[height][width], dp[cut][width] + dp[height - cut][width])
                
                # Try cutting vertically
                for cut in range(1, width):
                    dp[height][width] = max(dp[height][width], dp[height][cut] + dp[height][width - cut])
        
        return dp[m][n]