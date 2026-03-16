# Source: https://leetcode.com/problems/longest-common-prefix/   |   Difficulty: Easy
#
# Problem Description:
# Write a function to find the longest common prefix string amongst an array of strings.
#
# If there is no common prefix, return an empty string "".
#
# Example:
# Input: strs = ["flower","flow","flight"]
# Output: "fl"
#
# Constraints:
# 1 <= strs.length <= 200
# 	0 <= strs[i].length <= 200
# 	strs[i] consists of only lowercase English letters if it is non-empty.
#

class Solution(object):
    def longestCommonPrefix(self, strs):
        """
        :type strs: List[str]
        :rtype: str
        """
        if not strs:
            return ""
        
        prefix = strs[0]
        
        for s in strs[1:]:
            while not s.startswith(prefix):
                prefix = prefix[:-1]
                if not prefix:
                    return ""
        
        return prefix