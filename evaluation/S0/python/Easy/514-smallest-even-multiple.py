# Source: https://leetcode.com/problems/smallest-even-multiple/   |   Difficulty: Easy
#
# Problem Description:
# Given a positive integer n, return the smallest positive integer that is a multiple of both 2 and n.
#
# Example:
# Input: n = 5
# Output: 10
# Explanation: The smallest multiple of both 5 and 2 is 10.
#
# Constraints:
# 1 <= n <= 150
#

class Solution(object):
    def smallestEvenMultiple(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n % 2 == 0:
            return n
        else:
            return n * 2