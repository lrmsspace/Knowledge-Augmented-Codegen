# Source: https://leetcode.com/problems/string-matching-in-an-array/   |   Difficulty: Easy
#
# Problem Description:
# Given an array of string words, return all strings in words that are a substring of another word. You can return the answer in any order.
#
# Example:
# Input: words = ["mass","as","hero","superhero"]
# Output: ["as","hero"]
# Explanation: "as" is substring of "mass" and "hero" is substring of "superhero".
# ["hero","as"] is also a valid answer.
#
# Constraints:
# 1 <= words.length <= 100
# 	1 <= words[i].length <= 30
# 	words[i] contains only lowercase English letters.
# 	All the strings of words are unique.
#

class Solution(object):
    def stringMatching(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        res = []
        n = len(words)
        for i in range(n):
            for j in range(n):
                if i != j and words[i] in words[j]:
                    res.append(words[i])
                    break
        return res