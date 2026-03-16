# Source: https://leetcode.com/problems/alternating-groups-ii/   |   Difficulty: Medium
#
# Problem Description:
# There is a circle of red and blue tiles. You are given an array of integers colors and an integer k. The color of tile i is represented by colors[i]:
#
#
# 	colors[i] == 0 means that tile i is red.
# 	colors[i] == 1 means that tile i is blue.
#
#
# An alternating group is every k contiguous tiles in the circle with alternating colors (each tile in the group except the first and last one has a different color from its left and right tiles).
#
# Return the number of alternating groups.
#
# Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.
#
# Example:
# Input: colors = [0,1,0,1,0], k = 3
#
# Output: 3
#
# Explanation:
#
#
#
# Alternating groups:
#
# Constraints:
# 3 <= colors.length <= 105
# 	0 <= colors[i] <= 1
# 	3 <= k <= colors.length
#

class Solution(object):
    def numberOfAlternatingGroups(self, colors, k):
        """
        :type colors: List[int]
        :type k: int
        :rtype: int
        """
        n = len(colors)
        colors = colors * 2  # Duplicate the array to handle circular nature
        count = 0

        for i in range(n):
            is_alternating = True
            for j in range(1, k):
                if colors[i + j] == colors[i + j - 1]:
                    is_alternating = False
                    break
            if is_alternating:
                count += 1

        return count