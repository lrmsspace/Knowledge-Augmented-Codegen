# Source: https://leetcode.com/problems/maximum-ascending-subarray-sum/   |   Difficulty: Easy
#
# Problem Description:
# Given an array of positive integers nums, return the maximum possible sum of an strictly increasing subarray in nums.
#
# A subarray is defined as a contiguous sequence of numbers in an array.
#
# Example:
# Input: nums = [10,20,30,5,10,50]
# Output: 65
# Explanation: [5,10,50] is the ascending subarray with the maximum sum of 65.
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 100
#

class Solution(object):
    def maxAscendingSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_sum = curr_sum = nums[0]
        
        for i in range(1, len(nums)):
            if nums[i] > nums[i - 1]:
                curr_sum += nums[i]
            else:
                curr_sum = nums[i]
            max_sum = max(max_sum, curr_sum)
        
        return max_sum