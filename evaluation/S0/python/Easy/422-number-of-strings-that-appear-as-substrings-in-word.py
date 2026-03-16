# Source: https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/   |   Difficulty: Easy
#
# Problem Description:
# Given an array of strings patterns and a string word, return the number of strings in patterns that exist as a substring in word.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: patterns = ["a","abc","bc","d"], word = "abc"
# Output: 3
# Explanation:
# - "a" appears as a substring in "abc".
# - "abc" appears as a substring in "abc".
# - "bc" appears as a substring in "abc".
# - "d" does not appear as a substring in "abc".
# 3 of the strings in patterns appear as a substring in word.
#
# Constraints:
# 1 <= patterns.length <= 100
# 	1 <= patterns[i].length <= 100
# 	1 <= word.length <= 100
# 	patterns[i] and word consist of lowercase English letters.
#

class Solution(object):
    def numOfStrings(self, patterns, word):
        """
        :type patterns: List[str]
        :type word: str
        :rtype: int
        """
        count = 0
        for pattern in patterns:
            if pattern in word:
                count += 1
        return count