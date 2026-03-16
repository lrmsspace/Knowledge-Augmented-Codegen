# Source: https://leetcode.com/problems/substring-matching-pattern/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s and a pattern string p, where p contains exactly one '*' character.
#
# The '*' in p can be replaced with any sequence of zero or more characters.
#
# Return true if p can be made a substring of s, and false otherwise.
#
# Example:
# Input: s = "leetcode", p = "ee*e"
#
# Output: true
#
# Explanation:
#
# By replacing the '*' with "tcod", the substring "eetcode" matches the pattern.
#
# Constraints:
# 1 <= s.length <= 50
# 	1 <= p.length <= 50 
# 	s contains only lowercase English letters.
# 	p contains only lowercase English letters and exactly one '*'
#

class Solution(object):
    def hasMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        star_index = p.index('*')
        prefix = p[:star_index]
        suffix = p[star_index + 1:]

        # Check if s is long enough to contain both prefix and suffix
        if len(s) < len(prefix) + len(suffix):
            return False

        # Check if s starts with the prefix
        if not s.startswith(prefix):
            return False

        # Check if s ends with the suffix
        if not s.endswith(suffix):
            return False

        return True