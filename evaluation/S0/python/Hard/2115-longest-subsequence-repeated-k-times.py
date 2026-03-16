# Source: https://leetcode.com/problems/longest-subsequence-repeated-k-times/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s of length n, and an integer k. You are tasked to find the longest subsequence repeated k times in string s.
#
# A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
#
# A subsequence seq is repeated k times in the string s if seq * k is a subsequence of s, where seq * k represents a string constructed by concatenating seq k times.
#
#
# 	For example, "bba" is repeated 2 times in the string "bababcba", because the string "bbabba", constructed by concatenating "bba" 2 times, is a subsequence of the string "bababcba".
#
#
# Return the longest subsequence repeated k times in string s. If multiple such subsequences are found, return the lexicographically largest one. If there is no such subsequence, return an empty string.
#
# Example:
# Input: s = "letsleetcode", k = 2
# Output: "let"
# Explanation: There are two longest subsequences repeated 2 times: "let" and "ete".
# "let" is the lexicographically largest one.
#
# Constraints:
# n == s.length
# 	2 <= k <= 2000
# 	2 <= n < min(2001, k * 8)
# 	s consists of lowercase English letters.
#

class Solution(object):
    def longestSubsequenceRepeatedK(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        from collections import Counter
        count = Counter(s)
        chars = [c for c in count if count[c] >= k]
        chars.sort()
        
        res = ""
        
        def backtrack(path):
            nonlocal res
            if len(path) * k > len(s):
                return
            
            if self.is_k_repeated_subsequence(s, path, k):
                if len(path) > len(res) or (len(path) == len(res) and path > res):
                    res = path
            
            for c in chars:
                backtrack(path + c)
        
        backtrack("")
        return res