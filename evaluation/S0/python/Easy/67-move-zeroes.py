# Source: https://leetcode.com/problems/move-zeroes/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
#
# Note that you must do this in-place without making a copy of the array.
#
# Example:
# Input: nums = [0,1,0,3,12]
# Output: [1,3,12,0,0]
#
# Constraints:
# 1 <= nums.length <= 104
# 	-231 <= nums[i] <= 231 - 1
#
#
#  
# Follow up: Could you minimize the total number of operations done?
#

class Solution(object):
    def moveZeroes(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        last_non_zero_found_at = 0
        
        for current in range(len(nums)):
            if nums[current] != 0:
                nums[last_non_zero_found_at], nums[current] = nums[current], nums[last_non_zero_found_at]
                last_non_zero_found_at += 1
        return nums