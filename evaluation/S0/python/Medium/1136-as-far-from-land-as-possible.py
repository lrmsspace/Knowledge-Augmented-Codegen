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

class Solution(object):
    def maxDistance(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from collections import deque
        
        n = len(grid)
        queue = deque()
        
        # Add all land cells to the queue
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    queue.append((i, j))
        
        # If there is no land or water, return -1
        if len(queue) == 0 or len(queue) == n * n:
            return -1
        
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        distance = -1
        
        # Perform multi-source BFS
        while queue:
            distance += 1
            for _ in range(len(queue)):
                x, y = queue.popleft()
                
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    
                    if 0 <= nx < n and 0 <= ny < n and grid[nx][ny] == 0:
                        grid[nx][ny] = 1  # Mark as visited
                        queue.append((nx, ny))
        
        return distance