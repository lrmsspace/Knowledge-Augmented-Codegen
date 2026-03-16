# Source: https://leetcode.com/problems/disconnect-path-in-a-binary-matrix-by-at-most-one-flip/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed m x n binary matrix grid. You can move from a cell (row, col) to any of the cells (row + 1, col) or (row, col + 1) that has the value 1. The matrix is disconnected if there is no path from (0, 0) to (m - 1, n - 1).
#
# You can flip the value of at most one (possibly none) cell. You cannot flip the cells (0, 0) and (m - 1, n - 1).
#
# Return true if it is possible to make the matrix disconnect or false otherwise.
#
# Note that flipping a cell changes its value from 0 to 1 or from 1 to 0.
#
# Example:
# Input: grid = [[1,1,1],[1,0,0],[1,1,1]]
# Output: true
# Explanation: We can change the cell shown in the diagram above. There is no path from (0, 0) to (2, 2) in the resulting grid.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 1000
# 	1 <= m * n <= 105
# 	grid[i][j] is either 0 or 1.
# 	grid[0][0] == grid[m - 1][n - 1] == 1
#

class Solution(object):
    def isPossibleToCutPath(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: bool
        """
        m, n = len(grid), len(grid[0])
        
        def dfs(x, y, visited):
            if x == m - 1 and y == n - 1:
                return True
            visited.add((x, y))
            for dx, dy in [(1, 0), (0, 1)]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] == 1 and (nx, ny) not in visited:
                    if dfs(nx, ny, visited):
                        return True
            return False
        
        # Check if there's a path from (0, 0) to (m - 1, n - 1)
        if not dfs(0, 0, set()):
            return True
        
        # Try flipping each cell (except start and end) and check for path
        for i in range(m):
            for j in range(n):
                if (i == 0 and j == 0) or (i == m - 1 and j == n - 1):
                    continue
                grid[i][j] ^= 1  # Flip the cell
                if not dfs(0, 0, set()):
                    return True
                grid[i][j] ^= 1  # Flip back
        
        return False