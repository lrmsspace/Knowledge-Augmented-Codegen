# Source: https://leetcode.com/problems/number-of-matching-subsequences/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s and an array of strings words, return the number of words[i] that is a subsequence of s.
#
# A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
#
#
# 	For example, "ace" is a subsequence of "abcde".
#
# Example:
# Input: s = "abcde", words = ["a","bb","acd","ace"]
# Output: 3
# Explanation: There are three strings in words that are a subsequence of s: "a", "acd", "ace".
#
# Constraints:
# 1 <= s.length <= 5 * 104
# 	1 <= words.length <= 5000
# 	1 <= words[i].length <= 50
# 	s and words[i] consist of only lowercase English letters.
#

class Solution(object):
    def numMatchingSubseq(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: int
        """
        from collections import defaultdict
        import bisect

        char_indices = defaultdict(list)
        for index, char in enumerate(s):
            char_indices[char].append(index)

        def is_subsequence(word):
            prev_index = -1
            for char in word:
                if char not in char_indices:
                    return False
                indices = char_indices[char]
                i = bisect.bisect_right(indices, prev_index)
                if i == len(indices):
                    return False
                prev_index = indices[i]
            return True

        count = 0
        for word in words:
            if is_subsequence(word):
                count += 1

        return count