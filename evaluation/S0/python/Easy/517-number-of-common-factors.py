# Source: https://leetcode.com/problems/number-of-common-factors/   |   Difficulty: Easy
#
# Problem Description:
# Given two positive integers a and b, return the number of common factors of a and b.
#
# An integer x is a common factor of a and b if x divides both a and b.
#
# Example:
# Input: a = 12, b = 6
# Output: 4
# Explanation: The common factors of 12 and 6 are 1, 2, 3, 6.
#
# Constraints:
# 1 <= a, b <= 1000
#

class Solution(object):
    def commonFactors(self, a, b):
        """
        :type a: int
        :type b: int
        :rtype: int
        """
        count = 0
        for i in range(1, min(a, b) + 1):
            if a % i == 0 and b % i == 0:
                count += 1
        return count