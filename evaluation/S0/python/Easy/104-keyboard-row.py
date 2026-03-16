# Source: https://leetcode.com/problems/keyboard-row/   |   Difficulty: Easy
#
# Problem Description:
# Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.
#
# Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are at the same row.
#
# In the American keyboard:
#
#
# 	the first row consists of the characters "qwertyuiop",
# 	the second row consists of the characters "asdfghjkl", and
# 	the third row consists of the characters "zxcvbnm".
#
# Example:
# Input: words = ["Hello","Alaska","Dad","Peace"]
#
# Output: ["Alaska","Dad"]
#
# Explanation:
#
# Both "a" and "A" are in the 2nd row of the American keyboard due to case insensitivity.
#
# Constraints:
# 1 <= words.length <= 20
# 	1 <= words[i].length <= 100
# 	words[i] consists of English letters (both lowercase and uppercase).
#

class Solution(object):
    def findWords(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        row1 = set("qwertyuiopQWERTYUIOP")
        row2 = set("asdfghjklASDFGHJKL")
        row3 = set("zxcvbnmZXCVBNM")
        
        result = []
        
        for word in words:
            if all(char in row1 for char in word) or \
               all(char in row2 for char in word) or \
               all(char in row3 for char in word):
                result.append(word)
                
        return result