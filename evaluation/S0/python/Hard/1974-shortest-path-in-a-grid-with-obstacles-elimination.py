# Source: https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle). You can move up, down, left, or right from and to an empty cell in one step.
#
# Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1) given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.
#
# Example:
# Input: grid = [[0,0,0],[1,1,0],[0,0,0],[0,1,1],[0,0,0]], k = 1
# Output: 6
# Explanation: 
# The shortest path without eliminating any obstacle is 10.
# The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 40
# 	1 <= k <= m * n
# 	grid[i][j] is either 0 or 1.
# 	grid[0][0] == grid[m - 1][n - 1] == 0
#

class Solution(object):
    def shortestPath(self, grid, k):
        """
        :type grid: List[List[int]]
        :type k: int
        :rtype: int
        """
        from collections import deque

        m, n = len(grid), len(grid[0])
        if k >= m + n - 2:
            return m + n - 2

        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        queue = deque([(0, 0, 0, k)])  # (x, y, steps, remaining_k)
        visited = set((0, 0, k))

        while queue:
            x, y, steps, remaining_k = queue.popleft()

            if x == m - 1 and y == n - 1:
                return steps

            for dx, dy in directions:
                nx, ny = x + dx, y + dy

                if 0 <= nx < m and 0 <= ny < n:
                    nk = remaining_k - grid[nx][ny]
                    if nk >= 0 and (nx, ny, nk) not in visited:
                        visited.add((nx, ny, nk))
                        queue.append((nx, ny, steps + 1, nk))

        return -1