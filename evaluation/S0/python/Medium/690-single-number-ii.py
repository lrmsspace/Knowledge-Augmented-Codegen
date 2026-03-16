# Source: https://leetcode.com/problems/single-number-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.
#
# You must implement a solution with a linear runtime complexity and use only constant extra space.
#
# Example:
# Input: nums = [2,2,3,2]
# Output: 3
#
# Constraints:
# 1 <= nums.length <= 3 * 104
# 	-231 <= nums[i] <= 231 - 1
# 	Each element in nums appears exactly three times except for one element which appears once.
#

class Solution(object):
    def singleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        ones, twos = 0, 0
        for num in nums:
            ones = (ones ^ num) & ~twos
            twos = (twos ^ num) & ~ones
        return ones