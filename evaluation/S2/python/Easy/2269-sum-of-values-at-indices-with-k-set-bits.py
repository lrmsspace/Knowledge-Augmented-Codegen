# Source: https://leetcode.com/problems/sum-of-values-at-indices-with-k-set-bits/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed integer array nums and an integer k.
#
# Return an integer that denotes the sum of elements in nums whose corresponding indices have exactly k set bits in their binary representation.
#
# The set bits in an integer are the 1's present when it is written in binary.
#
#
# 	For example, the binary representation of 21 is 10101, which has 3 set bits.
#
# Example:
# Input: nums = [5,10,1,5,2], k = 1
# Output: 13
# Explanation: The binary representation of the indices are: 
# 0 = 0002
# 1 = 0012
# 2 = 0102
# 3 = 0112
# 4 = 1002 
# Indices 1, 2, and 4 have k = 1 set bits in their binary representation.
# Hence, the answer is nums[1] + nums[2] + nums[4] = 13.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= 105
# 	0 <= k <= 10
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
    def sumIndicesWithKSetBits(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        total_sum = 0
        
        for i in range(len(nums)):
            if bin(i).count('1') == k:
                total_sum += nums[i]
        
        return total_sum