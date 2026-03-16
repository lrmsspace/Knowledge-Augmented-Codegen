# Source: https://leetcode.com/problems/simplified-fractions/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return a list of all simplified fractions between 0 and 1 (exclusive) such that the denominator is less-than-or-equal-to n. You can return the answer in any order.
#
# Example:
# Input: n = 2
# Output: ["1/2"]
# Explanation: "1/2" is the only unique fraction with a denominator less-than-or-equal-to 2.
#
# Constraints:
# 1 <= n <= 100
#

class Solution(object):
    def simplifiedFractions(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        from math import gcd
        result = []
        for denominator in range(2, n + 1):
            for numerator in range(1, denominator):
                if gcd(numerator, denominator) == 1:
                    result.append(f"{numerator}/{denominator}")
        return result