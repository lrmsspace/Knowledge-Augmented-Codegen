# Source: https://leetcode.com/problems/find-the-safest-path-in-a-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:
#
#
# 	A cell containing a thief if grid[r][c] = 1
# 	An empty cell if grid[r][c] = 0
#
#
# You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in the grid, including cells containing thieves.
#
# The safeness factor of a path on the grid is defined as the minimum manhattan distance from any cell in the path to any thief in the grid.
#
# Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).
#
# An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.
#
# The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where |val| denotes the absolute value of val.
#
# Example:
# Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
# Output: 0
# Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves in cells (0, 0) and (n - 1, n - 1).
#
# Constraints:
# 1 <= grid.length == n <= 400
# 	grid[i].length == n
# 	grid[i][j] is either 0 or 1.
# 	There is at least one thief in the grid.
#

class Solution(object):
    def maximumSafenessFactor(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from collections import deque
        import heapq

        n = len(grid)
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        # Step 1: Multi-source BFS to calculate distance to nearest thief
        dist = [[float('inf')] * n for _ in range(n)]
        queue = deque()

        for r in range(n):
            for c in range(n):
                if grid[r][c] == 1:
                    dist[r][c] = 0
                    queue.append((r, c))

        while queue:
            r, c = queue.popleft()
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < n and 0 <= nc < n:
                    if dist[nr][nc] > dist[r][c] + 1:
                        dist[nr][nc] = dist[r][c] + 1
                        queue.append((nr, nc))

        # Step 2: Binary search on the safeness factor
        def canReach(safeness):
            if dist[0][0] < safeness:
                return False
            visited = [[False] * n for _ in range(n)]
            pq = [(-dist[0][0], 0, 0)]  # Max-heap based on distance
            visited[0][0] = True

            while pq:
                curr_dist, r, c = heapq.heappop(pq)
                curr_dist = -curr_dist

                if r == n - 1 and c == n - 1:
                    return True

                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < n and 0 <= nc < n and not visited[nr][nc]:
                        if dist[nr][nc] >= safeness:
                            visited[nr][nc] = True
                            heapq.heappush(pq, (-dist[nr][nc], nr, nc))

            return False

        left, right = 0, max(max(row) for row in dist)
        answer = 0

        while left <= right:
            mid = (left + right) // 2
            if canReach(mid):
                answer = mid
                left = mid +