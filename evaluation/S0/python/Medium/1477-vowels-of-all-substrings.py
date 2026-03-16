# Source: https://leetcode.com/problems/vowels-of-all-substrings/   |   Difficulty: Medium
#
# Problem Description:
# Given a string word, return the sum of the number of vowels ('a', 'e', 'i', 'o', and 'u') in every substring of word.
#
# A substring is a contiguous (non-empty) sequence of characters within a string.
#
# Note: Due to the large constraints, the answer may not fit in a signed 32-bit integer. Please be careful during the calculations.
#
# Example:
# Input: word = "aba"
# Output: 6
# Explanation: 
# All possible substrings are: "a", "ab", "aba", "b", "ba", and "a".
# - "b" has 0 vowels in it
# - "a", "ab", "ba", and "a" have 1 vowel each
# - "aba" has 2 vowels in it
# Hence, the total sum of vowels = 0 + 1 + 1 + 1 + 1 + 2 = 6.
#
# Constraints:
# 1 <= word.length <= 105
# 	word consists of lowercase English letters.
#

class Solution(object):
    def countVowels(self, word):
        """
        :type word: str
        :rtype: int
        """
        vowels = set('aeiou')
        total_vowels = 0
        n = len(word)
        
        for i, char in enumerate(word):
            if char in vowels:
                # Each vowel at position i contributes to (i + 1) * (n - i) substrings
                total_vowels += (i + 1) * (n - i)
        
        return total_vowels