# Source: https://leetcode.com/problems/first-unique-character-in-a-string/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.
#
# Example:
# Input: s = "leetcode"
#
# Output: 0
#
# Explanation:
#
# The character 'l' at index 0 is the first character that does not occur at any other index.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of only lowercase English letters.
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
    def firstUniqChar(self, s):
        """
        :type s: str
        :rtype: int
        """
        char_count = {}
        
        # Count the occurrences of each character
        for char in s:
            if char in char_count:
                char_count[char] += 1
            else:
                char_count[char] = 1
        
        # Find the index of the first unique character
        for index, char in enumerate(s):
            if char_count[char] == 1:
                return index
        
        return -1