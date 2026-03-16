# Source: https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/   |   Difficulty: Medium
#
# Problem Description:
# A string is considered beautiful if it satisfies the following conditions:
#
#
# 	Each of the 5 English vowels ('a', 'e', 'i', 'o', 'u') must appear at least once in it.
# 	The letters must be sorted in alphabetical order (i.e. all 'a's before 'e's, all 'e's before 'i's, etc.).
#
#
# For example, strings "aeiou" and "aaaaaaeiiiioou" are considered beautiful, but "uaeio", "aeoiu", and "aaaeeeooo" are not beautiful.
#
# Given a string word consisting of English vowels, return the length of the longest beautiful substring of word. If no such substring exists, return 0.
#
# A substring is a contiguous sequence of characters in a string.
#
# Example:
# Input: word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
# Output: 13
# Explanation: The longest beautiful substring in word is "aaaaeiiiiouuu" of length 13.
#
# Constraints:
# 1 <= word.length <= 5 * 105
# 	word consists of characters 'a', 'e', 'i', 'o', and 'u'.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def longestBeautifulSubstring(self, word):
        """
        :type word: str
        :rtype: int
        """
        vowels = 'aeiou'
        max_length = 0
        n = len(word)
        i = 0

        while i < n:
            if word[i] != 'a':
                i += 1
                continue

            count = 1
            current_vowel_index = 0
            j = i + 1

            while j < n:
                if word[j] == vowels[current_vowel_index]:
                    count += 1
                elif current_vowel_index < 4 and word[j] == vowels[current_vowel_index + 1]:
                    current_vowel_index += 1
                    count += 1
                else:
                    break
                j += 1

            if current_vowel_index == 4:
                max_length = max(max_length, count)

            i = j

        return max_length