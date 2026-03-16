# Source: https://leetcode.com/problems/making-a-large-island/   |   Difficulty: Hard
#
# Problem Description:
# You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
#
# Return the size of the largest island in grid after applying this operation.
#
# An island is a 4-directionally connected group of 1s.
#
# Example:
# Input: grid = [[1,0],[0,1]]
# Output: 3
# Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
#
# Constraints:
# n == grid.length
# 	n == grid[i].length
# 	1 <= n <= 500
# 	grid[i][j] is either 0 or 1.
#

class Solution(object):
    def largestIsland(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        island_id = 2
        island_size = {}

        def dfs(x, y, id):
            if x < 0 or x >= n or y < 0 or y >= n or grid[x][y] != 1:
                return 0
            grid[x][y] = id
            size = 1
            size += dfs(x + 1, y, id)
            size += dfs(x - 1, y, id)
            size += dfs(x, y + 1, id)
            size += dfs(x, y - 1, id)
            return size

        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    size = dfs(i, j, island_id)
                    island_size[island_id] = size
                    island_id += 1

        max_island = max(island_size.values(), default=0)

        for i in range(n):
            for j in range(n):
                if grid[i][j] == 0:
                    seen = set()
                    size = 1
                    for x, y in [(i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)]:
                        if 0 <= x < n and 0 <= y < n and grid[x][y] > 1:
                            id = grid[x][y]
                            if id not in seen:
                                seen.add(id)
                                size += island_size[id]
                    max_island = max(max_island, size)

        return max_island