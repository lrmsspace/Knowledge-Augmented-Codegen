# Source: https://leetcode.com/problems/rotting-oranges/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n grid where each cell can have one of three values:
#
#
# 	0 representing an empty cell,
# 	1 representing a fresh orange, or
# 	2 representing a rotten orange.
#
#
# Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
#
# Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.
#
# Example:
# Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
# Output: 4
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 10
# 	grid[i][j] is 0, 1, or 2.
#

class Solution(object):
    def orangesRotting(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from collections import deque

        rows, cols = len(grid), len(grid[0])
        queue = deque()
        fresh_count = 0

        # Initialize the queue with all rotten oranges and count fresh oranges
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 2:
                    queue.append((r, c))
                elif grid[r][c] == 1:
                    fresh_count += 1

        # Directions for adjacent cells (up, down, left, right)
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        minutes_passed = 0

        # BFS to rot adjacent fresh oranges
        while queue and fresh_count > 0:
            minutes_passed += 1
            for _ in range(len(queue)):
                x, y = queue.popleft()
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < rows and 0 <= ny < cols and grid[nx][ny] == 1:
                        grid[nx][ny] = 2
                        fresh_count -= 1
                        queue.append((nx, ny))

        return minutes_passed if fresh_count == 0 else -1