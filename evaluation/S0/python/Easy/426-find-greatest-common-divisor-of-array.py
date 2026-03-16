# Source: https://leetcode.com/problems/find-greatest-common-divisor-of-array/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums, return the greatest common divisor of the smallest number and largest number in nums.
#
# The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.
#
# Example:
# Input: nums = [2,5,6,9,10]
# Output: 2
# Explanation:
# The smallest number in nums is 2.
# The largest number in nums is 10.
# The greatest common divisor of 2 and 10 is 2.
#
# Constraints:
# 2 <= nums.length <= 1000
# 	1 <= nums[i] <= 1000
#

class Solution(object):
    def findGCD(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def gcd(a, b):
            while b:
                a, b = b, a % b
            return a

        min_num = min(nums)
        max_num = max(nums)
        return gcd(min_num, max_num)