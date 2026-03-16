# Source: https://leetcode.com/problems/find-the-maximum-factor-score-of-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
#
# The factor score of an array is defined as the product of the LCM and GCD of all elements of that array.
#
# Return the maximum factor score of nums after removing at most one element from it.
#
# Note that both the LCM and GCD of a single number are the number itself, and the factor score of an empty array is 0.
#
# Example:
# Input: nums = [2,4,8,16]
#
# Output: 64
#
# Explanation:
#
# On removing 2, the GCD of the rest of the elements is 4 while the LCM is 16, which gives a maximum factor score of 4 * 16 = 64.
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 30
#
# Helpful references (internal KB):
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Euclidean algorithm for computing the greatest common divisor (number, gcd)
#   • When to use: Use this algorithm to efficiently find the greatest common divisor of two non-negative integers, or as a subroutine for calculating the least common multiple.
#   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two integers by repeatedly applying the division algorithm. It has a logarithmic time complexity, typically O(log(min(a,b))).
#   • Invariants: The GCD of the current pair (a, b) is always equal to the GCD of the original input numbers.; If a and b are non-negative, then the current values of a and b remain non-negative.
#   • Tips: The GCD of any number and zero is the number itself (e.g., gcd(a, 0) = a).; To calculate LCM, use the formula lcm(a, b) = (a / gcd(a, b)) * b to prevent potential overflow.
#   • Pitfalls: Ensure inputs are non-negative; if negative, take absolute values first.; Be careful with `gcd(0, 0)` definition, which is often undefined or 0.
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
        from functools import reduce

        def lcm(a, b):
            return a * b // gcd(a, b)

        def lcm_multiple(numbers):
            return reduce(lcm, numbers, 1)

        def gcd_multiple(numbers):
            return reduce(gcd, numbers, 0)

        n = len(nums)
        max_factor_score = 0

        for i in range(n):
            remaining_nums = nums[:i] + nums[i+1:]
            if remaining_nums:
                current_gcd = gcd_multiple(remaining_nums)
                current_lcm = lcm_multiple(remaining_nums)
                factor_score = current_gcd * current_lcm
                max_factor_score = max(max_factor_score, factor_score)

        return max_factor_score