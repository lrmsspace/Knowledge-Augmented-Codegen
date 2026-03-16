# Source: https://leetcode.com/problems/maximum-trailing-zeros-in-a-cornered-path/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer array grid of size m x n, where each cell contains a positive integer.
#
# A cornered path is defined as a set of adjacent cells with at most one turn. More specifically, the path should exclusively move either horizontally or vertically up to the turn (if there is one), without returning to a previously visited cell. After the turn, the path will then move exclusively in the alternate direction: move vertically if it moved horizontally, and vice versa, also without returning to a previously visited cell.
#
# The product of a path is defined as the product of all the values in the path.
#
# Return the maximum number of trailing zeros in the product of a cornered path found in grid.
#
# Note:
#
#
# 	Horizontal movement means moving in either the left or right direction.
# 	Vertical movement means moving in either the up or down direction.
#
# Example:
# Input: grid = [[23,17,15,3,20],[8,1,20,27,11],[9,4,6,2,21],[40,9,1,10,6],[22,7,4,5,3]]
# Output: 3
# Explanation: The grid on the left shows a valid cornered path.
# It has a product of 15 * 20 * 6 * 1 * 10 = 18000 which has 3 trailing zeros.
# It can be shown that this is the maximum trailing zeros in the product of a cornered path.
#
# The grid in the middle is not a cornered path as it has more than one turn.
# The grid on the right is not a cornered path as it requires a return to a previously visited cell.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 105
# 	1 <= m * n <= 105
# 	1 <= grid[i][j] <= 1000
#
# Helpful references (internal KB):
# - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
#   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
#   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
#   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
#   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
#   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
# - Primality tests (number, enumeration, simulation)
#   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
#   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
#   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
#   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
#   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxTrailingZeros(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        
        def count_factors(x, factor):
            count = 0
            while x % factor == 0:
                x //= factor
                count += 1
            return count
        
        # Precompute the number of 2s and 5s in each cell
        twos = [[0] * n for _ in range(m)]
        fives = [[0] * n for _ in range(m)]
        
        for i in range(m):
            for j in range(n):
                twos[i][j] = count_factors(grid[i][j], 2)
                fives[i][j] = count_factors(grid[i][j], 5)
        
        # Prefix sums for rows and columns
        row_twos = [[0] * (n + 1) for _ in range(m)]
        row_fives = [[0] * (n + 1) for _ in range(m)]
        col_twos = [[0] * (m + 1) for _ in range(n)]
        col_fives = [[0] * (m + 1) for _ in range(n)]
        
        for i in range(m):
            for j in range(n):
                row_twos[i][j + 1] = row_twos[i][j] + twos[i][j]
                row_fives[i][j + 1] = row_fives[i][j] + fives[i][j]
        
        for j in range(n):
            for i in range(m):
                col_twos[j][i + 1] = col_twos[j][i] + twos[i][j]
                col_fives[j][i + 1] = col_fives[j][i] + fives[i][j]
        
        max_zeros = 0
        
        # Check all cornered paths
        for i in range(m):
            for j in range(n):
                # Up-Right
                if i > 0 and j < n - 1:
                    total_twos = col_twos[j][i] + row_twos[i][n] - row_twos[i][j + 1]
                    total_fives = col_fives[j][i] + row_fives[i][n] - row_fives[i][j + 1]
                    max_zeros = max(max_zeros, min(total_twos, total_fives))
                
                # Up-Left
                if i > 0 and j > 0:
                    total_twos = col_twos[j][i] + row_twos[i][j]
                    total_fives = col_fives[j][i] + row_fives[i][j]
                    max_zeros = max(max_zeros, min(total_twos, total_fives))
                
                # Down-Right
                if i < m - 1 and j < n - 1:
                    total_twos = col_twos[j][m] - col_twos[j][i + 1] + row_twos[i][n] - row_twos[i][j + 1]
                    total_fives = col_fives[j][m] - col_fives[j][i + 1] + row_fives[i][n] - row_fives[i][j + 1]
                    max_zeros = max(max_zeros, min(total_twos, total_fives))
                
                # Down-Left
                if i < m - 1 and j > 0:
                    total_twos = col_twos[j][m] - col_twos[j][i + 1] + row_twos[i][j]
                    total_fives = col_fives[j][m] - col_fives[j][i + 1] + row_fives[i][j]
                    max_zeros = max(max_zeros, min(total_twos, total_fives))
                        