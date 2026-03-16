# Source: https://leetcode.com/problems/find-the-count-of-monotonic-pairs-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of positive integers nums of length n.
#
# We call a pair of non-negative integer arrays (arr1, arr2) monotonic if:
#
#
# 	The lengths of both arrays are n.
# 	arr1 is monotonically non-decreasing, in other words, arr1[0] <= arr1[1] <= ... <= arr1[n - 1].
# 	arr2 is monotonically non-increasing, in other words, arr2[0] >= arr2[1] >= ... >= arr2[n - 1].
# 	arr1[i] + arr2[i] == nums[i] for all 0 <= i <= n - 1.
#
#
# Return the count of monotonic pairs.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [2,3,2]
#
# Output: 4
#
# Explanation:
#
# The good pairs are:
#
#
# 	([0, 1, 1], [2, 2, 1])
# 	([0, 1, 2], [2, 2, 0])
# 	([0, 2, 2], [2, 1, 0])
# 	([1, 2, 2], [1, 1, 0])
#
# Constraints:
# 1 <= n == nums.length <= 2000
# 	1 <= nums[i] <= 1000
#
# Helpful references (internal KB):
# - Binomial Coefficients (array, enumeration)
#   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
#   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
#   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
#   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
#   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
#   • When to use: Use when you need to perform O(1) range queries on a static array for an associative operation, after an O(N log N) preprocessing step.
#   • Idea: A data structure that precomputes answers for all possible range queries using an associative operation on a static array. It achieves O(1) query time and O(N log N) build time by storing prefix-like sums within logarithmically sized blocks.
#   • Invariants: For each level k, the array is partitioned into 2^k segments.; Within each segment, table[k][j] stores the result of the associative operation from j to the segment's midpoint (or midpoint to j).
#   • Tips: Ensure the operation is associative (e.g., min, max, sum, gcd, bitwise operations).; Preprocessing takes O(N log N) time and space.
#   • Pitfalls: Not suitable for mutable arrays; updates require rebuilding the table.; Requires O(N log N) memory, which can be substantial for very large N.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countOfPairs(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        max_num = max(nums)

        # dp[i][j] will store the number of ways to create a non-decreasing array of length i with sum j
        dp = [[0] * (max_num + 1) for _ in range(n + 1)]
        dp[0][0] = 1

        for i in range(1, n + 1):
            for j in range(max_num + 1):
                dp[i][j] = dp[i - 1][j]
                if j > 0:
                    dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD

        result = 0
        for num in nums:
            for j in range(num + 1):
                result = (result + dp[n][j]) % MOD

        return result