# Source: https://leetcode.com/problems/find-the-lexicographically-smallest-valid-sequence/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings word1 and word2.
#
# A string x is called almost equal to y if you can change at most one character in x to make it identical to y.
#
# A sequence of indices seq is called valid if:
#
#
# 	The indices are sorted in ascending order.
# 	Concatenating the characters at these indices in word1 in the same order results in a string that is almost equal to word2.
#
#
# Return an array of size word2.length representing the lexicographically smallest valid sequence of indices. If no such sequence of indices exists, return an empty array.
#
# Note that the answer must represent the lexicographically smallest array, not the corresponding string formed by those indices.
#
# Example:
# Input: word1 = "vbcca", word2 = "abc"
#
# Output: [0,1,2]
#
# Explanation:
#
# The lexicographically smallest valid sequence of indices is [0, 1, 2]:
#
#
# 	Change word1[0] to 'a'.
# 	word1[1] is already 'b'.
# 	word1[2] is already 'c'.
#
# Constraints:
# 1 <= word2.length < word1.length <= 3 * 105
# 	word1 and word2 consist only of lowercase English letters.
#

class Solution(object):
    def validSequence(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: List[int]
        """
        n, m = len(word1), len(word2)
        left, right = [ -1 ] * m, [ -1 ] * m
        
        j = 0
        for i in range(n):
            if j < m and word1[i] == word2[j]:
                left[j] = i
                j += 1
        
        j = m - 1
        for i in range(n - 1, -1, -1):
            if j >= 0 and word1[i] == word2[j]:
                right[j] = i
                j -= 1
        
        res = None
        for i in range(m):
            l = left[i - 1] + 1 if i > 0 else 0
            r = right[i + 1] - 1 if i < m - 1 else n - 1
            
            for c in range(26):
                ch = chr(ord('a') + c)
                pos = self.find_char_in_range(word1, ch, l, r)
                if pos != -1:
                    candidate = left[:i] + [pos] + right[i + 1:]
                    if res is None or candidate < res:
                        res = candidate
                    break
        
        return res if res is not None else []