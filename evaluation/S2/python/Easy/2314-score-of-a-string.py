# Source: https://leetcode.com/problems/score-of-a-string/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s. The score of a string is defined as the sum of the absolute difference between the ASCII values of adjacent characters.
#
# Return the score of s.
#
# Example:
# Input: s = "hello"
#
# Output: 13
#
# Explanation:
#
# The ASCII values of the characters in s are: 'h' = 104, 'e' = 101, 'l' = 108, 'o' = 111. So, the score of s would be |104 - 101| + |101 - 108| + |108 - 108| + |108 - 111| = 3 + 7 + 0 + 3 = 13.
#
# Constraints:
# 2 <= s.length <= 100
# 	s consists only of lowercase English letters.
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
    def scoreOfString(self, s):
        """
        :type s: str
        :rtype: int
        """
        score = 0
        for i in range(len(s) - 1):
            score += abs(ord(s[i]) - ord(s[i + 1]))
        return score