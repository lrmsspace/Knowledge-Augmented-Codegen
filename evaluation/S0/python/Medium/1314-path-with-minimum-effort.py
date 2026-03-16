# Source: https://leetcode.com/problems/path-with-minimum-effort/   |   Difficulty: Medium
#
# Problem Description:
# You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of cell (row, col). You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.
#
# A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.
#
# Return the minimum effort required to travel from the top-left cell to the bottom-right cell.
#
# Example:
# Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
# Output: 2
# Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
# This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.
#
# Constraints:
# rows == heights.length
# 	columns == heights[i].length
# 	1 <= rows, columns <= 100
# 	1 <= heights[i][j] <= 106
#

class Solution(object):
    def minimumEffortPath(self, heights):
        """
        :type heights: List[List[int]]
        :rtype: int
        """
        import heapq

        rows, cols = len(heights), len(heights[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        effort = [[float('inf')] * cols for _ in range(rows)]
        effort[0][0] = 0
        min_heap = [(0, 0, 0)]  # (effort, row, col)

        while min_heap:
            current_effort, x, y = heapq.heappop(min_heap)

            if x == rows - 1 and y == cols - 1:
                return current_effort

            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < rows and 0 <= ny < cols:
                    next_effort = max(current_effort, abs(heights[nx][ny] - heights[x][y]))
                    if next_effort < effort[nx][ny]:
                        effort[nx][ny] = next_effort
                        heapq.heappush(min_heap, (next_effort, nx, ny))

        return 0