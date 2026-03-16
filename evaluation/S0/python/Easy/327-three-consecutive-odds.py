# Source: https://leetcode.com/problems/three-consecutive-odds/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array arr, return true if there are three consecutive odd numbers in the array. Otherwise, return false.
#
# Example:
# Input: arr = [2,6,4,1]
# Output: false
# Explanation: There are no three consecutive odds.
#
# Constraints:
# 1 <= arr.length <= 1000
# 	1 <= arr[i] <= 1000
#

class Solution(object):
    def threeConsecutiveOdds(self, arr):
        """
        :type arr: List[int]
        :rtype: bool
        """
        count = 0
        for num in arr:
            if num % 2 == 1:
                count += 1
                if count == 3:
                    return True
            else:
                count = 0
        return False