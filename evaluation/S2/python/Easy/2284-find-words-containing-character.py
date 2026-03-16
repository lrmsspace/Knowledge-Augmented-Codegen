# Source: https://leetcode.com/problems/find-words-containing-character/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed array of strings words and a character x.
#
# Return an array of indices representing the words that contain the character x.
#
# Note that the returned array may be in any order.
#
# Example:
# Input: words = ["leet","code"], x = "e"
# Output: [0,1]
# Explanation: "e" occurs in both words: "leet", and "code". Hence, we return indices 0 and 1.
#
# Constraints:
# 1 <= words.length <= 50
# 	1 <= words[i].length <= 50
# 	x is a lowercase English letter.
# 	words[i] consists only of lowercase English letters.
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
    def findWordsContaining(self, words, x):
        """
        :type words: List[str]
        :type x: str
        :rtype: List[int]
        """
        result = []
        for i, word in enumerate(words):
            if x in word:
                result.append(i)
        return result