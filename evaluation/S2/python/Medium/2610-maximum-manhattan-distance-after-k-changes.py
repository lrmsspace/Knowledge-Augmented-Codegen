# Source: https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s consisting of the characters 'N', 'S', 'E', and 'W', where s[i] indicates movements in an infinite grid:
#
#
# 	'N' : Move north by 1 unit.
# 	'S' : Move south by 1 unit.
# 	'E' : Move east by 1 unit.
# 	'W' : Move west by 1 unit.
#
#
# Initially, you are at the origin (0, 0). You can change at most k characters to any of the four directions.
#
# Find the maximum Manhattan distance from the origin that can be achieved at any time while performing the movements in order.
# The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
#
# Example:
# Input: s = "NWSE", k = 1
#
# Output: 3
#
# Explanation:
#
# Change s[2] from 'S' to 'N'. The string s becomes "NWNE".
#
#
# 	
# 		
# 			Movement
# 			Position (x, y)
# 			Manhattan Distance
# 			Maximum
# 		
# 	
# 	
# 		
# 			s[0] == 'N'
# 			(0, 1)
# 			0 + 1 = 1
# 			1
# 		
# 		
# 			s[1] == 'W'
# 			(-1, 1)
# 			1 + 1 = 2
# 			2
# 		
# 		
# 			s[2] == 'N'
# 			(-1, 2)
# 			1 + 2 = 3
# 			3
# 		
# 		
# 			s[3] == 'E'
# 			(0, 2)
# 			0 + 2 = 2
# 			3
# 		
# 	
#
#
# The maximum Manhattan distance from the origin that can be achieved is 3. Hence, 3 is the output.
#
# Constraints:
# 1 <= s.length <= 105
# 	0 <= k <= s.length
# 	s consists of only 'N', 'S', 'E', and 'W'.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxDistance(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        x = y = 0
        for c in s:
            if c == 'N':
                y += 1
            elif c == 'S':
                y -= 1
            elif c == 'E':
                x += 1
            elif c == 'W':
                x -= 1

        dist = abs(x) + abs(y)
        return dist + min(k, len(s) - dist)