# Source: https://leetcode.com/problems/largest-positive-integer-that-exists-with-its-negative/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums that does not contain any zeros, find the largest positive integer k such that -k also exists in the array.
#
# Return the positive integer k. If there is no such integer, return -1.
#
# Example:
# Input: nums = [-1,2,-3,3]
# Output: 3
# Explanation: 3 is the only valid k we can find in the array.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	-1000 <= nums[i] <= 1000
# 	nums[i] != 0
#

class Solution(object):
    def findMaxK(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        num_set = set(nums)
        max_k = -1
        
        for num in nums:
            if num > 0 and -num in num_set:
                max_k = max(max_k, num)
        
        return max_k