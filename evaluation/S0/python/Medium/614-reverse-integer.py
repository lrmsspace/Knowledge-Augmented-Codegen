# Source: https://leetcode.com/problems/reverse-integer/   |   Difficulty: Medium
#
# Problem Description:
# Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.
#
# Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
#
# Example:
# Input: x = 123
# Output: 321
#
# Constraints:
# -231 <= x <= 231 - 1
#

class Solution(object):
    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        INT_MIN, INT_MAX = -2**31, 2**31 - 1
        sign = -1 if x < 0 else 1
        x_abs = abs(x)
        reversed_x = 0

        while x_abs != 0:
            digit = x_abs % 10
            x_abs //= 10

            # Check for overflow
            if (reversed_x > INT_MAX // 10) or (reversed_x == INT_MAX // 10 and digit > INT_MAX % 10):
                return 0

            reversed_x = reversed_x * 10 + digit

        return sign * reversed_x