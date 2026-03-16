# Source: https://leetcode.com/problems/sum-of-two-integers/   |   Difficulty: Medium
#
# Problem Description:
# Given two integers a and b, return the sum of the two integers without using the operators + and -.
#
# Example:
# Input: a = 1, b = 2
# Output: 3
#
# Constraints:
# -1000 <= a, b <= 1000
#

class Solution(object):
    def getSum(self, a, b):
        """
        :type a: int
        :type b: int
        :rtype: int
        """
        while b != 0:
            carry = a & b
            a = a ^ b
            b = carry << 1
        return a