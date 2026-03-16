# Source: https://leetcode.com/problems/k-highest-ranked-items-within-a-price-range/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed 2D integer array grid of size m x n that represents a map of the items in a shop. The integers in the grid represent the following:
#
#
# 	0 represents a wall that you cannot pass through.
# 	1 represents an empty cell that you can freely move to and from.
# 	All other positive integers represent the price of an item in that cell. You may also freely move to and from these item cells.
#
#
# It takes 1 step to travel between adjacent grid cells.
#
# You are also given integer arrays pricing and start where pricing = [low, high] and start = [row, col] indicates that you start at the position (row, col) and are interested only in items with a price in the range of [low, high] (inclusive). You are further given an integer k.
#
# You are interested in the positions of the k highest-ranked items whose prices are within the given price range. The rank is determined by the first of these criteria that is different:
#
#
# 	Distance, defined as the length of the shortest path from the start (shorter distance has a higher rank).
# 	Price (lower price has a higher rank, but it must be in the price range).
# 	The row number (smaller row number has a higher rank).
# 	The column number (smaller column number has a higher rank).
#
#
# Return the k highest-ranked items within the price range sorted by their rank (highest to lowest). If there are fewer than k reachable items within the price range, return all of them.
#
# Example:
# Input: grid = [[1,2,0,1],[1,3,0,1],[0,2,5,1]], pricing = [2,5], start = [0,0], k = 3
# Output: [[0,1],[1,1],[2,1]]
# Explanation: You start at (0,0).
# With a price range of [2,5], we can take items from (0,1), (1,1), (2,1) and (2,2).
# The ranks of these items are:
# - (0,1) with distance 1
# - (1,1) with distance 2
# - (2,1) with distance 3
# - (2,2) with distance 4
# Thus, the 3 highest ranked items in the price range are (0,1), (1,1), and (2,1).
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 105
# 	1 <= m * n <= 105
# 	0 <= grid[i][j] <= 105
# 	pricing.length == 2
# 	2 <= low <= high <= 105
# 	start.length == 2
# 	0 <= row <= m - 1
# 	0 <= col <= n - 1
# 	grid[row][col] > 0
# 	1 <= k <= m * n
#

class Solution(object):
    def highestRankedKItems(self, grid, pricing, start, k):
        """
        :type grid: List[List[int]]
        :type pricing: List[int]
        :type start: List[int]
        :type k: int
        :rtype: List[List[int]]
        """
        from collections import deque
        m, n = len(grid), len(grid[0])
        low, high = pricing
        sr, sc = start
        visited = [[False]*n for _ in range(m)]
        visited[sr][sc] = True
        q = deque()
        q.append((sr, sc, 0))  # (row, col, distance)
        items = []

        while q:
            r, c, dist = q.popleft()
            if low <= grid[r][c] <= high:
                items.append((dist, grid[r][c], r, c))

            for dr, dc in [(-1,0),(1,0),(0,-1),(0,1)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and not visited[nr][nc] and grid[nr][nc] != 0:
                    visited[nr][nc] = True
                    q.append((nr, nc, dist + 1))

        items.sort()
        result = [[r, c] for _, _, r, c in items[:k]]
        return result