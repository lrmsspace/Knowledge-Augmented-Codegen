# Source: https://leetcode.com/problems/unique-length-3-palindromic-subsequences/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, return the number of unique palindromes of length three that are a subsequence of s.
#
# Note that even if there are multiple ways to obtain the same subsequence, it is still only counted once.
#
# A palindrome is a string that reads the same forwards and backwards.
#
# A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
#
#
# 	For example, "ace" is a subsequence of "abcde".
#
# Example:
# Input: s = "aabca"
# Output: 3
# Explanation: The 3 palindromic subsequences of length 3 are:
# - "aba" (subsequence of "aabca")
# - "aaa" (subsequence of "aabca")
# - "aca" (subsequence of "aabca")
#
# Constraints:
# 3 <= s.length <= 105
# 	s consists of only lowercase English letters.
#

class Solution(object):
    def countPalindromicSubsequence(self, s):
        """
        :type s: str
        :rtype: int
        """
        unique_palindromes = set()
        n = len(s)

        for i in range(n):
            for j in range(i + 1, n):
                if s[i] == s[j]:
                    for k in range(i + 1, j):
                        unique_palindromes.add(s[i] + s[k] + s[j])

        return len(unique_palindromes)