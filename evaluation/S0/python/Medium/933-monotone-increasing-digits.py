# Source: https://leetcode.com/problems/monotone-increasing-digits/   |   Difficulty: Medium
#
# Problem Description:
# An integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.
#
# Given an integer n, return the largest number that is less than or equal to n with monotone increasing digits.
#
# Example:
# Input: n = 10
# Output: 9
#
# Constraints:
# 0 <= n <= 109
#

class Solution(object):
    def monotoneIncreasingDigits(self, n):
        """
        :type n: int
        :rtype: int
        """
        digits = list(map(int, str(n)))
        n = len(digits)
        marker = n
        for i in range(n - 1, 0, -1):
            if digits[i] < digits[i - 1]:
                marker = i
                digits[i - 1] -= 1
        for i in range(marker, n):
            digits[i] = 9
        return int(''.join(map(str, digits)))