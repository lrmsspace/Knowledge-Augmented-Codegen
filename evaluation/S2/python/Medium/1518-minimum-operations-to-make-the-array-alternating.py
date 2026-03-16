# Source: https://leetcode.com/problems/minimum-operations-to-make-the-array-alternating/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array nums consisting of n positive integers.
#
# The array nums is called alternating if:
#
#
# 	nums[i - 2] == nums[i], where 2 <= i <= n - 1.
# 	nums[i - 1] != nums[i], where 1 <= i <= n - 1.
#
#
# In one operation, you can choose an index i and change nums[i] into any positive integer.
#
# Return the minimum number of operations required to make the array alternating.
#
# Example:
# Input: nums = [3,1,3,2,4,3]
# Output: 3
# Explanation:
# One way to make the array alternating is by converting it to [3,1,3,1,3,1].
# The number of operations required in this case is 3.
# It can be proven that it is not possible to make the array alternating in less than 3 operations.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 105
#
# Helpful references (internal KB):
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
# - MEX (minimal excluded) of a sequence (tree, binary-search)
#   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
#   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
#   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
#   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
#   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import Counter

        n = len(nums)
        if n <= 2:
            return 0

        odd_counts = Counter(nums[i] for i in range(1, n, 2))
        even_counts = Counter(nums[i] for i in range(0, n, 2))

        odd_common = odd_counts.most_common(2)
        even_common = even_counts.most_common(2)

        odd_top = odd_common[0] if odd_common else (None, 0)
        even_top = even_common[0] if even_common else (None, 0)

        if odd_top[0] != even_top[0]:
            return n - odd_top[1] - even_top[1]
        else:
            odd_second = odd_common[1] if len(odd_common) > 1 else (None, 0)
            even_second = even_common[1] if len(even_common) > 1 else (None, 0)

            return min(n - odd_top[1] - even_second[1], n - odd_second[1] - even_top[1])