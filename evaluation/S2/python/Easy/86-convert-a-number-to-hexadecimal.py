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
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def toHex(self, num):
        """
        :type num: int
        :rtype: str
        """
        if num == 0:
            return "0"
        
        hex_chars = "0123456789abcdef"
        hex_string = ""
        
        # Handle negative numbers using two's complement
        if num < 0:
            num += 2 ** 32
        
        while num > 0:
            hex_string = hex_chars[num % 16] + hex_string
            num //= 16
        
        return hex_string