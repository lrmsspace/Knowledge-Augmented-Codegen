# Source: https://leetcode.com/problems/group-anagrams/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of strings strs, group the anagrams together. You can return the answer in any order.
#
# Example:
# Input: strs = ["eat","tea","tan","ate","nat","bat"]
#
# Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
#
# Explanation:
#
#
# 	There is no string in strs that can be rearranged to form "bat".
# 	The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
# 	The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.
#
# Constraints:
# 1 <= strs.length <= 104
# 	0 <= strs[i].length <= 100
# 	strs[i] consists of lowercase English letters.
#

class Solution(object):
    def groupAnagrams(self, strs):
        """
        :type strs: List[str]
        :rtype: List[List[str]]
        """
        anagrams = {}
        for s in strs:
            key = ''.join(sorted(s))
            if key not in anagrams:
                anagrams[key] = []
            anagrams[key].append(s)
        return list(anagrams.values())