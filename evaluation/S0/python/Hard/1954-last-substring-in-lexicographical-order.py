# Source: https://leetcode.com/problems/last-substring-in-lexicographical-order/   |   Difficulty: Hard
#
# Problem Description:
# Given a string s, return the last substring of s in lexicographical order.
#
# Example:
# Input: s = "abab"
# Output: "bab"
# Explanation: The substrings are ["a", "ab", "aba", "abab", "b", "ba", "bab"]. The lexicographically maximum substring is "bab".
#
# Constraints:
# 1 <= s.length <= 4 * 105
# 	s contains only lowercase English letters.
#

class Solution(object):
    def lastSubstring(self, s):
        """
        :type s: str
        :rtype: str
        """
        n = len(s)
        i, j, k = 0, 1, 0
        while j + k < n:
            if s[i + k] == s[j + k]:
                k += 1
            elif s[i + k] > s[j + k]:
                j = j + k + 1
                k = 0
            else:
                i, j = max(i + k + 1, j), i
                k = 0
        return s[i:]