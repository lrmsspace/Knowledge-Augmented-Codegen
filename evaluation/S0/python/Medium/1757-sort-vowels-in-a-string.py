# Source: https://leetcode.com/problems/sort-vowels-in-a-string/   |   Difficulty: Medium
#
# Problem Description:
# Given a 0-indexed string s, permute s to get a new string t such that:
#
#
# 	All consonants remain in their original places. More formally, if there is an index i with 0 <= i < s.length such that s[i] is a consonant, then t[i] = s[i].
# 	The vowels must be sorted in the nondecreasing order of their ASCII values. More formally, for pairs of indices i, j with 0 <= i < j < s.length such that s[i] and s[j] are vowels, then t[i] must not have a higher ASCII value than t[j].
#
#
# Return the resulting string.
#
# The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in lowercase or uppercase. Consonants comprise all letters that are not vowels.
#
# Example:
# Input: s = "lEetcOde"
# Output: "lEOtcede"
# Explanation: 'E', 'O', and 'e' are the vowels in s; 'l', 't', 'c', and 'd' are all consonants. The vowels are sorted according to their ASCII values, and the consonants remain in the same places.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists only of letters of the English alphabet in uppercase and lowercase.
#

class Solution(object):
    def sortVowels(self, s):
        """
        :type s: str
        :rtype: str
        """
        vowels = 'aeiouAEIOU'
        vowel_chars = sorted([c for c in s if c in vowels])
        result = []
        vowel_index = 0

        for char in s:
            if char in vowels:
                result.append(vowel_chars[vowel_index])
                vowel_index += 1
            else:
                result.append(char)

        return ''.join(result)