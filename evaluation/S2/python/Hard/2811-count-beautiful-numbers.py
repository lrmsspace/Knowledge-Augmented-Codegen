# Source: https://leetcode.com/problems/count-beautiful-numbers/   |   Difficulty: Hard
#
# Problem Description:
# You are given two positive integers, l and r. A positive integer is called beautiful if the product of its digits is divisible by the sum of its digits.
#
# Return the count of beautiful numbers between l and r, inclusive.
#
# Example:
# Input: l = 10, r = 20
#
# Output: 2
#
# Explanation:
#
# The beautiful numbers in the range are 10 and 20.
#
# Constraints:
# 1 <= l <= r < 109
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
    def beautifulNumbers(self, l, r):
        """
        :type l: int
        :type r: int
        :rtype: int
        """
        def is_beautiful(num):
            s = 0
            p = 1
            for digit in str(num):
                d = int(digit)
                s += d
                p *= d
            return p % s == 0

        count = 0
        for num in range(l, r + 1):
            if is_beautiful(num):
                count += 1

        return count