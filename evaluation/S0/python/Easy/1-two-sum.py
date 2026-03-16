# Source: https://leetcode.com/problems/two-sum/   |   Difficulty: Easy
#
# Problem Description:
# Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
#
# You may assume that each input would have exactly one solution, and you may not use the same element twice.
#
# You can return the answer in any order.
#
# Example:
# Input: nums = [2,7,11,15], target = 9
# Output: [0,1]
# Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
#
# Constraints:
# 2 <= nums.length <= 104
# 	-109 <= nums[i] <= 109
# 	-109 <= target <= 109
# 	Only one valid answer exists.
#
#
#  
# Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
#

class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        num_map = {}
        for i, num in enumerate(nums):
            complement = target - num
            if complement in num_map:
                return [num_map[complement], i]
            num_map[num] = i
        return [] # Just in case there is no solution       
