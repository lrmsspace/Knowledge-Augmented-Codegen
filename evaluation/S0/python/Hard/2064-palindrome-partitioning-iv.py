# Source: https://leetcode.com/problems/palindrome-partitioning-iv/   |   Difficulty: Hard
#
# Problem Description:
# Given a string s, return true if it is possible to split the string s into three non-empty palindromic substrings. Otherwise, return false.​​​​​
#
# A string is said to be palindrome if it the same string when reversed.
#
# Example:
# Input: s = "abcbdd"
# Output: true
# Explanation: "abcbdd" = "a" + "bcb" + "dd", and all three substrings are palindromes.
#
# Constraints:
# 3 <= s.length <= 2000
# 	s​​​​​​ consists only of lowercase English letters.
#

class Solution(object):
    def checkPartitioning(self, s):
        """
        :type s: str
        :rtype: bool
        """
        n = len(s)
        is_palindrome = [[False] * n for _ in range(n)]
        
        for i in range(n):
            is_palindrome[i][i] = True
        
        for length in range(2, n + 1):
            for start in range(n - length + 1):
                end = start + length - 1
                if s[start] == s[end]:
                    if length == 2:
                        is_palindrome[start][end] = True
                    else:
                        is_palindrome[start][end] = is_palindrome[start + 1][end - 1]
        
        for i in range(1, n - 1):
            for j in range(i, n - 1):
                if is_palindrome[0][i - 1] and is_palindrome[i][j] and is_palindrome[j + 1][n - 1]:
                    return True
        
        return False