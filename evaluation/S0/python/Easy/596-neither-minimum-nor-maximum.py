# Source: https://leetcode.com/problems/neither-minimum-nor-maximum/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums containing distinct positive integers, find and return any number from the array that is neither the minimum nor the maximum value in the array, or -1 if there is no such number.
#
# Return the selected integer.
#
# Example:
# Input: nums = [3,2,1,4]
# Output: 2
# Explanation: In this example, the minimum value is 1 and the maximum value is 4. Therefore, either 2 or 3 can be valid answers.
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 100
# 	All values in nums are distinct
#

class Solution(object):
    def findNonMinOrMax(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) <= 2:
            return -1
        
        nums.sort()
        return nums[1]