# Source: https://leetcode.com/problems/optimal-partition-of-string/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, partition the string into one or more substrings such that the characters in each substring are unique. That is, no letter appears in a single substring more than once.
#
# Return the minimum number of substrings in such a partition.
#
# Note that each character should belong to exactly one substring in a partition.
#
# Example:
# Input: s = "abacaba"
# Output: 4
# Explanation:
# Two possible partitions are ("a","ba","cab","a") and ("ab","a","ca","ba").
# It can be shown that 4 is the minimum number of substrings needed.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of only English lowercase letters.
#

class Solution(object):
    def partitionString(self, s):
        """
        :type s: str
        :rtype: int
        """
        count = 1
        seen = set()
        
        for char in s:
            if char in seen:
                count += 1
                seen = set()
            seen.add(char)
        
        return count