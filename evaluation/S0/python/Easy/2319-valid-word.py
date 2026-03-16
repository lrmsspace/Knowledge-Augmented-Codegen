# Source: https://leetcode.com/problems/valid-word/   |   Difficulty: Easy
#
# Problem Description:
# A word is considered valid if:
#
#
# 	It contains a minimum of 3 characters.
# 	It contains only digits (0-9), and English letters (uppercase and lowercase).
# 	It includes at least one vowel.
# 	It includes at least one consonant.
#
#
# You are given a string word.
#
# Return true if word is valid, otherwise, return false.
#
# Example:
# Input: word = "234Adas"
#
# Output: true
#
# Explanation:
#
# This word satisfies the conditions.
#
# Constraints:
# 1 <= word.length <= 20
# 	word consists of English uppercase and lowercase letters, digits, '@', '#', and '$'.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isValid(self, word):
        """
        :type word: str
        :rtype: bool
        """
        if len(word) < 3:
            return False
        
        has_vowel = False
        has_consonant = False
        
        for char in word:
            if char.isdigit() or char.isalpha():
                if char.lower() in 'aeiou':
                    has_vowel = True
                elif char.isalpha():
                    has_consonant = True
            else:
                return False
        
        return has_vowel and has_consonant