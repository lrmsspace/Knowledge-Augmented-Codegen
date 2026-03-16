# Source: https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n representing the dimensions of an n x n grid, with the origin at the bottom-left corner of the grid. You are also given a 2D array of coordinates rectangles, where rectangles[i] is in the form [startx, starty, endx, endy], representing a rectangle on the grid. Each rectangle is defined as follows:
#
#
# 	(startx, starty): The bottom-left corner of the rectangle.
# 	(endx, endy): The top-right corner of the rectangle.
#
#
# Note that the rectangles do not overlap. Your task is to determine if it is possible to make either two horizontal or two vertical cuts on the grid such that:
#
#
# 	Each of the three resulting sections formed by the cuts contains at least one rectangle.
# 	Every rectangle belongs to exactly one section.
#
#
# Return true if such cuts can be made; otherwise, return false.
#
# Example:
# Input: n = 5, rectangles = [[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]
#
# Output: true
#
# Explanation:
#
#
#
# The grid is shown in the diagram. We can make horizontal cuts at y = 2 and y = 4. Hence, output is true.
#
# Constraints:
# 3 <= n <= 109
# 	3 <= rectangles.length <= 105
# 	0 <= rectangles[i][0] < rectangles[i][2] <= n
# 	0 <= rectangles[i][1] < rectangles[i][3] <= n
# 	No two rectangles overlap.
#

class Solution(object):
    def checkValidCuts(self, n, rectangles):
        """
        :type n: int
        :type rectangles: List[List[int]]
        :rtype: bool
        """
        from collections import defaultdict

        row_cuts = defaultdict(int)
        col_cuts = defaultdict(int)

        for rect in rectangles:
            row_cuts[rect[1]] += 1
            row_cuts[rect[3]] += 1
            col_cuts[rect[0]] += 1
            col_cuts[rect[2]] += 1

        def can_make_two_cuts(cuts):
            cut_positions = sorted(cuts.keys())
            count = 0
            sections = 0

            for pos in cut_positions:
                count += cuts[pos]
                if count > 0:
                    sections += 1
                    count = 0
                if sections == 3:
                    return True

            return False

        return can_make_two_cuts(row_cuts) or can_make_two_cuts(col_cuts)