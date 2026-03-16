# Source: https://leetcode.com/problems/base-7/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer num, return a string of its base 7 representation.
#
# Example:
# Input: num = 100
# Output: "202"
#
# Constraints:
# -107 <= num <= 107
#

class Solution(object):
    def convertToBase7(self, num):
        """
        :type num: int
        :rtype: str
        """
        if num == 0:
            return "0"
        
        negative = num < 0
        num = abs(num)
        digits = []
        
        while num > 0:
            digits.append(str(num % 7))
            num //= 7
        
        if negative:
            digits.append('-')
        
        return ''.join(reversed(digits))