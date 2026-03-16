# Source: https://leetcode.com/problems/detect-cycles-in-2d-grid/   |   Difficulty: Medium
#
# Problem Description:
# Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.
#
# A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.
#
# Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.
#
# Return true if any cycle of the same value exists in grid, otherwise, return false.
#
# Example:
# Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
# Output: true
# Explanation: There are two valid cycles shown in different colors in the image below:
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 500
# 	grid consists only of lowercase English letters.
#

class Solution(object):
    def containsCycle(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: bool
        """
        rows, cols = len(grid), len(grid[0])
        visited = [[False for _ in range(cols)] for _ in range(rows)]
        
        def dfs(r, c, pr, pc, char):
            if visited[r][c]:
                return True
            
            visited[r][c] = True
            
            directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == char:
                    if (nr, nc) != (pr, pc):
                        if dfs(nr, nc, r, c, char):
                            return True
            
            return False
        
        for i in range(rows):
            for j in range(cols):
                if not visited[i][j]:
                    if dfs(i, j, -1, -1, grid[i][j]):
                        return True
        
        return False