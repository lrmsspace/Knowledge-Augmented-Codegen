# Source: https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array of strings words and a string chars.
#
# A string is good if it can be formed by characters from chars (each character can only be used once for each word in words).
#
# Return the sum of lengths of all good strings in words.
#
# Example:
# Input: words = ["cat","bt","hat","tree"], chars = "atach"
# Output: 6
# Explanation: The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.
#
# Constraints:
# 1 <= words.length <= 1000
# 	1 <= words[i].length, chars.length <= 100
# 	words[i] and chars consist of lowercase English letters.
#

class Solution(object):
    def countCharacters(self, words, chars):
        """
        :type words: List[str]
        :type chars: str
        :rtype: int
        """
        from collections import Counter

        char_count = Counter(chars)
        total_length = 0

        for word in words:
            word_count = Counter(word)
            if all(word_count[char] <= char_count[char] for char in word_count):
                total_length += len(word)

        return total_length