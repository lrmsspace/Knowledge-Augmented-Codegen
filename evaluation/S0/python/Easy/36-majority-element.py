# Source: https://leetcode.com/problems/majority-element/   |   Difficulty: Easy
#
# Problem Description:
# Given an array nums of size n, return the majority element.
#
# The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
#
# Example:
# Input: nums = [3,2,3]
# Output: 3
#
# Constraints:
# n == nums.length
# 	1 <= n <= 5 * 104
# 	-109 <= nums[i] <= 109
#
#
#  
# Follow-up: Could you solve the problem in linear time and in O(1) space?
#

class Solution(object):
    def majorityElement(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        count = 0
        candidate = None

        for num in nums:
            if count == 0:
                candidate = num
            count += (1 if num == candidate else -1)

        return candidate