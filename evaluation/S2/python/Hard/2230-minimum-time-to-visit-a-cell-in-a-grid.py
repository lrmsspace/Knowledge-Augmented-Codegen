# Source: https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/   |   Difficulty: Hard
#
# Problem Description:
# You are given a m x n matrix grid consisting of non-negative integers where grid[row][col] represents the minimum time required to be able to visit the cell (row, col), which means you can visit the cell (row, col) only when the time you visit it is greater than or equal to grid[row][col].
#
# You are standing in the top-left cell of the matrix in the 0th second, and you must move to any adjacent cell in the four directions: up, down, left, and right. Each move you make takes 1 second.
#
# Return the minimum time required in which you can visit the bottom-right cell of the matrix. If you cannot visit the bottom-right cell, then return -1.
#
# Example:
# Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
# Output: 7
# Explanation: One of the paths that we can take is the following:
# - at t = 0, we are on the cell (0,0).
# - at t = 1, we move to the cell (0,1). It is possible because grid[0][1] <= 1.
# - at t = 2, we move to the cell (1,1). It is possible because grid[1][1] <= 2.
# - at t = 3, we move to the cell (1,2). It is possible because grid[1][2] <= 3.
# - at t = 4, we move to the cell (1,1). It is possible because grid[1][1] <= 4.
# - at t = 5, we move to the cell (1,2). It is possible because grid[1][2] <= 5.
# - at t = 6, we move to the cell (1,3). It is possible because grid[1][3] <= 6.
# - at t = 7, we move to the cell (2,3). It is possible because grid[2][3] <= 7.
# The final time is 7. It can be shown that it is the minimum time possible.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	2 <= m, n <= 1000
# 	4 <= m * n <= 105
# 	0 <= grid[i][j] <= 105
# 	grid[0][0] == 0
#
#
#  
# .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
# }
# .spoiler {overflow:hidden;}
# .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
# .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
# .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
#
# Helpful references (internal KB):
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
# - Hungarian algorithm for solving the assignment problem (matrix, graph, array, greedy, bfs, enumeration)
#   • When to use: Use when finding a minimum cost perfect matching in a bipartite graph, typically represented as an N x N cost matrix, where each row must be assigned to exactly one column.
#   • Idea: The Hungarian algorithm finds a minimum weight perfect matching in a bipartite graph, solving the assignment problem for an N x N cost matrix. It iteratively finds augmenting paths in an equality graph and adjusts potentials, achieving O(N^3) time complexity.
#   • Invariants: For all i, j, u[i] + v[j] <= A[i][j] (potential condition).; The current matching is always valid (each row/column used at most once).
#   • Tips: Understand the concept of potentials and their role in maintaining the equality graph.; The algorithm can be adapted for maximum profit problems by negating costs.
#   • Pitfalls: Incorrectly updating potentials can lead to non-optimal solutions or infinite loops.; Handling non-square matrices requires careful padding with dummy values.
# - Bellman-Ford Algorithm (graph, queue, bellman-ford, bfs)
#   • When to use: Use when finding shortest paths in a graph that may contain negative edge weights. It is also suitable for detecting the presence of negative cycles reachable from a source.
#   • Idea: The Bellman-Ford algorithm computes shortest paths from a single source to all other vertices in a weighted graph, even with negative edge weights. It iteratively relaxes all edges V-1 times, achieving O(VE) complexity.
#   • Invariants: After k iterations, dist[v] holds the shortest path from source to v using at most k edges.; If no negative cycle exists, dist[v] eventually converges to the true shortest path distance.
#   • Tips: Initialize source distance to 0 and all other distances to infinity.; Perform exactly V-1 relaxation passes over all edges to guarantee shortest paths if no negative cycles exist.
#   • Pitfalls: Incorrectly handling negative cycles can lead to infinite loops if not explicitly checked.; SPFA's worst-case time complexity remains O(VE), making it inefficient for certain graph structures.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumTime(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        if (m + n - 2) % 2 != grid[0][0] % 2:
            return -1

        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        visited = [[False] * n for _ in range(m)]
        min_heap = [(0, 0, 0)]  # (time, row, col)

        while min_heap:
            time, row, col = heapq.heappop(min_heap)
            if visited[row][col]:
                continue
            visited[row][col] = True

            if row == m - 1 and col == n - 1:
                return time

            for dr, dc in directions:
                new_row, new_col = row + dr, col + dc
                if 0 <= new_row < m and 0 <= new_col < n and not visited[new_row][new_col]:
                    next_time = max(time + 1, grid[new_row][new_col])
                    heapq.heappush(min_heap, (next_time, new_row, new_col))

        return -1