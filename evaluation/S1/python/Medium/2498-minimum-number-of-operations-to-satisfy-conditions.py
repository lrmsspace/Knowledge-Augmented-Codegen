# Source: https://leetcode.com/problems/minimum-number-of-operations-to-satisfy-conditions/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D matrix grid of size m x n. In one operation, you can change the value of any cell to any non-negative number. You need to perform some operations such that each cell grid[i][j] is:
#
#
# 	Equal to the cell below it, i.e. grid[i][j] == grid[i + 1][j] (if it exists).
# 	Different from the cell to its right, i.e. grid[i][j] != grid[i][j + 1] (if it exists).
#
#
# Return the minimum number of operations needed.
#
# Example:
# Input: grid = [[1,0,2],[1,0,2]]
#
# Output: 0
#
# Explanation:
#
#
#
# All the cells in the matrix already satisfy the properties.
#
# Constraints:
# 1 <= n, m <= 1000
# 	0 <= grid[i][j] <= 9
#
# Helpful references (internal KB):
# - Knuth's Optimization (array, interval, dp-2d)
#   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
#   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
#   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
#   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
#   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Counting labeled graphs (number, dp-2d, counting, recursion)
#   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
#   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
#   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
#   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
#   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumOperations(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        INF = float('inf')
        
        # Precompute cost to change each column to all 0s or all 1s
        cost = [[0] * n for _ in range(2)]
        for j in range(n):
            for i in range(m):
                if grid[i][j] == 0:
                    cost[1][j] += 1  # Cost to make column j all 1s
                else:
                    cost[0][j] += 1  # Cost to make column j all 0s
        
        # DP arrays
        dp0 = [INF] * n  # dp0[j]: min cost to satisfy conditions up to column j with column j as 0s
        dp1 = [INF] * n  # dp1[j]: min cost to satisfy conditions up to column j with column j as 1s
        
        # Base case
        dp0[0] = cost[0][0]
        dp1[0] = cost[1][0]
        
        for j in range(1, n):
            # If current column is 0s, previous must be 1s
            dp0[j] = dp1[j-1] + cost[0][j]
            # If current column is 1s, previous must be 0s
            dp1[j] = dp0[j-1] + cost[1][j]
        
        return min(dp0[n-1], dp1[n-1])