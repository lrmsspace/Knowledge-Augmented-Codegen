# Source: https://leetcode.com/problems/maximum-repeating-substring/   |   Difficulty: Easy
#
# Problem Description:
# For a string sequence, a string word is k-repeating if word concatenated k times is a substring of sequence. The word's maximum k-repeating value is the highest value k where word is k-repeating in sequence. If word is not a substring of sequence, word's maximum k-repeating value is 0.
#
# Given strings sequence and word, return the maximum k-repeating value of word in sequence.
#
# Example:
# Input: sequence = "ababc", word = "ab"
# Output: 2
# Explanation: "abab" is a substring in "ababc".
#
# Constraints:
# 1 <= sequence.length <= 100
# 	1 <= word.length <= 100
# 	sequence and word contains only lowercase English letters.
#

class Solution(object):
    def maxRepeating(self, sequence, word):
        """
        :type sequence: str
        :type word: str
        :rtype: int
        """
        max_count = 0
        current_count = 0
        word_length = len(word)
        i = 0
        
        while i <= len(sequence) - word_length:
            if sequence[i:i + word_length] == word:
                current_count += 1
                max_count = max(max_count, current_count)
                i += word_length
            else:
                current_count = 0
                i += 1
        
        return max_count