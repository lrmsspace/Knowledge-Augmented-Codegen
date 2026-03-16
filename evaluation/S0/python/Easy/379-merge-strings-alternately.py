# Source: https://leetcode.com/problems/merge-strings-alternately/   |   Difficulty: Easy
#
# Problem Description:
# You are given two strings word1 and word2. Merge the strings by adding letters in alternating order, starting with word1. If a string is longer than the other, append the additional letters onto the end of the merged string.
#
# Return the merged string.
#
# Example:
# Input: word1 = "abc", word2 = "pqr"
# Output: "apbqcr"
# Explanation: The merged string will be merged as so:
# word1:  a   b   c
# word2:    p   q   r
# merged: a p b q c r
#
# Constraints:
# 1 <= word1.length, word2.length <= 100
# 	word1 and word2 consist of lowercase English letters.
#

class Solution(object):
    def mergeAlternately(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: str
        """
        merged = []
        len1, len2 = len(word1), len(word2)
        min_len = min(len1, len2)
        
        for i in range(min_len):
            merged.append(word1[i])
            merged.append(word2[i])
        
        if len1 > len2:
            merged.append(word1[min_len:])
        else:
            merged.append(word2[min_len:])
        
        return ''.join(merged)