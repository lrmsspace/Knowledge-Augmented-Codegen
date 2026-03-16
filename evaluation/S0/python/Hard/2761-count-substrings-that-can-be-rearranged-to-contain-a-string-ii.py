# Source: https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given two strings word1 and word2.
#
# A string x is called valid if x can be rearranged to have word2 as a prefix.
#
# Return the total number of valid substrings of word1.
#
# Note that the memory limits in this problem are smaller than usual, so you must implement a solution with a linear runtime complexity.
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
# 1 <= word1.length <= 106
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
        if len1 < len2:
            return 0

        count2 = Counter(word2)
        window_count = Counter(word1[:len2 - 1])
        result = 0

        for i in range(len2 - 1, len1):
            window_count[word1[i]] += 1

            if all(window_count[char] >= count2[char] for char in count2):
                result += 1

            window_count[word1[i - len2 + 1]] -= 1
            if window_count[word1[i - len2 + 1]] == 0:
                del window_count[word1[i - len2 + 1]]

        return result