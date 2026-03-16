# Source: https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string word and a non-negative integer k.
#
# Return the total number of substrings of word that contain every vowel ('a', 'e', 'i', 'o', and 'u') at least once and exactly k consonants.
#
# Example:
# Input: word = "aeioqq", k = 1
#
# Output: 0
#
# Explanation:
#
# There is no substring with every vowel.
#
# Constraints:
# 5 <= word.length <= 250
# 	word consists only of lowercase English letters.
# 	0 <= k <= word.length - 5
#

class Solution(object):
    def countOfSubstrings(self, word, k):
        """
        :type word: str
        :type k: int
        :rtype: int
        """
        vowels = set('aeiou')
        n = len(word)
        result = 0

        for i in range(n):
            vowel_count = 0
            consonant_count = 0
            seen_vowels = set()

            for j in range(i, n):
                if word[j] in vowels:
                    seen_vowels.add(word[j])
                else:
                    consonant_count += 1

                if len(seen_vowels) == 5 and consonant_count == k:
                    result += 1
                elif consonant_count > k:
                    break

        return result