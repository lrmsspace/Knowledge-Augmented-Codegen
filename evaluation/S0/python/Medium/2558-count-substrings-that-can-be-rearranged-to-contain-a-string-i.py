# Source: https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings word1 and word2.
#
# A string x is called valid if x can be rearranged to have word2 as a prefix.
#
# Return the total number of valid substrings of word1.
#
# Example:
# Input: word1 = "bcca", word2 = "abc"
#
# Output: 1
#
# Explanation:
#
# The only valid substring is "bcca" which can be rearranged to "abcc" having "abc" as a prefix.
#
# Constraints:
# 1 <= word1.length <= 105
# 	1 <= word2.length <= 104
# 	word1 and word2 consist only of lowercase English letters.
#

class Solution(object):
    def validSubstringCount(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        from collections import Counter

        len1, len2 = len(word1), len(word2)
        count2 = Counter(word2)
        result = 0

        for i in range(len1 - len2 + 1):
            substring = word1[i:i + len2]
            count_substring = Counter(substring)

            if all(count_substring[char] >= count2[char] for char in count2):
                result += 1

        return result