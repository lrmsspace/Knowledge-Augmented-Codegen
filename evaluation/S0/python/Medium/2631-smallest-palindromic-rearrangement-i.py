# Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given a palindromic string s.
#
# Return the lexicographically smallest palindromic permutation of s.
#
# Example:
# Input: s = "z"
#
# Output: "z"
#
# Explanation:
#
# A string of only one character is already the lexicographically smallest palindrome.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of lowercase English letters.
# 	s is guaranteed to be palindromic.
#

class Solution(object):
    def smallestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        from collections import Counter
        count = Counter(s)
        half = []
        
        for char in sorted(count.keys()):
            half.append(char * (count[char] // 2))
        
        half_str = ''.join(half)
        return half_str + half_str[::-1]