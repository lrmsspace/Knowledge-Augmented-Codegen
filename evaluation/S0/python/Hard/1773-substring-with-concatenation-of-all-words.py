# Source: https://leetcode.com/problems/substring-with-concatenation-of-all-words/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s and an array of strings words. All the strings of words are of the same length.
#
# A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.
#
#
# 	For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.
#
#
# Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.
#
# Example:
# Input: s = "barfoothefoobarman", words = ["foo","bar"]
#
# Output: [0,9]
#
# Explanation:
#
# The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
# The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.
#
# Constraints:
# 1 <= s.length <= 104
# 	1 <= words.length <= 5000
# 	1 <= words[i].length <= 30
# 	s and words[i] consist of lowercase English letters.
#

class Solution(object):
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        if not s or not words:
            return []
        
        word_length = len(words[0])
        num_words = len(words)
        total_length = word_length * num_words
        word_count = {}
        
        for word in words:
            word_count[word] = word_count.get(word, 0) + 1
        
        result_indices = []
        
        for i in range(len(s) - total_length + 1):
            seen_words = {}
            for j in range(num_words):
                word_index = i + j * word_length
                word = s[word_index:word_index + word_length]
                
                if word not in word_count:
                    break
                
                seen_words[word] = seen_words.get(word, 0) + 1
                
                if seen_words[word] > word_count[word]:
                    break
            else:
                result_indices.append(i)
        
        return result_indices