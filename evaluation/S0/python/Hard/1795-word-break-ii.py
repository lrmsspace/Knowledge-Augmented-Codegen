# Source: https://leetcode.com/problems/word-break-ii/   |   Difficulty: Hard
#
# Problem Description:
# Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.
#
# Note that the same word in the dictionary may be reused multiple times in the segmentation.
#
# Example:
# Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
# Output: ["cats and dog","cat sand dog"]
#
# Constraints:
# 1 <= s.length <= 20
# 	1 <= wordDict.length <= 1000
# 	1 <= wordDict[i].length <= 10
# 	s and wordDict[i] consist of only lowercase English letters.
# 	All the strings of wordDict are unique.
# 	Input is generated in a way that the length of the answer doesn't exceed 105.
#

class Solution(object):
    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: List[str]
        """
        word_set = set(wordDict)
        memo = {}

        def backtrack(start):
            if start in memo:
                return memo[start]

            if start == len(s):
                return [""]

            sentences = []
            for end in range(start + 1, len(s) + 1):
                word = s[start:end]
                if word in word_set:
                    for sub_sentence in backtrack(end):
                        if sub_sentence:
                            sentences.append(word + " " + sub_sentence)
                        else:
                            sentences.append(word)

            memo[start] = sentences
            return sentences

        return backtrack(0)