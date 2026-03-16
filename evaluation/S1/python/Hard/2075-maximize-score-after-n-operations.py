# Source: https://leetcode.com/problems/maximize-score-after-n-operations/   |   Difficulty: Hard
#
# Problem Description:
# You are given nums, an array of positive integers of size 2 * n. You must perform n operations on this array.
#
# In the ith operation (1-indexed), you will:
#
#
# 	Choose two elements, x and y.
# 	Receive a score of i * gcd(x, y).
# 	Remove x and y from nums.
#
#
# Return the maximum score you can receive after performing n operations.
#
# The function gcd(x, y) is the greatest common divisor of x and y.
#
# Example:
# Input: nums = [1,2]
# Output: 1
# Explanation: The optimal choice of operations is:
# (1 * gcd(1, 2)) = 1
#
# Constraints:
# 1 <= n <= 7
# 	nums.length == 2 * n
# 	1 <= nums[i] <= 106
#
# Helpful references (internal KB):
# - Euclidean algorithm for computing the greatest common divisor (number, gcd)
#   • When to use: Use this algorithm to efficiently find the greatest common divisor of two or more integers, or as a subroutine for tasks like simplifying fractions or finding the least common multiple.
#   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two non-negative integers by repeatedly applying the division algorithm. It operates in logarithmic time complexity, O(log min(a, b)).
#   • Invariants: The greatest common divisor of the current pair (a, b) remains constant and equal to the GCD of the original inputs.; The second number (b) is always non-negative.
#   • Tips: Handle the base case where one of the numbers is zero; gcd(a, 0) = a.; The algorithm works for any order of inputs; if a < b, the first step swaps them effectively.
#   • Pitfalls: Forgetting to take absolute values if negative inputs are possible, as GCD is typically defined for non-negative integers.; Incorrectly handling the zero input case, which can lead to infinite loops or incorrect results.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Garner's algorithm
#  (number, array, enumeration)
#   • When to use: Use when reconstructing a large integer from a system of congruences with pairwise coprime moduli, offering an alternative to the direct Chinese Remainder Theorem approach.
#   • Idea: Garner's algorithm efficiently reconstructs an integer from its remainders modulo a set of pairwise coprime numbers, by computing its mixed radix representation coefficients. It typically runs in O(k^2 log M) time, where k is the number of moduli and M is the maximum modulus, assuming modular inverse takes log M time.
#   • Invariants: At the start of iteration j, the partial sum $V_{j-1}$ satisfies $V_{j-1} \equiv a_i \pmod{p_i}$ for all $i < j$.; For each iteration j, the coefficient $x_j$ is uniquely determined in the range $[0, p_j - 1]$.
#   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Precompute modular inverses for efficiency, especially if many are needed.
#   • Pitfalls: Incorrectly calculating modular inverses, leading to wrong coefficients.; Not handling large intermediate products, which can cause integer overflow.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxScore(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from math import gcd
        from functools import lru_cache

        n = len(nums) // 2
        nums.sort()

        @lru_cache(None)
        def dfs(mask, op):
            if mask == (1 << 2 * n) - 1:
                return 0

            max_score = 0
            for i in range(2 * n):
                if mask & (1 << i):
                    continue
                for j in range(i + 1, 2 * n):
                    if mask & (1 << j):
                        continue
                    new_mask = mask | (1 << i) | (1 << j)
                    score = op * gcd(nums[i], nums[j]) + dfs(new_mask, op + 1)
                    max_score = max(max_score, score)

            return max_score

        return dfs(0, 1)