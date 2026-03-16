                                                # Source: https://leetcode.com/problems/get-equal-substrings-within-budget/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings s and t of the same length and an integer maxCost.
#
# You want to change s to t. Changing the ith character of s to ith character of t costs |s[i] - t[i]| (i.e., the absolute difference between the ASCII values of the characters).
#
# Return the maximum length of a substring of s that can be changed to be the same as the corresponding substring of t with a cost less than or equal to maxCost. If there is no substring from s that can be changed to its corresponding substring from t, return 0.
#
# Example:
# Input: s = "abcd", t = "bcdf", maxCost = 3
# Output: 3
# Explanation: "abc" of s can change to "bcd".
# That costs 3, so the maximum length is 3.
#
# Constraints:
# 1 <= s.length <= 105
# 	t.length == s.length
# 	0 <= maxCost <= 106
# 	s and t consist of only lowercase English letters.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def equalSubstring(self, s, t, maxCost):
        """
        :type s: str
        :type t: str
        :type maxCost: int
        :rtype: int
        """         
        left = 0
        current_cost = 0
        max_length = 0
        
        for right in range(len(s)):
            current_cost += abs(ord(s[right]) - ord(t[right]))
            
            while current_cost > maxCost:
                current_cost -= abs(ord(s[left]) - ord(t[left]))
                left += 1
            
            max_length = max(max_length, right - left + 1)
        
        return max_length