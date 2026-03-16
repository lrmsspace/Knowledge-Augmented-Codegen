# Source: https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s consisting only of characters 'a' and 'b'​​​​.
#
# You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.
#
# Return the minimum number of deletions needed to make s balanced.
#
# Example:
# Input: s = "aababbab"
# Output: 2
# Explanation: You can either:
# Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
# Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is 'a' or 'b'​​.
#

class Solution(object):
    def minimumDeletions(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        prefix_b = [0] * (n + 1)
        
        for i in range(1, n + 1):
            prefix_b[i] = prefix_b[i - 1] + (1 if s[i - 1] == 'b' else 0)
        
        min_deletions = float('inf')
        
        for i in range(n + 1):
            deletions = prefix_b[i] + (s[i:].count('a') if i < n else 0)
            min_deletions = min(min_deletions, deletions)
        
        return min_deletions