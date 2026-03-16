# Source: https://leetcode.com/problems/average-value-of-even-numbers-that-are-divisible-by-three/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums of positive integers, return the average value of all even integers that are divisible by 3.
#
# Note that the average of n elements is the sum of the n elements divided by n and rounded down to the nearest integer.
#
# Example:
# Input: nums = [1,3,6,10,12,15]
# Output: 9
# Explanation: 6 and 12 are even numbers that are divisible by 3. (6 + 12) / 2 = 9.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= 1000
#

class Solution(object):
    def averageValue(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        total = 0
        count = 0
        
        for num in nums:
            if num % 2 == 0 and num % 3 == 0:
                total += num
                count += 1
        
        if count == 0:
            return 0
        
        return total // count