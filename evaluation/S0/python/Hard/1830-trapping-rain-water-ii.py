# Source: https://leetcode.com/problems/trapping-rain-water-ii/   |   Difficulty: Hard
#
# Problem Description:
# Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
#
# Example:
# Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
# Output: 4
# Explanation: After the rain, water is trapped between the blocks.
# We have two small ponds 1 and 3 units trapped.
# The total volume of water trapped is 4.
#
# Constraints:
# m == heightMap.length
# 	n == heightMap[i].length
# 	1 <= m, n <= 200
# 	0 <= heightMap[i][j] <= 2 * 104
#

class Solution(object):
    def trapRainWater(self, heightMap):
        """
        :type heightMap: List[List[int]]
        :rtype: int
        """
        if not heightMap or not heightMap[0]:
            return 0

        import heapq

        m, n = len(heightMap), len(heightMap[0])
        visited = [[False] * n for _ in range(m)]
        heap = []

        # Add all the boundary cells to the heap
        for i in range(m):
            for j in range(n):
                if i == 0 or i == m - 1 or j == 0 or j == n - 1:
                    heapq.heappush(heap, (heightMap[i][j], i, j))
                    visited[i][j] = True

        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        water_trapped = 0
        max_height = float('-inf')

        while heap:
            height, x, y = heapq.heappop(heap)
            max_height = max(max_height, height)

            for dx, dy in directions:
                nx, ny = x + dx, y + dy

                if 0 <= nx < m and 0 <= ny < n and not visited[nx][ny]:
                    visited[nx][ny] = True
                    if heightMap[nx][ny] < max_height:
                        water_trapped += max_height - heightMap[nx][ny]
                    heapq.heappush(heap, (heightMap[nx][ny], nx, ny))

        return water_trapped