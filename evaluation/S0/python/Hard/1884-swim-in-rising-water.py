# Source: https://leetcode.com/problems/swim-in-rising-water/   |   Difficulty: Hard
#
# Problem Description:
# You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).
#
# It starts raining, and water gradually rises over time. At time t, the water level is t, meaning any cell with elevation less than equal to t is submerged or reachable.
#
# You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.
#
# Return the minimum time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).
#
# Example:
# Input: grid = [[0,2],[1,3]]
# Output: 3
# Explanation:
# At time 0, you are in grid location (0, 0).
# You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
# You cannot reach point (1, 1) until time 3.
# When the depth of water is 3, we can swim anywhere inside the grid.
#
# Constraints:
# n == grid.length
# 	n == grid[i].length
# 	1 <= n <= 50
# 	0 <= grid[i][j] < n2
# 	Each value grid[i][j] is unique.
#

class Solution(object):
    def swimInWater(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        left, right = grid[0][0], n * n - 1

        def canReach(t):
            visited = [[False] * n for _ in range(n)]
            directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

            def dfs(x, y):
                if x == n - 1 and y == n - 1:
                    return True
                visited[x][y] = True
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < n and 0 <= ny < n and not visited[nx][ny] and grid[nx][ny] <= t:
                        if dfs(nx, ny):
                            return True
                return False

            return dfs(0, 0)

        while left < right:
            mid = (left + right) // 2
            if canReach(mid):
                right = mid
            else:
                left = mid + 1

        return left