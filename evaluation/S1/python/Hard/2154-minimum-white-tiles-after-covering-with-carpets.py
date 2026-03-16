# Source: https://leetcode.com/problems/minimum-white-tiles-after-covering-with-carpets/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed binary string floor, which represents the colors of tiles on a floor:
#
#
# 	floor[i] = '0' denotes that the ith tile of the floor is colored black.
# 	On the other hand, floor[i] = '1' denotes that the ith tile of the floor is colored white.
#
#
# You are also given numCarpets and carpetLen. You have numCarpets black carpets, each of length carpetLen tiles. Cover the tiles with the given carpets such that the number of white tiles still visible is minimum. Carpets may overlap one another.
#
# Return the minimum number of white tiles still visible.
#
# Example:
# Input: floor = "10110101", numCarpets = 2, carpetLen = 2
# Output: 2
# Explanation: 
# The figure above shows one way of covering the tiles with the carpets such that only 2 white tiles are visible.
# No other way of covering the tiles with the carpets can leave less than 2 white tiles visible.
#
# Constraints:
# 1 <= carpetLen <= floor.length <= 1000
# 	floor[i] is either '0' or '1'.
# 	1 <= numCarpets <= 1000
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
#   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
#   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
#   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
#   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
#   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumWhiteTiles(self, floor, numCarpets, carpetLen):
        """
        :type floor: str
        :type numCarpets: int
        :type carpetLen: int
        :rtype: int
        """
        n = len(floor)
        # Precompute the prefix sum of white tiles
        prefix_white = [0] * (n + 1)
        for i in range(1, n + 1):
            prefix_white[i] = prefix_white[i - 1] + (1 if floor[i - 1] == '1' else 0)
        # Initialize DP table
        dp = [[float('inf')] * (numCarpets + 1) for _ in range(n + 1)]
        dp[0][0] = 0  # Base case: no tiles, no
        for i in range(1, n + 1):
            for j in range(numCarpets + 1):
                # Option 1: Do not use a carpet on the ith tile
                dp[i][j] = dp[i - 1][j] + (1 if floor[i - 1] == '1' else 0)
                # Option 2: Use a carpet ending at the ith tile (if we have carpets left)
                if j > 0:
                    start = max(0, i - carpetLen)
                    dp[i][j] = min(dp[i][j], dp[start][j - 1])
        return dp[n][numCarpets]    