# Source: https://leetcode.com/problems/largest-1-bordered-square/   |   Difficulty: Medium
#
# Problem Description:
# Given a 2D grid of 0s and 1s, return the number of elements in the largest square subgrid that has all 1s on its border, or 0 if such a subgrid doesn't exist in the grid.
#
# Example:
# Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
# Output: 9
#
# Constraints:
# 1 <= grid.length <= 100
# 	1 <= grid[0].length <= 100
# 	grid[i][j] is 0 or 1
#
# Helpful references (internal KB):
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
# - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
#   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
#   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
#   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
#   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
#   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def largest1BorderedSquare(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        if not grid or not grid[0]:
            return 0

        rows, cols = len(grid), len(grid[0])
        max_side = min(rows, cols)

        # Precompute the number of consecutive 1s to the right and down for each cell
        right = [[0] * cols for _ in range(rows)]
        down = [[0] * cols for _ in range(rows)]

        for r in range(rows - 1, -1, -1):
            for c in range(cols - 1, -1, -1):
                if grid[r][c] == 1:
                    right[r][c] = 1 + (right[r][c + 1] if c + 1 < cols else 0)
                    down[r][c] = 1 + (down[r + 1][c] if r + 1 < rows else 0)

        # Check for the largest square with all 1s on the border
        for side in range(max_side, 0, -1):
            for r in range(rows - side + 1):
                for c in range(cols - side + 1):
                    if (right[r][c] >= side and
                        down[r][c] >= side and
                        right[r + side - 1][c] >= side and
                        down[r][c + side - 1] >= side):
                        return side * side

        return 0