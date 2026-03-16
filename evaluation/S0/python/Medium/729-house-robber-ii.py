# Source: https://leetcode.com/problems/house-robber-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.
#
# Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
#
# Example:
# Input: nums = [2,3,2]
# Output: 3
# Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.
#
# Constraints:
# 1 <= nums.length <= 100
# 	0 <= nums[i] <= 1000
#

class Solution(object):
    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) == 1:
            return nums[0]
        
        def rob_linear(houses):
            prev1, prev2 = 0, 0
            for amount in houses:
                temp = prev1
                prev1 = max(prev2 + amount, prev1)
                prev2 = temp
            return prev1
        
        return max(rob_linear(nums[1:]), rob_linear(nums[:-1]))