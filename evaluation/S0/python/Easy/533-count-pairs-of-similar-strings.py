# Source: https://leetcode.com/problems/count-pairs-of-similar-strings/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed string array words.
#
# Two strings are similar if they consist of the same characters.
#
#
# 	For example, "abca" and "cba" are similar since both consist of characters 'a', 'b', and 'c'.
# 	However, "abacba" and "bcfd" are not similar since they do not consist of the same characters.
#
#
# Return the number of pairs (i, j) such that 0 <= i < j <= word.length - 1 and the two strings words[i] and words[j] are similar.
#
# Example:
# Input: words = ["aba","aabb","abcd","bac","aabc"]
# Output: 2
# Explanation: There are 2 pairs that satisfy the conditions:
# - i = 0 and j = 1 : both words[0] and words[1] only consist of characters 'a' and 'b'. 
# - i = 3 and j = 4 : both words[3] and words[4] only consist of characters 'a', 'b', and 'c'.
#
# Constraints:
# 1 <= words.length <= 100
# 	1 <= words[i].length <= 100
# 	words[i] consist of only lowercase English letters.
#

class Solution(object):
    def similarPairs(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        from collections import defaultdict

        char_set_count = defaultdict(int)

        for word in words:
            unique_chars = frozenset(word)
            char_set_count[unique_chars] += 1

        pair_count = 0
        for count in char_set_count.values():
            if count > 1:
                pair_count += count * (count - 1) // 2

        return pair_count