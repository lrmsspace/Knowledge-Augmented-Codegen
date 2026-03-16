# Source: https://leetcode.com/problems/shortest-palindrome/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s. You can convert s to a palindrome by adding characters in front of it.
#
# Return the shortest palindrome you can find by performing this transformation.
#
# Example:
# Input: s = "aacecaaa"
# Output: "aaacecaaa"
#
# Constraints:
# 0 <= s.length <= 5 * 104
# 	s consists of lowercase English letters only.
#

class Solution(object):
    def shortestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        if not s:
            return s
        
        # Function to find the longest palindromic prefix
        def longest_palindromic_prefix(s):
            rev_s = s[::-1]
            l = s + '#' + rev_s
            p = [0] * len(l)
            
            for i in range(1, len(l)):
                j = p[i - 1]
                while j > 0 and l[i] != l[j]:
                    j = p[j - 1]
                if l[i] == l[j]:
                    j += 1
                p[i] = j
            
            return p[-1]
        
        lp_len = longest_palindromic_prefix(s)
        suffix = s[lp_len:]
        return suffix[::-1] + s