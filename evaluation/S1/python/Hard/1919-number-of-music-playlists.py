# Source: https://leetcode.com/problems/number-of-music-playlists/   |   Difficulty: Hard
#
# Problem Description:
# Your music player contains n different songs. You want to listen to goal songs (not necessarily different) during your trip. To avoid boredom, you will create a playlist so that:
#
#
# 	Every song is played at least once.
# 	A song can only be played again only if k other songs have been played.
#
#
# Given n, goal, and k, return the number of possible playlists that you can create. Since the answer can be very large, return it modulo 109 + 7.
#
# Example:
# Input: n = 3, goal = 3, k = 1
# Output: 6
# Explanation: There are 6 possible playlists: [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], and [3, 2, 1].
#
# Constraints:
# 0 <= k < n <= goal <= 100
#
# Helpful references (internal KB):
# - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
#   • When to use: Use when selecting a subset of items, each with a weight and value, to maximize total value without exceeding a given capacity. It is applicable for resource allocation problems with discrete choices.
#   • Idea: The Knapsack Problem aims to choose items with maximum total value such that their total weight does not exceed a given capacity. It is typically solved using dynamic programming, achieving a time complexity of O(nW) for n items and capacity W.
#   • Invariants: `dp[j]` (in 1D DP) represents the maximum value achievable with capacity `j` using items considered so far.; When processing item `i` and capacity `j` (decreasing `j`), `dp[j-weight_i]` holds the value from previous items for that reduced capacity.
#   • Tips: Initialize DP table with zeros for capacity 0 and unreachable states.; For 0-1 knapsack with 1D DP, iterate capacity `j` in decreasing order.
#   • Pitfalls: Incorrect iteration order for 1D DP in 0-1 knapsack (using increasing `j`).; Off-by-one errors in item indices or capacity calculations.
# - Counting labeled graphs (number, dp-2d, counting, recursion)
#   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
#   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
#   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
#   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
#   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numMusicPlaylists(self, n, goal, k):
        """
        :type n: int
        :type goal: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        # dp[i][j] = number of playlists of length i using j unique songs
        dp = [[0] * (n + 1) for _ in range(goal + 1)]
        dp[0][0] = 1

        for i in range(1, goal + 1):
            for j in range(1, min(i, n) + 1):
                # Case 1: Add a new unique song
                dp[i][j] += dp[i - 1][j - 1] * (n - (j - 1))
                # Case 2: Add a previously used song (only if we have at least k other songs)
                if j > k:
                    dp[i][j] += dp[i - 1][j] * (j - k)
                dp[i][j] %= MOD

        return dp[goal][n]  