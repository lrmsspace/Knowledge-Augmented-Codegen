# Source: https://leetcode.com/problems/palindrome-pairs/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed array of unique strings words.
#
# A palindrome pair is a pair of integers (i, j) such that:
#
#
#  0 <= i, j < words.length,
#  i != j, and
#  words[i] + words[j] (the concatenation of the two strings) is a palindrome.
#
#
# Return an array of all the palindrome pairs of words.
#
# You must write an algorithm with O(sum of words[i].length) runtime complexity.
#
# Example:
# Input: words = ["abcd","dcba","lls","s","sssll"]
# Output: [[0,1],[1,0],[3,2],[2,4]]
# Explanation: The palindromes are ["abcddcba","dcbaabcd","slls","llssssll"]
#
# Constraints:
# 1 <= words.length <= 5000
#  0 <= words[i].length <= 300
#  words[i] consists of lowercase English letters.
#

class Solution(object):
    def palindromePairs(self, words):
        """
        :type words: List[str]
        :rtype: List[List[int]]
        """
        word_dict = {word: i for i, word in enumerate(words)}
        result = []

        for i, word in enumerate(words):
            for j in range(len(word) + 1):
                prefix, suffix = word[:j], word[j:]

                if prefix == prefix[::-1]:
                    reversed_suffix = suffix[::-1]
                    if reversed_suffix in word_dict and word_dict[reversed_suffix] != i:
                        result.append([word_dict[reversed_suffix], i])

                if j != len(word) and suffix == suffix[::-1]:
                    reversed_prefix = prefix[::-1]
                    if reversed_prefix in word_dict and word_dict[reversed_prefix] != i:
                        result.append([i, word_dict[reversed_prefix]])

        return result