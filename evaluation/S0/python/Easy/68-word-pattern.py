# Source: https://leetcode.com/problems/word-pattern/   |   Difficulty: Easy
#
# Problem Description:
# Given a pattern and a string s, find if s follows the same pattern.
#
# Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in s. Specifically:
#
#
# 	Each letter in pattern maps to exactly one unique word in s.
# 	Each unique word in s maps to exactly one letter in pattern.
# 	No two letters map to the same word, and no two words map to the same letter.
#
# Example:
# Input: pattern = "abba", s = "dog cat cat dog"
#
# Output: true
#
# Explanation:
#
# The bijection can be established as:
#
#
# 	'a' maps to "dog".
# 	'b' maps to "cat".
#
# Constraints:
# 1 <= pattern.length <= 300
# 	pattern contains only lower-case English letters.
# 	1 <= s.length <= 3000
# 	s contains only lowercase English letters and spaces ' '.
# 	s does not contain any leading or trailing spaces.
# 	All the words in s are separated by a single space.
#

class Solution(object):
    def wordPattern(self, pattern, s):
        """
        :type pattern: str
        :type s: str
        :rtype: bool
        """
        words = s.split()
        if len(pattern) != len(words):
            return False
        
        char_to_word = {}
        word_to_char = {}
        
        for p_char, word in zip(pattern, words):
            if p_char in char_to_word:
                if char_to_word[p_char] != word:
                    return False
            else:
                char_to_word[p_char] = word
            
            if word in word_to_char:
                if word_to_char[word] != p_char:
                    return False
            else:
                word_to_char[word] = p_char
        
        return True