# Source: https://leetcode.com/problems/projection-area-of-3d-shapes/   |   Difficulty: Easy
#
# Problem Description:
# You are given an n x n grid where we place some 1 x 1 x 1 cubes that are axis-aligned with the x, y, and z axes.
#
# Each value v = grid[i][j] represents a tower of v cubes placed on top of the cell (i, j).
#
# We view the projection of these cubes onto the xy, yz, and zx planes.
#
# A projection is like a shadow, that maps our 3-dimensional figure to a 2-dimensional plane. We are viewing the "shadow" when looking at the cubes from the top, the front, and the side.
#
# Return the total area of all three projections.
#
# Example:
# Input: grid = [[1,2],[3,4]]
# Output: 17
# Explanation: Here are the three projections ("shadows") of the shape made with each axis-aligned plane.
#
# Constraints:
# n == grid.length == grid[i].length
# 	1 <= n <= 50
# 	0 <= grid[i][j] <= 50
#

class Solution(object):
    def projectionArea(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        xy_area = 0
        yz_area = 0
        zx_area = 0
        
        for i in range(n):
            max_row = 0
            max_col = 0
            for j in range(n):
                # XY projection
                if grid[i][j] > 0:
                    xy_area += 1
                
                # YZ projection
                max_row = max(max_row, grid[i][j])
                
                # ZX projection
                max_col = max(max_col, grid[j][i])
            
            yz_area += max_row
            zx_area += max_col
        
        return xy_area + yz_area + zx_area