# Source: https://leetcode.com/problems/longest-palindromic-substring/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, return the longest palindromic substring in s.
#
# Example:
# Input: s = "babad"
# Output: "bab"
# Explanation: "aba" is also a valid answer.
#
# Constraints:
# 1 <= s.length <= 1000
# 	s consist of only digits and English letters.
#

class Solution(object):
    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        def expand_around_center(left, right):
            while left >= 0 and right < len(s) and s[left] == s[right]:
                left -= 1
                right += 1
            return right - left - 1

        start, end = 0, 0
        for i in range(len(s)):
            len1 = expand_around_center(i, i)      # Odd length palindromes
            len2 = expand_around_center(i, i + 1)  # Even length palindromes
            max_len = max(len1, len2)
            if max_len > end - start:
                start = i - (max_len - 1) // 2
                end = i + max_len // 2

        return s[start:end + 1]