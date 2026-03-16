# Source: https://leetcode.com/problems/find-closest-number-to-zero/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums of size n, return the number with the value closest to 0 in nums. If there are multiple answers, return the number with the largest value.
#
# Example:
# Input: nums = [-4,-2,1,4,8]
# Output: 1
# Explanation:
# The distance from -4 to 0 is |-4| = 4.
# The distance from -2 to 0 is |-2| = 2.
# The distance from 1 to 0 is |1| = 1.
# The distance from 4 to 0 is |4| = 4.
# The distance from 8 to 0 is |8| = 8.
# Thus, the closest number to 0 in the array is 1.
#
# Constraints:
# 1 <= n <= 1000
# 	-105 <= nums[i] <= 105
#

class Solution(object):
    def findClosestNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        closest = nums[0]
        for num in nums:
            if abs(num) < abs(closest) or (abs(num) == abs(closest) and num > closest):
                closest = num
        return closest