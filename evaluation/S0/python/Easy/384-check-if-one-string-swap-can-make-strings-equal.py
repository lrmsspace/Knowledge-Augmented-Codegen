# Source: https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/   |   Difficulty: Easy
#
# Problem Description:
# You are given two strings s1 and s2 of equal length. A string swap is an operation where you choose two indices in a string (not necessarily different) and swap the characters at these indices.
#
# Return true if it is possible to make both strings equal by performing at most one string swap on exactly one of the strings. Otherwise, return false.
#
# Example:
# Input: s1 = "bank", s2 = "kanb"
# Output: true
# Explanation: For example, swap the first character with the last character of s2 to make "bank".
#
# Constraints:
# 1 <= s1.length, s2.length <= 100
# 	s1.length == s2.length
# 	s1 and s2 consist of only lowercase English letters.
#

class Solution(object):
    def areAlmostEqual(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        diff = []
        for a, b in zip(s1, s2):
            if a != b:
                diff.append((a, b))
            if len(diff) > 2:
                return False
        if len(diff) == 0:
            return True
        if len(diff) != 2:
            return False
        return diff[0] == diff[1][::-1]