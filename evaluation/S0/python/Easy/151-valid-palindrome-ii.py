# Source: https://leetcode.com/problems/valid-palindrome-ii/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, return true if the s can be palindrome after deleting at most one character from it.
#
# Example:
# Input: s = "aba"
# Output: true
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of lowercase English letters.
#

class Solution(object):
    def validPalindrome(self, s):
        """
        :type s: str
        :rtype: bool
        """
        def is_palindrome_range(i, j):
            return all(s[k] == s[j - k + i] for k in range(i, j // 2 + 1))

        left, right = 0, len(s) - 1
        while left < right:
            if s[left] != s[right]:
                return is_palindrome_range(left + 1, right) or is_palindrome_range(left, right - 1)
            left += 1
            right -= 1
        return True