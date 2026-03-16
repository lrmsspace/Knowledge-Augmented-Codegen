# Source: https://leetcode.com/problems/number-of-closed-islands/   |   Difficulty: Medium
#
# Problem Description:
# Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.
#
# Return the number of closed islands.
#
# Example:
# Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
# Output: 2
# Explanation: 
# Islands in gray are closed because they are completely surrounded by water (group of 1s).
#
# Constraints:
# 1 <= grid.length, grid[0].length <= 100
# 	0 <= grid[i][j] <=1
#

class Solution(object):
    def closedIsland(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        if not grid or not grid[0]:
            return 0

        rows, cols = len(grid), len(grid[0])

        def dfs(r, c):
            if r < 0 or r >= rows or c < 0 or c >= cols:
                return False
            if grid[r][c] == 1:
                return True

            grid[r][c] = 1  # Mark as visited
            up = dfs(r - 1, c)
            down = dfs(r + 1, c)
            left = dfs(r, c - 1)
            right = dfs(r, c + 1)

            return up and down and left and right

        closed_island_count = 0

        for i in range(1, rows - 1):
            for j in range(1, cols - 1):
                if grid[i][j] == 0:
                    if dfs(i, j):
                        closed_island_count += 1

        return closed_island_count