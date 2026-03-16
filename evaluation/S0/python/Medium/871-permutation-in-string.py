# Source: https://leetcode.com/problems/permutation-in-string/   |   Difficulty: Medium
#
# Problem Description:
# Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
#
# In other words, return true if one of s1's permutations is the substring of s2.
#
# Example:
# Input: s1 = "ab", s2 = "eidbaooo"
# Output: true
# Explanation: s2 contains one permutation of s1 ("ba").
#
# Constraints:
# 1 <= s1.length, s2.length <= 104
# 	s1 and s2 consist of lowercase English letters.
#

class Solution(object):
    def checkInclusion(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        from collections import Counter

        len_s1 = len(s1)
        count_s1 = Counter(s1)

        for i in range(len(s2) - len_s1 + 1):
            substring = s2[i:i + len_s1]
            count_substring = Counter(substring)

            if count_substring == count_s1:
                return True

        return False