# Source: https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers num1 and num2.
#
# In one operation, you can choose integer i in the range [0, 60] and subtract 2i + num2 from num1.
#
# Return the integer denoting the minimum number of operations needed to make num1 equal to 0.
#
# If it is impossible to make num1 equal to 0, return -1.
#
# Example:
# Input: num1 = 3, num2 = -2
# Output: 3
# Explanation: We can make 3 equal to 0 with the following operations:
# - We choose i = 2 and subtract 22 + (-2) from 3, 3 - (4 + (-2)) = 1.
# - We choose i = 2 and subtract 22 + (-2) from 1, 1 - (4 + (-2)) = -1.
# - We choose i = 0 and subtract 20 + (-2) from -1, (-1) - (1 + (-2)) = 0.
# It can be proven, that 3 is the minimum number of operations that we need to perform.
#
# Constraints:
# 1 <= num1 <= 109
#  -109 <= num2 <= 109
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
    def makeTheIntegerZero(self, num1, num2):
        """
        :type num1: int
        :type num2: int
        :rtype: int
        """
        from math import ceil, log2

        if num1 == 0:
            return 0

        for ops in range(1, 61):
            remainder = num1 - ops * num2
            if remainder < ops or remainder < 0:
                continue
            if bin(remainder).count('1') <= ops:
                return ops

        return -1