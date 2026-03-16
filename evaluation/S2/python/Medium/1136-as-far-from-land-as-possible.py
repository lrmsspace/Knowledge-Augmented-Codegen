# Source: https://leetcode.com/problems/as-far-from-land-as-possible/   |   Difficulty: Medium
#
# Problem Description:
# Given an n x n grid containing only values 0 and 1, where 0 represents water and 1 represents land, find a water cell such that its distance to the nearest land cell is maximized, and return the distance. If no land or water exists in the grid, return -1.
#
# The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.
#
# Example:
# Input: grid = [[1,0,1],[0,0,0],[1,0,1]]
# Output: 2
# Explanation: The cell (1, 1) is as far as possible from all the land with distance 2.
#
# Constraints:
# n == grid.length
# 	n == grid[i].length
# 	1 <= n <= 100
# 	grid[i][j] is 0 or 1
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxDistance(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from collections import deque

        n = len(grid)
        queue = deque()

        # 将所有陆地单元格加入队列
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    queue.append((i, j))

        # 如果没有陆地或水域，返回 -1
        if not queue or len(queue) == n * n:
            return -1

        max_distance = -1
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

        while queue:
            x, y = queue.popleft()
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < n and 0 <= ny < n and grid[nx][ny] == 0:
                    grid[nx][ny] = grid[x][y] + 1  # 更新距离
                    max_distance = max(max_distance, grid[nx][ny] - 1)
                    queue.append((nx, ny))

        return max_distance