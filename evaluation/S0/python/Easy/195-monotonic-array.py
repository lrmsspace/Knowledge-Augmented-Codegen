# Source: https://leetcode.com/problems/monotonic-array/   |   Difficulty: Easy
#
# Problem Description:
# An array is monotonic if it is either monotone increasing or monotone decreasing.
#
# An array nums is monotone increasing if for all i <= j, nums[i] <= nums[j]. An array nums is monotone decreasing if for all i <= j, nums[i] >= nums[j].
#
# Given an integer array nums, return true if the given array is monotonic, or false otherwise.
#
# Example:
# Input: nums = [1,2,2,3]
# Output: true
#
# Constraints:
# 1 <= nums.length <= 105
# 	-105 <= nums[i] <= 105
#

class Solution(object):
    def isMonotonic(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        increasing = decreasing = True
        
        for i in range(1, len(nums)):
            if nums[i] > nums[i - 1]:
                decreasing = False
            elif nums[i] < nums[i - 1]:
                increasing = False
            
            if not increasing and not decreasing:
                return False
        
        return True