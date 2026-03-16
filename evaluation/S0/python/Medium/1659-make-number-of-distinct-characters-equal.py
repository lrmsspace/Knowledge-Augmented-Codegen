# Source: https://leetcode.com/problems/make-number-of-distinct-characters-equal/   |   Difficulty: Medium
#
# Problem Description:
# You are given two 0-indexed strings word1 and word2.
#
# A move consists of choosing two indices i and j such that 0 <= i < word1.length and 0 <= j < word2.length and swapping word1[i] with word2[j].
#
# Return true if it is possible to get the number of distinct characters in word1 and word2 to be equal with exactly one move. Return false otherwise.
#
# Example:
# Input: word1 = "ac", word2 = "b"
# Output: false
# Explanation: Any pair of swaps would yield two distinct characters in the first string, and one in the second string.
#
# Constraints:
# 1 <= word1.length, word2.length <= 105
# 	word1 and word2 consist of only lowercase English letters.
#

class Solution(object):
    def isItPossible(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: bool
        """
        set1 = set(word1)
        set2 = set(word2)
        len1 = len(set1)
        len2 = len(set2)

        for c1 in set1:
            for c2 in set2:
                new_len1 = len1 - (1 if c1 not in set2 else 0) + (1 if c2 not in set1 else 0)
                new_len2 = len2 - (1 if c2 not in set1 else 0) + (1 if c1 not in set2 else 0)
                if new_len1 == new_len2:
                    return True
        return False