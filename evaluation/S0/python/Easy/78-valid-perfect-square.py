# Source: https://leetcode.com/problems/valid-perfect-square/   |   Difficulty: Easy
#
# Problem Description:
# Given a positive integer num, return true if num is a perfect square or false otherwise.
#
# A perfect square is an integer that is the square of an integer. In other words, it is the product of some integer with itself.
#
# You must not use any built-in library function, such as sqrt.
#
# Example:
# Input: num = 16
# Output: true
# Explanation: We return true because 4 * 4 = 16 and 4 is an integer.
#
# Constraints:
# 1 <= num <= 231 - 1
#

class Solution(object):
    def isPerfectSquare(self, num):
        """
        :type num: int
        :rtype: bool
        """
        left, right = 1, num
        while left <= right:
            mid = left + (right - left) // 2
            square = mid * mid
            if square == num:
                return True
            elif square < num:
                left = mid + 1
            else:
                right = mid - 1
        return False