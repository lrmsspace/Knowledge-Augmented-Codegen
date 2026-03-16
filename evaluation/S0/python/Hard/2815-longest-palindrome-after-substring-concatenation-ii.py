# Source: https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given two strings, s and t.
#
# You can create a new string by selecting a substring from s (possibly empty) and a substring from t (possibly empty), then concatenating them in order.
#
# Return the length of the longest palindrome that can be formed this way.
#
# Example:
# Input: s = "a", t = "a"
#
# Output: 2
#
# Explanation:
#
# Concatenating "a" from s and "a" from t results in "aa", which is a palindrome of length 2.
#
# Constraints:
# 1 <= s.length, t.length <= 1000
#  s and t consist of lowercase English letters.
#

class Solution(object):
    def longestPalindrome(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: int
        """
        combined = s + t
        n = len(combined)
        max_len = 0

        for center in range(n):
            # Odd length palindromes
            left, right = center, center
            while left >= 0 and right < n and combined[left] == combined[right]:
                if left < len(s) <= right:
                    max_len = max(max_len, right - left + 1)
                left -= 1
                right += 1

            # Even length palindromes
            left, right = center, center + 1
            while left >= 0 and right < n and combined[left] == combined[right]:
                if left < len(s) <= right:
                    max_len = max(max_len, right - left + 1)
                left -= 1
                right += 1

        return max_len