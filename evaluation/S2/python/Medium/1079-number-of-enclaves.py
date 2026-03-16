# Source: https://leetcode.com/problems/number-of-enclaves/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.
#
# A move consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.
#
# Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.
#
# Example:
# Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
# Output: 3
# Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 500
# 	grid[i][j] is either 0 or 1.
#
# Helpful references (internal KB):
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
# - Search for connected components in a graph (graph, dfs, bfs, enumeration)
#   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
#   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
#   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
#   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
#   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numEnclaves(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        if not grid:
            return 0

        rows, cols = len(grid), len(grid[0])
        visited = [[False] * cols for _ in range(rows)]

        def dfs(r, c):
            if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] == 0 or visited[r][c]:
                return 0
            visited[r][c] = True
            return 1 + dfs(r + 1, c) + dfs(r - 1, c) + dfs(r, c + 1) + dfs(r, c - 1)

        # Mark land cells connected to the boundary as visited
        for i in range(rows):
            for j in range(cols):
                if (i == 0 or i == rows - 1 or j == 0 or j == cols - 1) and grid[i][j] == 1 and not visited[i][j]:
                    dfs(i, j)

        # Count enclaved land cells
        enclave_count = 0
        for i in range(1, rows - 1):
            for j in range(1, cols - 1):
                if grid[i][j] == 1 and not visited[i][j]:
                    enclave_count += dfs(i, j)

        return enclave_count