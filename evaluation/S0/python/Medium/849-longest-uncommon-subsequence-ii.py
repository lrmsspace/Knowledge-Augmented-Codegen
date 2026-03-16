# Source: https://leetcode.com/problems/longest-uncommon-subsequence-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of strings strs, return the length of the longest uncommon subsequence between them. If the longest uncommon subsequence does not exist, return -1.
#
# An uncommon subsequence between an array of strings is a string that is a subsequence of one string but not the others.
#
# A subsequence of a string s is a string that can be obtained after deleting any number of characters from s.
#
#
# 	For example, "abc" is a subsequence of "aebdc" because you can delete the underlined characters in "aebdc" to get "abc". Other subsequences of "aebdc" include "aebdc", "aeb", and "" (empty string).
#
# Example:
# Input: strs = ["aba","cdc","eae"]
# Output: 3
#
# Constraints:
# 2 <= strs.length <= 50
# 	1 <= strs[i].length <= 10
# 	strs[i] consists of lowercase English letters.
#

class Solution(object):
    def findLUSlength(self, strs):
        """
        :type strs: List[str]
        :rtype: int
        """
        def is_subsequence(s, t):
            it = iter(t)
            return all(c in it for c in s)

        strs.sort(key=len, reverse=True)

        for i, s in enumerate(strs):
            if all(not is_subsequence(s, t) for j, t in enumerate(strs) if i != j):
                return len(s)

        return -1