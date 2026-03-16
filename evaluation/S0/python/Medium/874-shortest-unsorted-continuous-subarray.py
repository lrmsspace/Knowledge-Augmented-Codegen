# Source: https://leetcode.com/problems/shortest-unsorted-continuous-subarray/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, you need to find one continuous subarray such that if you only sort this subarray in non-decreasing order, then the whole array will be sorted in non-decreasing order.
#
# Return the shortest such subarray and output its length.
#
# Example:
# Input: nums = [2,6,4,8,10,9,15]
# Output: 5
# Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
#
# Constraints:
# 1 <= nums.length <= 104
# 	-105 <= nums[i] <= 105
#
#
#  
# Follow up: Can you solve it in O(n) time complexity?
#

class Solution(object):
    def findUnsortedSubarray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        sorted_nums = sorted(nums)
        left, right = 0, len(nums) - 1
        
        while left < len(nums) and nums[left] == sorted_nums[left]:
            left += 1
            
        while right > left and nums[right] == sorted_nums[right]:
            right -= 1
            
        return right - left + 1 if right - left >= 0 else 0