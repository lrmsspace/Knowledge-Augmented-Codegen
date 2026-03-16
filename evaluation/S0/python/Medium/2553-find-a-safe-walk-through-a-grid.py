# Source: https://leetcode.com/problems/find-a-safe-walk-through-a-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n binary matrix grid and an integer health.
#
# You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1).
#
# You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive.
#
# Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1.
#
# Return true if you can reach the final cell with a health value of 1 or more, and false otherwise.
#
# Example:
# Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1
#
# Output: true
#
# Explanation:
#
# The final cell can be reached safely by walking along the gray cells below.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 50
# 	2 <= m * n
# 	1 <= health <= m + n
# 	grid[i][j] is either 0 or 1.
#

class Solution(object):
    def findSafeWalk(self, grid, health):
        """
        :type grid: List[List[int]]
        :type health: int
        :rtype: bool
        """
        from collections import deque

        m, n = len(grid), len(grid[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        visited = [[[False] * (health + 1) for _ in range(n)] for _ in range(m)]
        queue = deque([(0, 0, health)])

        while queue:
            x, y, h = queue.popleft()

            if x == m - 1 and y == n - 1 and h > 0:
                return True

            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n:
                    nh = h - grid[nx][ny]
                    if nh > 0 and not visited[nx][ny][nh]:
                        visited[nx][ny][nh] = True
                        queue.append((nx, ny, nh))

        return False