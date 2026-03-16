# Source: https://leetcode.com/problems/non-decreasing-array/   |   Difficulty: Medium
#
# Problem Description:
# Given an array nums with n integers, your task is to check if it could become non-decreasing by modifying at most one element.
#
# We define an array is non-decreasing if nums[i] <= nums[i + 1] holds for every i (0-based) such that (0 <= i <= n - 2).
#
# Example:
# Input: nums = [4,2,3]
# Output: true
# Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
#
# Constraints:
# n == nums.length
# 	1 <= n <= 104
# 	-105 <= nums[i] <= 105
#

class Solution(object):
    def checkPossibility(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        count = 0
        for i in range(1, len(nums)):
            if nums[i] < nums[i - 1]:
                if count == 1:
                    return False
                count += 1
                if i - 2 < 0 or nums[i - 2] <= nums[i]:
                    nums[i - 1] = nums[i]
                else:
                    nums[i] = nums[i - 1]
        return True