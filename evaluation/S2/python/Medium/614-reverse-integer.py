# Source: https://leetcode.com/problems/reverse-integer/   |   Difficulty: Medium
#
# Problem Description:
# Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.
#
# Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
#
# Example:
# Input: x = 123
# Output: 321
#
# Constraints:
# -231 <= x <= 231 - 1
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
    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        sign = -1 if x < 0 else 1
        x *= sign
        rev = 0
        
        while x:
            rev = rev * 10 + x % 10
            x //= 10
        
        rev *= sign
        
        # Check for overflow
        if rev < -2**31 or rev > 2**31 - 1:
            return 0
        
        return rev