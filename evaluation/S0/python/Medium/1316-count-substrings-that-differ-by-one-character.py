# Source: https://leetcode.com/problems/count-substrings-that-differ-by-one-character/   |   Difficulty: Medium
#
# Problem Description:
# Given two strings s and t, find the number of ways you can choose a non-empty substring of s and replace a single character by a different character such that the resulting substring is a substring of t. In other words, find the number of substrings in s that differ from some substring in t by exactly one character.
#
# For example, the underlined substrings in "computer" and "computation" only differ by the 'e'/'a', so this is a valid way.
#
# Return the number of substrings that satisfy the condition above.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: s = "aba", t = "baba"
# Output: 6
# Explanation: The following are the pairs of substrings from s and t that differ by exactly 1 character:
# ("aba", "baba")
# ("aba", "baba")
# ("aba", "baba")
# ("aba", "baba")
# ("aba", "baba")
# ("aba", "baba")
# The underlined portions are the substrings that are chosen from s and t.
#
# ​​Example 2:
#
#
# Input: s = "ab", t = "bb"
# Output: 3
# Explanation: The following are the pairs of substrings from s and t that differ by 1 character:
# ("ab", "bb")
# ("ab", "bb")
# ("ab", "bb")
# ​​​​The underlined portions are the substrings that are chosen from s and t.
#
# Constraints:
# 1 <= s.length, t.length <= 100
# 	s and t consist of lowercase English letters only.
#

class Solution(object):
    def countSubstrings(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: int
        """
        count = 0
        len_s, len_t = len(s), len(t)
        
        for i in range(len_s):
            for j in range(len_t):
                diff = 0
                k = 0
                
                while i + k < len_s and j + k < len_t:
                    if s[i + k] != t[j + k]:
                        diff += 1
                    
                    if diff == 1:
                        count += 1
                    elif diff > 1:
                        break
                    
                    k += 1
        
        return count