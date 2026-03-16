# Source: https://leetcode.com/problems/sum-multiples/   |   Difficulty: Easy
#
# Problem Description:
# Given a positive integer n, find the sum of all integers in the range [1, n] inclusive that are divisible by 3, 5, or 7.
#
# Return an integer denoting the sum of all numbers in the given range satisfying the constraint.
#
# Example:
# Input: n = 7
# Output: 21
# Explanation: Numbers in the range [1, 7] that are divisible by 3, 5, or 7 are 3, 5, 6, 7. The sum of these numbers is 21.
#
# Constraints:
# 1 <= n <= 103
#

class Solution(object):
    def sumOfMultiples(self, n):
        """
        :type n: int
        :rtype: int
        """
        total = 0
        for i in range(1, n + 1):
            if i % 3 == 0 or i % 5 == 0 or i % 7 == 0:
                total += i
        return total