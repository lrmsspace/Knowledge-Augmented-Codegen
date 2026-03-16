# Source: https://leetcode.com/problems/valid-anagram/   |   Difficulty: Easy
#
# Problem Description:
# Given two strings s and t, return true if t is an anagram of s, and false otherwise.
#
# Example:
# Input: s = "anagram", t = "nagaram"
#
# Output: true
#
# Constraints:
# 1 <= s.length, t.length <= 5 * 104
# 	s and t consist of lowercase English letters.
#
#
#  
# Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
#

class Solution(object):
    def isAnagram(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: bool
        """
        return sorted(s) == sorted(t)