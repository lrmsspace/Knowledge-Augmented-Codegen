# Source: https://leetcode.com/problems/count-fertile-pyramids-in-a-land/   |   Difficulty: Hard
#
# Problem Description:
# A farmer has a rectangular grid of land with m rows and n columns that can be divided into unit cells. Each cell is either fertile (represented by a 1) or barren (represented by a 0). All cells outside the grid are considered barren.
#
# A pyramidal plot of land can be defined as a set of cells with the following criteria:
#
#
# 	The number of cells in the set has to be greater than 1 and all cells must be fertile.
# 	The apex of a pyramid is the topmost cell of the pyramid. The height of a pyramid is the number of rows it covers. Let (r, c) be the apex of the pyramid, and its height be h. Then, the plot comprises of cells (i, j) where r <= i <= r + h - 1 and c - (i - r) <= j <= c + (i - r).
#
#
# An inverse pyramidal plot of land can be defined as a set of cells with similar criteria:
#
#
# 	The number of cells in the set has to be greater than 1 and all cells must be fertile.
# 	The apex of an inverse pyramid is the bottommost cell of the inverse pyramid. The height of an inverse pyramid is the number of rows it covers. Let (r, c) be the apex of the pyramid, and its height be h. Then, the plot comprises of cells (i, j) where r - h + 1 <= i <= r and c - (r - i) <= j <= c + (r - i).
#
#
# Some examples of valid and invalid pyramidal (and inverse pyramidal) plots are shown below. Black cells indicate fertile cells.
#
# Given a 0-indexed m x n binary matrix grid representing the farmland, return the total number of pyramidal and inverse pyramidal plots that can be found in grid.
#
# Example:
# Input: grid = [[0,1,1,0],[1,1,1,1]]
# Output: 2
# Explanation: The 2 possible pyramidal plots are shown in blue and red respectively.
# There are no inverse pyramidal plots in this grid. 
# Hence total number of pyramidal and inverse pyramidal plots is 2 + 0 = 2.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 1000
# 	1 <= m * n <= 105
# 	grid[i][j] is either 0 or 1.
#
# Helpful references (internal KB):
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Binomial Coefficients (number, enumeration)
#   • When to use: Use when needing to calculate multiple binomial coefficients or when a single coefficient is required and N and K are not excessively large, allowing for table precomputation.
#   • Idea: This method computes binomial coefficients C(n, k) using Pascal's recurrence relation C(n, k) = C(n-1, k-1) + C(n-1, k), typically building a table. It has a time complexity of O(N*K) or O(N^2) for building the full triangle up to N.
#   • Invariants: C[i][0] is always 1 for any row i.; C[i][i] is always 1 for any row i.
#   • Tips: Intermediate results for Pascal's Triangle never exceed the final answer, simplifying overflow checks if not using modular arithmetic.; Each new table element requires only one addition, making it computationally efficient per element.
#   • Pitfalls: Building the entire Pascal's Triangle for a single C(N, K) can be slow for large N and K, as it computes many unnecessary values.; Directly computing C(N, K) using factorials can lead to overflow issues for large N, even if the final result fits.
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countPyramids(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        dp_up = [[0] * n for _ in range(m)]
        dp_down = [[0] * n for _ in range(m)]

        # Calculate dp_up (pyramids)
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    if i > 0 and j > 0 and j < n - 1:
                        dp_up[i][j] = min(dp_up[i-1][j-1], dp_up[i-1][j], dp_up[i-1][j+1]) + 1
                    else:
                        dp_up[i][j] = 1

        # Calculate dp_down (inverse pyramids)
        for i in range(m-1, -1, -1):
            for j in range(n):
                if grid[i][j] == 1:
                    if i < m - 1 and j > 0 and j < n - 1:
                        dp_down[i][j] = min(dp_down[i+1][j-1], dp_down[i+1][j], dp_down[i+1][j+1]) + 1
                    else:
                        dp_down[i][j] = 1

        count = 0
        for i in range(m):
            for j in range(n):
                if dp_up[i][j] > 1:
                    count += dp_up[i][j] - 1
                if dp_down[i][j] > 1:
                    count += dp_down[i][j] - 1

        return count