# Source: https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D binary array grid. Find a rectangle with horizontal and vertical sides with the smallest area, such that all the 1's in grid lie inside this rectangle.
#
# Return the minimum possible area of the rectangle.
#
# Example:
# Input: grid = [[0,1,0],[1,0,1]]
#
# Output: 6
#
# Explanation:
#
#
#
# The smallest rectangle has a height of 2 and a width of 3, so it has an area of 2 * 3 = 6.
#
# Constraints:
# 1 <= grid.length, grid[i].length <= 1000
# 	grid[i][j] is either 0 or 1.
# 	The input is generated such that there is at least one 1 in grid.
#

class Solution(object):
    def minimumArea(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        rows = len(grid)
        cols = len(grid[0])
        
        min_row, max_row = rows, -1
        min_col, max_col = cols, -1
        
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    if r < min_row:
                        min_row = r
                    if r > max_row:
                        max_row = r
                    if c < min_col:
                        min_col = c
                    if c > max_col:
                        max_col = c
        
        height = max_row - min_row + 1
        width = max_col - min_col + 1
        
        return height * width