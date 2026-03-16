# Source: https://leetcode.com/problems/string-without-aaa-or-bbb/   |   Difficulty: Medium
#
# Problem Description:
# Given two integers a and b, return any string s such that:
#
#
# 	s has length a + b and contains exactly a 'a' letters, and exactly b 'b' letters,
# 	The substring 'aaa' does not occur in s, and
# 	The substring 'bbb' does not occur in s.
#
# Example:
# Input: a = 1, b = 2
# Output: "abb"
# Explanation: "abb", "bab" and "bba" are all correct answers.
#
# Constraints:
# 0 <= a, b <= 100
# 	It is guaranteed such an s exists for the given a and b.
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
    def strWithout3a3b(self, a, b):
        """
        :type a: int
        :type b: int
        :rtype: str
        """
        result = []
        while a > 0 or b > 0:
            if (a > b and (len(result) < 2 or result[-1] != 'a' or result[-2] != 'a')) or (b > 0 and (len(result) >= 2 and result[-1] == 'b' and result[-2] == 'b')):
                result.append('a')
                a -= 1
            else:
                result.append('b')
                b -= 1
        return ''.join(result)