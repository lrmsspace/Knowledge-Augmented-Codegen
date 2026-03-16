# Source: https://leetcode.com/problems/thousand-separator/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer n, add a dot (".") as the thousands separator and return it in string format.
#
# Example:
# Input: n = 987
# Output: "987"
#
# Constraints:
# 0 <= n <= 231 - 1
#

class Solution(object):
    def thousandSeparator(self, n):
        """
        :type n: int
        :rtype: str
        """
        s = str(n)[::-1]
        parts = [s[i:i+3] for i in range(0, len(s), 3)]
        return '.'.join(part[::-1] for part in parts[::-1])