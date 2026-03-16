# Source: https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n binary grid grid where 1 represents land and 0 represents water. An island is a maximal 4-directionally (horizontal or vertical) connected group of 1's.
#
# The grid is said to be connected if we have exactly one island, otherwise is said disconnected.
#
# In one day, we are allowed to change any single land cell (1) into a water cell (0).
#
# Return the minimum number of days to disconnect the grid.
#
# Example:
# Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
#
# Output: 2
# Explanation: We need at least 2 days to get a disconnected grid.
# Change land grid[1][1] and grid[0][2] to water and get 2 disconnected island.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 30
# 	grid[i][j] is either 0 or 1.
#

class Solution(object):
    def minDays(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        rows, cols = len(grid), len(grid[0])
        
        def is_connected():
            visited = [[False] * cols for _ in range(rows)]
            def dfs(r, c):
                if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] == 0 or visited[r][c]:
                    return
                visited[r][c] = True
                dfs(r + 1, c)
                dfs(r - 1, c)
                dfs(r, c + 1)
                dfs(r, c - 1)
            
            found_land = False
            for r in range(rows):
                for c in range(cols):
                    if grid[r][c] == 1 and not visited[r][c]:
                        if found_land:
                            return False
                        found_land = True
                        dfs(r, c)
            return True
        
        if not is_connected():
            return 0
        
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    grid[r][c] = 0
                    if not is_connected():
                        return 1
                    grid[r][c] = 1
        
        return 2