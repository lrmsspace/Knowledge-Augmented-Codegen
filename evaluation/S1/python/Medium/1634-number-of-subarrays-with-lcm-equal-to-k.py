# Source: https://leetcode.com/problems/number-of-subarrays-with-lcm-equal-to-k/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums and an integer k, return the number of subarrays of nums where the least common multiple of the subarray's elements is k.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# The least common multiple of an array is the smallest positive integer that is divisible by all the array elements.
#
# Example:
# Input: nums = [3,6,2,7,1], k = 6
# Output: 4
# Explanation: The subarrays of nums where 6 is the least common multiple of all the subarray's elements are:
# - [3,6,2,7,1]
# - [3,6,2,7,1]
# - [3,6,2,7,1]
# - [3,6,2,7,1]
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i], k <= 1000
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
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
    def subarrayLCM(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from math import gcd
        def lcm(a, b):
            return a * b // gcd(a, b)

        count = 0
        n = len(nums)

        for i in range(n):
            current_lcm = nums[i]
            for j in range(i, n):
                current_lcm = lcm(current_lcm, nums[j])
                if current_lcm == k:
                    count += 1
                if current_lcm > k:
                    break

        return count