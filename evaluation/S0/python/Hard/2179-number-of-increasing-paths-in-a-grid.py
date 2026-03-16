# Source: https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n integer matrix grid, where you can move from a cell to any adjacent cell in all 4 directions.
#
# Return the number of strictly increasing paths in the grid such that you can start from any cell and end at any cell. Since the answer may be very large, return it modulo 109 + 7.
#
# Two paths are considered different if they do not have exactly the same sequence of visited cells.
#
# Example:
# Input: grid = [[1,1],[3,4]]
# Output: 8
# Explanation: The strictly increasing paths are:
# - Paths with length 1: [1], [1], [3], [4].
# - Paths with length 2: [1 -> 3], [1 -> 4], [3 -> 4].
# - Paths with length 3: [1 -> 3 -> 4].
# The total number of paths is 4 + 3 + 1 = 8.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 1000
# 	1 <= m * n <= 105
# 	1 <= grid[i][j] <= 105
#

class Solution(object):
    def countPaths(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        m, n = len(grid), len(grid[0])
        dp = [[-1] * n for _ in range(m)]

        def dfs(x, y):
            if dp[x][y] != -1:
                return dp[x][y]
            res = 1  # Count the path that starts and ends at (x, y)
            directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] > grid[x][y]:
                    res += dfs(nx, ny)
                    res %= MOD
            dp[x][y] = res
            return res

        total_paths = 0
        for i in range(m):
            for j in range(n):
                total_paths += dfs(i, j)
                total_paths %= MOD

        return total_paths