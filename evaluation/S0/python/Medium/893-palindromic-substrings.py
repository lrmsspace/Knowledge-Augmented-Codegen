# Source: https://leetcode.com/problems/palindromic-substrings/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, return the number of palindromic substrings in it.
#
# A string is a palindrome when it reads the same backward as forward.
#
# A substring is a contiguous sequence of characters within the string.
#
# Example:
# Input: s = "abc"
# Output: 3
# Explanation: Three palindromic strings: "a", "b", "c".
#
# Constraints:
# 1 <= s.length <= 1000
# 	s consists of lowercase English letters.
#

class Solution(object):
    def countSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        count = 0
        
        # Function to expand around the center and count palindromes
        def expandAroundCenter(left, right):
            nonlocal count
            while left >= 0 and right < n and s[left] == s[right]:
                count += 1
                left -= 1
                right += 1
        
        for i in range(n):
            # Odd length palindromes
            expandAroundCenter(i, i)
            # Even length palindromes
            expandAroundCenter(i, i + 1)
        
        return count