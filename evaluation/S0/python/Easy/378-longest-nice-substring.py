# Source: https://leetcode.com/problems/longest-nice-substring/   |   Difficulty: Easy
#
# Problem Description:
# A string s is nice if, for every letter of the alphabet that s contains, it appears both in uppercase and lowercase. For example, "abABB" is nice because 'A' and 'a' appear, and 'B' and 'b' appear. However, "abA" is not because 'b' appears, but 'B' does not.
#
# Given a string s, return the longest substring of s that is nice. If there are multiple, return the substring of the earliest occurrence. If there are none, return an empty string.
#
# Example:
# Input: s = "YazaAay"
# Output: "aAa"
# Explanation: "aAa" is a nice string because 'A/a' is the only letter of the alphabet in s, and both 'A' and 'a' appear.
# "aAa" is the longest nice substring.
#
# Constraints:
# 1 <= s.length <= 100
# 	s consists of uppercase and lowercase English letters.
#

class Solution(object):
    def longestNiceSubstring(self, s):
        """
        :type s: str
        :rtype: str
        """
        def is_nice(subs):
            char_set = set(subs)
            for c in char_set:
                if c.islower() and c.upper() not in char_set:
                    return False
                if c.isupper() and c.lower() not in char_set:
                    return False
            return True

        n = len(s)
        max_len = 0
        result = ""

        for i in range(n):
            for j in range(i + 1, n + 1):
                subs = s[i:j]
                if is_nice(subs):
                    if j - i > max_len:
                        max_len = j - i
                        result = subs

        return result