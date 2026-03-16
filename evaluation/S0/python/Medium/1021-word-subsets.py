# Source: https://leetcode.com/problems/word-subsets/   |   Difficulty: Medium
#
# Problem Description:
# You are given two string arrays words1 and words2.
#
# A string b is a subset of string a if every letter in b occurs in a including multiplicity.
#
#
# 	For example, "wrr" is a subset of "warrior" but is not a subset of "world".
#
#
# A string a from words1 is universal if for every string b in words2, b is a subset of a.
#
# Return an array of all the universal strings in words1. You may return the answer in any order.
#
# Example:
# Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
#
# Output: ["facebook","google","leetcode"]
#
# Constraints:
# 1 <= words1.length, words2.length <= 104
# 	1 <= words1[i].length, words2[i].length <= 10
# 	words1[i] and words2[i] consist only of lowercase English letters.
# 	All the strings of words1 are unique.
#

class Solution(object):
    def wordSubsets(self, words1, words2):
        """
        :type words1: List[str]
        :type words2: List[str]
        :rtype: List[str]
        """
        from collections import Counter
        import copy

        max_freq = Counter()
        for b in words2:
            freq_b = Counter(b)
            for char in freq_b:
                max_freq[char] = max(max_freq[char], freq_b[char])

        result = []
        for a in words1:
            freq_a = Counter(a)
            is_universal = True
            for char in max_freq:
                if freq_a[char] < max_freq[char]:
                    is_universal = False
                    break
            if is_universal:
                result.append(a)

        return result