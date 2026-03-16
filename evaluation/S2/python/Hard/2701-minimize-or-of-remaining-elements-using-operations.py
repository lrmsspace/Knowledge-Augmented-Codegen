# Source: https://leetcode.com/problems/minimize-or-of-remaining-elements-using-operations/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums and an integer k.
#
# In one operation, you can pick any index i of nums such that 0 <= i < nums.length - 1 and replace nums[i] and nums[i + 1] with a single occurrence of nums[i] & nums[i + 1], where & represents the bitwise AND operator.
#
# Return the minimum possible value of the bitwise OR of the remaining elements of nums after applying at most k operations.
#
# Example:
# Input: nums = [3,5,3,2,7], k = 2
# Output: 3
# Explanation: Let's do the following operations:
# 1. Replace nums[0] and nums[1] with (nums[0] & nums[1]) so that nums becomes equal to [1,3,2,7].
# 2. Replace nums[2] and nums[3] with (nums[2] & nums[3]) so that nums becomes equal to [1,3,2].
# The bitwise-or of the final array is 3.
# It can be shown that 3 is the minimum possible value of the bitwise OR of the remaining elements of nums after applying at most k operations.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] < 230
# 	0 <= k < nums.length
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
    def minOrAfterOperations(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        if k >= n - 1:
            return 0  # If we can reduce the array to a single element, the result is 0
        
        # We will use a sliding window of size k + 1 to find the minimum OR
        min_or = float('inf')
        
        for i in range(n - k):
            current_or = 0
            for j in range(i, i + k + 1):
                current_or |= nums[j]
            min_or = min(min_or, current_or)
        
        return min_or