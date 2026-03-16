# Source: https://leetcode.com/problems/largest-1-bordered-square/   |   Difficulty: Medium
#
# Problem Description:
# Given a 2D grid of 0s and 1s, return the number of elements in the largest square subgrid that has all 1s on its border, or 0 if such a subgrid doesn't exist in the grid.
#
# Example:
# Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
# Output: 9
#
# Constraints:
# 1 <= grid.length <= 100
# 	1 <= grid[0].length <= 100
# 	grid[i][j] is 0 or 1
#

class Solution(object):
    def largest1BorderedSquare(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        if not grid or not grid[0]:
            return 0
        
        rows, cols = len(grid), len(grid[0])
        max_side = 0
        
        # Precompute the number of continuous 1s to the right and down
        right = [[0] * cols for _ in range(rows)]
        down = [[0] * cols for _ in range(rows)]
        
        for r in range(rows - 1, -1, -1):
            for c in range(cols - 1, -1, -1):
                if grid[r][c] == 1:
                    right[r][c] = 1 + (right[r][c + 1] if c + 1 < cols else 0)
                    down[r][c] = 1 + (down[r + 1][c] if r + 1 < rows else 0)
        
        # Check for largest square with all 1s on the border
        for r in range(rows):
            for c in range(cols):
                small_side = min(right[r][c], down[r][c])
                while small_side > max_side:
                    if (down[r][c + small_side - 1] >= small_side and
                        right[r + small_side - 1][c] >= small_side):
                        max_side = small_side
                    small_side -= 1
        
        return max_side * max_side