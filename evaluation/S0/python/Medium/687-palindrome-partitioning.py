# Source: https://leetcode.com/problems/palindrome-partitioning/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.
#
# Example:
# Input: s = "aab"
# Output: [["a","a","b"],["aa","b"]]
#
# Constraints:
# 1 <= s.length <= 16
# 	s contains only lowercase English letters.
#

class Solution(object):
    def partition(self, s):
        """
        :type s: str
        :rtype: List[List[str]]
        """
        res = []
        
        def is_palindrome(sub):
            return sub == sub[::-1]
        
        def backtrack(start, path):
            if start == len(s):
                res.append(path[:])
                return
            
            for end in range(start + 1, len(s) + 1):
                substring = s[start:end]
                if is_palindrome(substring):
                    path.append(substring)
                    backtrack(end, path)
                    path.pop()
        
        backtrack(0, [])
        return res