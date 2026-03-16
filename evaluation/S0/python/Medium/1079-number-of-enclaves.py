# Source: https://leetcode.com/problems/number-of-enclaves/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.
#
# A move consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.
#
# Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.
#
# Example:
# Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
# Output: 3
# Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 500
# 	grid[i][j] is either 0 or 1.
#

class Solution(object):
    def numEnclaves(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        rows, cols = len(grid), len(grid[0])
        
        def dfs(r, c):
            if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] == 0:
                return
            grid[r][c] = 0  # Mark as visited by sinking the land
            dfs(r + 1, c)
            dfs(r - 1, c)
            dfs(r, c + 1)
            dfs(r, c - 1)
        
        # Eliminate lands connected to the borders
        for r in range(rows):
            for c in range(cols):
                if (r in [0, rows - 1] or c in [0, cols - 1]) and grid[r][c] == 1:
                    dfs(r, c)
        
        # Count remaining land cells
        enclave_count = sum(grid[r][c] == 1 for r in range(rows) for c in range(cols))
        
        return enclave_count