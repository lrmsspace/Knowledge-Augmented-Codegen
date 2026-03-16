# Source: https://leetcode.com/problems/repeated-substring-pattern/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.
#
# Example:
# Input: s = "abab"
# Output: true
# Explanation: It is the substring "ab" twice.
#
# Constraints:
# 1 <= s.length <= 104
# 	s consists of lowercase English letters.
#

class Solution(object):
    def repeatedSubstringPattern(self, s):
        """
        :type s: str
        :rtype: bool
        """
        n = len(s)
        for i in range(1, n // 2 + 1):
            if n % i == 0:
                if s[:i] * (n // i) == s:
                    return True
        return False