# Source: https://leetcode.com/problems/third-maximum-number/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums, return the third distinct maximum number in this array. If the third maximum does not exist, return the maximum number.
#
# Example:
# Input: nums = [3,2,1]
# Output: 1
# Explanation:
# The first distinct maximum is 3.
# The second distinct maximum is 2.
# The third distinct maximum is 1.
#
# Constraints:
# 1 <= nums.length <= 104
# 	-231 <= nums[i] <= 231 - 1
#
#
#  
# Follow up: Can you find an O(n) solution?
#

class Solution(object):
    def thirdMax(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        first = second = third = float('-inf')
        for num in nums:
            if num > first:
                first, second, third = num, first, second
            elif first > num > second:
                second, third = num, second
            elif second > num > third:
                third = num
        return third if third != float('-inf') else first