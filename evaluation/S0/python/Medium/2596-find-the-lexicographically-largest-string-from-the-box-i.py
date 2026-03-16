# Source: https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string word, and an integer numFriends.
#
# Alice is organizing a game for her numFriends friends. There are multiple rounds in the game, where in each round:
#
#
# 	word is split into numFriends non-empty strings, such that no previous round has had the exact same split.
# 	All the split words are put into a box.
#
#
# Find the lexicographically largest string from the box after all the rounds are finished.
#
# Example:
# Input: word = "dbca", numFriends = 2
#
# Output: "dbc"
#
# Explanation: 
#
# All possible splits are:
#
#
# 	"d" and "bca".
# 	"db" and "ca".
# 	"dbc" and "a".
#
# Constraints:
# 1 <= word.length <= 5 * 103
# 	word consists only of lowercase English letters.
# 	1 <= numFriends <= word.length
#

class Solution(object):
    def answerString(self, word, numFriends):
        """
        :type word: str
        :type numFriends: int
        :rtype: str
        """
        n = len(word)
        res = ""
        
        for i in range(1, n - numFriends + 2):
            res = max(res, word[:i])
        
        return res