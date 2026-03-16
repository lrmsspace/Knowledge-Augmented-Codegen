# Source: https://leetcode.com/problems/to-lower-case/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, return the string after replacing every uppercase letter with the same lowercase letter.
#
# Example:
# Input: s = "Hello"
# Output: "hello"
#
# Constraints:
# 1 <= s.length <= 100
# 	s consists of printable ASCII characters.
#

class Solution(object):
    def toLowerCase(self, s):
        """
        :type s: str
        :rtype: str
        """
        return s.lower()