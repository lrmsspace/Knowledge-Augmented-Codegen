# Source: https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n integer matrix grid and an array queries of size k.
#
# Find an array answer of size k such that for each integer queries[i] you start in the top left cell of the matrix and repeat the following process:
#
#
# 	If queries[i] is strictly greater than the value of the current cell that you are in, then you get one point if it is your first time visiting this cell, and you can move to any adjacent cell in all 4 directions: up, down, left, and right.
# 	Otherwise, you do not get any points, and you end this process.
#
#
# After the process, answer[i] is the maximum number of points you can get. Note that for each query you are allowed to visit the same cell multiple times.
#
# Return the resulting array answer.
#
# Example:
# Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
# Output: [5,8,1]
# Explanation: The diagrams above show which cells we visit to get points for each query.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	2 <= m, n <= 1000
# 	4 <= m * n <= 105
# 	k == queries.length
# 	1 <= k <= 104
# 	1 <= grid[i][j], queries[i] <= 106
#

class Solution(object):
    def maxPoints(self, grid, queries):
        """
        :type grid: List[List[int]]
        :type queries: List[int]
        :rtype: List[int]
        """
        import heapq

        m, n = len(grid), len(grid[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        result = []
        max_heap = []
        visited = [[False] * n for _ in range(m)]
        visited[0][0] = True
        heapq.heappush(max_heap, (grid[0][0], 0, 0))
        current_count = 0
        sorted_queries = sorted((val, idx) for idx, val in enumerate(queries))
        answers = [0] * len(queries)
        heap_index = 0

        for query_value, original_index in sorted_queries:
            while max_heap and max_heap[0][0] < query_value:
                value, x, y = heapq.heappop(max_heap)
                current_count += 1

                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < m and 0 <= ny < n and not visited[nx][ny]:
                        visited[nx][ny] = True
                        heapq.heappush(max_heap, (grid[nx][ny], nx, ny))

            answers[original_index] = current_count

        return answers