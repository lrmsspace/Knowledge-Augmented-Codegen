# Source: https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/   |   Difficulty: Medium
#
# Problem Description:
# A split of an integer array is good if:
#
#
# 	The array is split into three non-empty contiguous subarrays - named left, mid, right respectively from left to right.
# 	The sum of the elements in left is less than or equal to the sum of the elements in mid, and the sum of the elements in mid is less than or equal to the sum of the elements in right.
#
#
# Given nums, an array of non-negative integers, return the number of good ways to split nums. As the number may be too large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [1,1,1]
# Output: 1
# Explanation: The only good way to split nums is [1] [1] [1].
#
# Constraints:
# 3 <= nums.length <= 105
# 	0 <= nums[i] <= 104
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
# - Fenwick Tree (array, bit-fenwick, prefix-sum)
#   • When to use: When you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It is ideal for scenarios requiring both fast query and update operations on an array.
#   • Idea: A Fenwick tree, or Binary Indexed Tree (BIT), is an array-based data structure that efficiently calculates prefix sums and updates individual elements in an array. It supports both point updates and prefix sum queries in O(log N) time complexity.
#   • Invariants: Each `T[i]` stores the sum of a specific range `[g(i), i]` from the original array.; The `sum(idx)` function correctly aggregates values from `A[0]` to `A[idx]`.
#   • Tips: Understand the bit manipulation (`i & -i`) for navigating parent/child relationships.; Consistently choose and apply either 0-based or 1-based indexing throughout the implementation.
#   • Pitfalls: Incorrectly handling 0-based versus 1-based indexing can lead to off-by-one errors.; Forgetting to initialize the tree or performing updates incorrectly will yield wrong results.
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def waysToSplit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        prefix_sum = [0] * (n + 1)
        
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + nums[i]
        
        result = 0
        
        for i in range(1, n - 1):
            left_sum = prefix_sum[i]
            
            # Binary search for the start of mid subarray
            low, high = i + 1, n - 1
            while low < high:
                mid = (low + high) // 2
                if prefix_sum[mid] - left_sum >= left_sum:
                    high = mid
                else:
                    low = mid + 1
            mid_start = low
            
            # Binary search for the end of mid subarray
            low, high = i + 1, n - 1
            while low < high:
                mid = (low + high + 1) // 2
                if prefix_sum[n] - prefix_sum[mid] >= prefix_sum[mid] - left_sum:
                    low = mid
                else:
                    high = mid - 1
            mid_end = low
            
            if mid_start <= mid_end:
                result = (result + (mid_end - mid_start + 1)) % MOD
        
        return result