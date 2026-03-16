# Source: https://leetcode.com/problems/gray-code/   |   Difficulty: Medium
#
# Problem Description:
# An n-bit gray code sequence is a sequence of 2n integers where:
#
#
# 	Every integer is in the inclusive range [0, 2n - 1],
# 	The first integer is 0,
# 	An integer appears no more than once in the sequence,
# 	The binary representation of every pair of adjacent integers differs by exactly one bit, and
# 	The binary representation of the first and last integers differs by exactly one bit.
#
#
# Given an integer n, return any valid n-bit gray code sequence.
#
# Example:
# Input: n = 2
# Output: [0,1,3,2]
# Explanation:
# The binary representation of [0,1,3,2] is [00,01,11,10].
# - 00 and 01 differ by one bit
# - 01 and 11 differ by one bit
# - 11 and 10 differ by one bit
# - 10 and 00 differ by one bit
# [0,2,3,1] is also a valid gray code sequence, whose binary representation is [00,10,11,01].
# - 00 and 10 differ by one bit
# - 10 and 11 differ by one bit
# - 11 and 01 differ by one bit
# - 01 and 00 differ by one bit
#
# Constraints:
# 1 <= n <= 16
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
    def grayCode(self, n):
        """
        :type n: int
        :rtype: List[int]
        """
        result = []
        for i in range(2**n):
            gray = i ^ (i >> 1)
            result.append(gray)
        return result