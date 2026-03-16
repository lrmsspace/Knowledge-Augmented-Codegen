# Source: https://leetcode.com/problems/arithmetic-slices/   |   Difficulty: Medium
#
# Problem Description:
# An integer array is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
#
#
# 	For example, [1,3,5,7,9], [7,7,7,7], and [3,-1,-5,-9] are arithmetic sequences.
#
#
# Given an integer array nums, return the number of arithmetic subarrays of nums.
#
# A subarray is a contiguous subsequence of the array.
#
# Example:
# Input: nums = [1,2,3,4]
# Output: 3
# Explanation: We have 3 arithmetic slices in nums: [1, 2, 3], [2, 3, 4] and [1,2,3,4] itself.
#
# Constraints:
# 1 <= nums.length <= 5000
# 	-1000 <= nums[i] <= 1000
#

class Solution(object):
    def numberOfArithmeticSlices(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        if n < 3:
            return 0
        
        total_slices = 0
        current_slices = 0
        
        for i in range(2, n):
            if nums[i] - nums[i-1] == nums[i-1] - nums[i-2]:
                current_slices += 1
                total_slices += current_slices
            else:
                current_slices = 0
        
        return total_slices