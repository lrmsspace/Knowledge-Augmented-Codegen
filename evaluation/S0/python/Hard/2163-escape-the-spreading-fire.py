# Source: https://leetcode.com/problems/escape-the-spreading-fire/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed 2D integer array grid of size m x n which represents a field. Each cell has one of three values:
#
#
# 	0 represents grass,
# 	1 represents fire,
# 	2 represents a wall that you and fire cannot pass through.
#
#
# You are situated in the top-left cell, (0, 0), and you want to travel to the safehouse at the bottom-right cell, (m - 1, n - 1). Every minute, you may move to an adjacent grass cell. After your move, every fire cell will spread to all adjacent cells that are not walls.
#
# Return the maximum number of minutes that you can stay in your initial position before moving while still safely reaching the safehouse. If this is impossible, return -1. If you can always reach the safehouse regardless of the minutes stayed, return 109.
#
# Note that even if the fire spreads to the safehouse immediately after you have reached it, it will be counted as safely reaching the safehouse.
#
# A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
#
# Example:
# Input: grid = [[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]
# Output: 3
# Explanation: The figure above shows the scenario where you stay in the initial position for 3 minutes.
# You will still be able to safely reach the safehouse.
# Staying for more than 3 minutes will not allow you to safely reach the safehouse.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	2 <= m, n <= 300
# 	4 <= m * n <= 2 * 104
# 	grid[i][j] is either 0, 1, or 2.
# 	grid[0][0] == grid[m - 1][n - 1] == 0
#

class Solution(object):
    def maximumMinutes(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from collections import deque
        import heapq

        m, n = len(grid), len(grid[0])
        fire_time = [[float('inf')] * n for _ in range(m)]
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        # Multi-source BFS for fire spread time
        fire_queue = deque()
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    fire_queue.append((i, j))
                    fire_time[i][j] = 0

        while fire_queue:
            x, y = fire_queue.popleft()
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] != 2:
                    if fire_time[nx][ny] > fire_time[x][y] + 1:
                        fire_time[nx][ny] = fire_time[x][y] + 1
                        fire_queue.append((nx, ny))

        # Binary search for maximum wait time
        def can_escape(wait_time):
            if wait_time >= fire_time[0][0]:
                return False
            pq = [(wait_time, 0, 0)]  # (time, x, y)
            visited = set((0, 0))

            while pq:
                time, x, y = heapq.heappop(pq)
                if (x, y) == (m - 1, n - 1):
                    return True
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] != 2:
                        next_time = time + 1
                        if next_time < fire_time[nx][ny] and (nx, ny) not in visited:
                            visited.add((nx, ny))
                            heapq.heappush(pq, (next_time, nx, ny))
            return False

        left, right = 0, m * n
        result = -1
        while left <= right:
            mid = (left + right) // 2
            if can_escape(mid):
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        return result if result != m * n else 10**9 