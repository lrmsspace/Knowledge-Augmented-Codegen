# Source: https://leetcode.com/problems/longest-happy-prefix/   |   Difficulty: Hard
#
# Problem Description:
# A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).
#
# Given a string s, return the longest happy prefix of s. Return an empty string "" if no such prefix exists.
#
# Example:
# Input: s = "level"
# Output: "l"
# Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".
#
# Constraints:
# 1 <= s.length <= 105
# 	s contains only lowercase English letters.
#

class Solution(object):
    def longestPrefix(self, s):
        """
        :type s: str
        :rtype: str
        """
        n = len(s)
        lps = [0] * n  # Longest Prefix Suffix array
        length = 0  # Length of the previous longest prefix suffix
        i = 1

        while i < n:
            if s[i] == s[length]:
                length += 1
                lps[i] = length
                i += 1
            else:
                if length != 0:
                    length = lps[length - 1]
                else:
                    lps[i] = 0
                    i += 1

        return s[:lps[-1]]