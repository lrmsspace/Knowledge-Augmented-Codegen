# Source: https://leetcode.com/problems/coloring-a-border/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n integer matrix grid, and three integers row, col, and color. Each value in the grid represents the color of the grid square at that location.
#
# Two squares are called adjacent if they are next to each other in any of the 4 directions.
#
# Two squares belong to the same connected component if they have the same color and they are adjacent.
#
# The border of a connected component is all the squares in the connected component that are either adjacent to (at least) a square not in the component, or on the boundary of the grid (the first or last row or column).
#
# You should color the border of the connected component that contains the square grid[row][col] with color.
#
# Return the final grid.
#
# Example:
# Input: grid = [[1,1],[1,2]], row = 0, col = 0, color = 3
# Output: [[3,3],[3,2]]
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 50
# 	1 <= grid[i][j], color <= 1000
# 	0 <= row < m
# 	0 <= col < n
#

class Solution(object):
    def colorBorder(self, grid, row, col, color):
        """
        :type grid: List[List[int]]
        :type row: int
        :type col: int
        :type color: int
        :rtype: List[List[int]]
        """
        m, n = len(grid), len(grid[0])
        original_color = grid[row][col]
        visited = [[False] * n for _ in range(m)]
        borders = []

        def is_border(r, c):
            if r == 0 or r == m - 1 or c == 0 or c == n - 1:
                return True
            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr, nc = r + dr, c + dc
                if grid[nr][nc] != original_color:
                    return True
            return False

        def dfs(r, c):
            visited[r][c] = True
            if is_border(r, c):
                borders.append((r, c))
            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and not visited[nr][nc] and grid[nr][nc] == original_color:
                    dfs(nr, nc)

        dfs(row, col)

        for r, c in borders:
            grid[r][c] = color

        return grid