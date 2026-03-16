# Source: https://leetcode.com/problems/check-whether-two-strings-are-almost-equivalent/   |   Difficulty: Easy
#
# Problem Description:
# Two strings word1 and word2 are considered almost equivalent if the differences between the frequencies of each letter from 'a' to 'z' between word1 and word2 is at most 3.
#
# Given two strings word1 and word2, each of length n, return true if word1 and word2 are almost equivalent, or false otherwise.
#
# The frequency of a letter x is the number of times it occurs in the string.
#
# Example:
# Input: word1 = "aaaa", word2 = "bccb"
# Output: false
# Explanation: There are 4 'a's in "aaaa" but 0 'a's in "bccb".
# The difference is 4, which is more than the allowed 3.
#
# Constraints:
# n == word1.length == word2.length
# 	1 <= n <= 100
# 	word1 and word2 consist only of lowercase English letters.
#

class Solution(object):
    def checkAlmostEquivalent(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: bool
        """
        freq1 = [0] * 26
        freq2 = [0] * 26
        
        for char in word1:
            freq1[ord(char) - ord('a')] += 1
            
        for char in word2:
            freq2[ord(char) - ord('a')] += 1
            
        for i in range(26):
            if abs(freq1[i] - freq2[i]) > 3:
                return False
                
        return True