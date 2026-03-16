# Source: https://leetcode.com/problems/shortest-bridge/   |   Difficulty: Medium
#
# Problem Description:
# You are given an n x n binary matrix grid where 1 represents land and 0 represents water.
#
# An island is a 4-directionally connected group of 1's not connected to any other 1's. There are exactly two islands in grid.
#
# You may change 0's to 1's to connect the two islands to form one island.
#
# Return the smallest number of 0's you must flip to connect the two islands.
#
# Example:
# Input: grid = [[0,1],[1,0]]
# Output: 1
#
# Constraints:
# n == grid.length == grid[i].length
# 	2 <= n <= 100
# 	grid[i][j] is either 0 or 1.
# 	There are exactly two islands in grid.
#

class Solution(object):
    def shortestBridge(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from collections import deque

        n = len(grid)
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

        def in_bounds(x, y):
            return 0 <= x < n and 0 <= y < n

        def dfs(x, y, visited, island):
            visited.add((x, y))
            island.append((x, y))
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if in_bounds(nx, ny) and (nx, ny) not in visited and grid[nx][ny] == 1:
                    dfs(nx, ny, visited, island)

        def bfs(island):
            queue = deque(island)
            visited = set(island)
            steps = 0

            while queue:
                for _ in range(len(queue)):
                    x, y = queue.popleft()
                    if grid[x][y] == 0:
                        return steps
                    for dx, dy in directions:
                        nx, ny = x + dx, y + dy
                        if in_bounds(nx, ny) and (nx, ny) not in visited:
                            visited.add((nx, ny))
                            queue.append((nx, ny))
                steps += 1

        visited = set()
        island1 = []
        found = False

        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1 and (i, j) not in visited:
                    dfs(i, j, visited, island1)
                    found = True
                    break
            if found:
                break

        return bfs(island1)