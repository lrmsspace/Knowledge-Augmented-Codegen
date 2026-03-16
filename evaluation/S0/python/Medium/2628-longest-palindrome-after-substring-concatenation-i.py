# Source: https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-i/   |   Difficulty: Medium
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
# 1 <= s.length, t.length <= 30
# 	s and t consist of lowercase English letters.
#

class Solution(object):
    def longestPalindrome(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: int
        """
        max_len = 0
        n, m = len(s), len(t)

        # Helper function to expand around center and find palindrome length
        def expand_around_center(left, right):
            while left >= 0 and right < n + m:
                if left < n and right >= n:
                    if s[left] != t[right - n]:
                        break
                elif left < n:
                    if s[left] != s[right]:
                        break
                else:
                    if t[left - n] != t[right - n]:
                        break
                left -= 1
                right += 1
            return right - left - 1

        # Check all possible centers for palindromes
        for i in range(n + m):
            len1 = expand_around_center(i, i)      # Odd length palindromes
            len2 = expand_around_center(i, i + 1)  # Even length palindromes
            max_len = max(max_len, len1, len2)

        return max_len