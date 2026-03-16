# Source: https://leetcode.com/problems/convert-a-number-to-hexadecimal/   |   Difficulty: Easy
#
# Problem Description:
# Given a 32-bit integer num, return a string representing its hexadecimal representation. For negative integers, two’s complement method is used.
#
# All the letters in the answer string should be lowercase characters, and there should not be any leading zeros in the answer except for the zero itself.
#
# Note: You are not allowed to use any built-in library method to directly solve this problem.
#
# Example:
# Input: num = 26
# Output: "1a"
#
# Constraints:
# -231 <= num <= 231 - 1
#

class Solution(object):
    def toHex(self, num):
        """
        :type num: int
        :rtype: str
        """
        if num == 0:
            return "0"
        
        hex_chars = "0123456789abcdef"
        result = []
        
        # Handle negative numbers using two's complement
        if num < 0:
            num += 2**32
        
        while num > 0:
            remainder = num % 16
            result.append(hex_chars[remainder])
            num //= 16
        
        # The digits are in reverse order, so reverse them before joining
        return ''.join(reversed(result))