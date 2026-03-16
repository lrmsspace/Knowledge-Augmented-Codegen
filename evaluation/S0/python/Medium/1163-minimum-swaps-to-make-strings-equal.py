# Source: https://leetcode.com/problems/minimum-swaps-to-make-strings-equal/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings s1 and s2 of equal length consisting of letters "x" and "y" only. Your task is to make these two strings equal to each other. You can swap any two characters that belong to different strings, which means: swap s1[i] and s2[j].
#
# Return the minimum number of swaps required to make s1 and s2 equal, or return -1 if it is impossible to do so.
#
# Example:
# Input: s1 = "xx", s2 = "yy"
# Output: 1
# Explanation: Swap s1[0] and s2[1], s1 = "yx", s2 = "yx".
#
# Constraints:
# 1 <= s1.length, s2.length <= 1000
# 	s1.length == s2.length
# 	s1, s2 only contain 'x' or 'y'.
#

class Solution(object):
    def minimumSwap(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: int
        """
        xy = 0
        yx = 0
        for a, b in zip(s1, s2):
            if a == 'x' and b == 'y':
                xy += 1
            elif a == 'y' and b == 'x':
                yx += 1
        if (xy + yx) % 2 == 1:
            return -1
        return xy // 2 + yx // 2 + xy % 2 + yx % 2