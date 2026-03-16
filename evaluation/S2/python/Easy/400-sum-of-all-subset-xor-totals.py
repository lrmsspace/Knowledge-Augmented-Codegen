# Source: https://leetcode.com/problems/sum-of-all-subset-xor-totals/   |   Difficulty: Easy
#
# Problem Description:
# The XOR total of an array is defined as the bitwise XOR of all its elements, or 0 if the array is empty.
#
#
# 	For example, the XOR total of the array [2,5,6] is 2 XOR 5 XOR 6 = 1.
#
#
# Given an array nums, return the sum of all XOR totals for every subset of nums. 
#
# Note: Subsets with the same elements should be counted multiple times.
#
# An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b.
#
# Example:
# Input: nums = [1,3]
# Output: 6
# Explanation: The 4 subsets of [1,3] are:
# - The empty subset has an XOR total of 0.
# - [1] has an XOR total of 1.
# - [3] has an XOR total of 3.
# - [1,3] has an XOR total of 1 XOR 3 = 2.
# 0 + 1 + 3 + 2 = 6
#
# Constraints:
# 1 <= nums.length <= 12
# 	1 <= nums[i] <= 20
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def subsetXORSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        total_sum = 0
        n = len(nums)

        # There are 2^n subsets for an array of size n
        for i in range(1 << n):
            subset_xor = 0
            for j in range(n):
                # Check if the j-th element is included in the current subset
                if (i & (1 << j)) > 0:
                    subset_xor ^= nums[j]
            total_sum += subset_xor

        return total_sum