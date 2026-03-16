# Source: https://leetcode.com/problems/word-ladder/   |   Difficulty: Hard
#
# Problem Description:
# A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
#
#
# 	Every adjacent pair of words differs by a single letter.
# 	Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
# 	sk == endWord
#
#
# Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.
#
# Example:
# Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
# Output: 5
# Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
#
# Constraints:
# 1 <= beginWord.length <= 10
# 	endWord.length == beginWord.length
# 	1 <= wordList.length <= 5000
# 	wordList[i].length == beginWord.length
# 	beginWord, endWord, and wordList[i] consist of lowercase English letters.
# 	beginWord != endWord
# 	All the words in wordList are unique.
#

class Solution(object):
    def ladderLength(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """
        wordSet = set(wordList)
        if endWord not in wordSet:
            return 0
        
        queue = [(beginWord, 1)]
        visited = set([beginWord])
        
        while queue:
            current_word, length = queue.pop(0)
            if current_word == endWord:
                return length
            
            for i in range(len(current_word)):
                for c in 'abcdefghijklmnopqrstuvwxyz':
                    next_word = current_word[:i] + c + current_word[i+1:]
                    if next_word in wordSet and next_word not in visited:
                        visited.add(next_word)
                        queue.append((next_word, length + 1))
        
        return 0