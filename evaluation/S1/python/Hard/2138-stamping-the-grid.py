# Source: https://leetcode.com/problems/stamping-the-grid/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n binary matrix grid where each cell is either 0 (empty) or 1 (occupied).
#
# You are then given stamps of size stampHeight x stampWidth. We want to fit the stamps such that they follow the given restrictions and requirements:
#
#
# 	Cover all the empty cells.
# 	Do not cover any of the occupied cells.
# 	We can put as many stamps as we want.
# 	Stamps can overlap with each other.
# 	Stamps are not allowed to be rotated.
# 	Stamps must stay completely inside the grid.
#
#
# Return true if it is possible to fit the stamps while following the given restrictions and requirements. Otherwise, return false.
#
# Example:
# Input: grid = [[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0]], stampHeight = 4, stampWidth = 3
# Output: true
# Explanation: We have two overlapping stamps (labeled 1 and 2 in the image) that are able to cover all the empty cells.
#
# Constraints:
# m == grid.length
# 	n == grid[r].length
# 	1 <= m, n <= 105
# 	1 <= m * n <= 2 * 105
# 	grid[r][c] is either 0 or 1.
# 	1 <= stampHeight, stampWidth <= 105
#
# Helpful references (internal KB):
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def possibleToStamp(self, grid, stampHeight, stampWidth):
        """
        :type grid: List[List[int]]
        :type stampHeight: int
        :type stampWidth: int
        :rtype: bool
        """
        # Step 1: Calculate the prefix sum of the grid to quickly determine if a submatrix contains any occupied cells.
        m, n = len(grid), len(grid[0])
        prefix_sum = [[0] * (n + 1) for _ in range(m + 1)]
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                prefix_sum[i][j] = grid[i - 1][j - 1] + prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1]
        
        # Step 2: Create a boolean matrix to mark where stamps can be placed.
        can_stamp = [[False] * n for _ in range(m)]
        
        for i in range(stampHeight, m + 1):
            for j in range(stampWidth, n + 1):
                # Check if the submatrix from (i-stampHeight, j-stampWidth) to (i-1, j-1) is empty
                total_cells = stampHeight * stampWidth
                occupied_cells = prefix_sum[i][j] - prefix_sum[i - stampHeight][j] - prefix_sum[i][j - stampWidth] + prefix_sum[i - stampHeight][j - stampWidth]
                
                if occupied_cells == 0:
                    can_stamp[i - stampHeight][j - stampWidth] = True
        
        # Step 3: Use a coverage matrix to mark which cells are covered by stamps.
        covered = [[False] * n for _ in range(m)]
        
        for i in range(m):
            for j in range(n):
                if can_stamp[i][j]:
                    for x in range(stampHeight):
                        for y in range(stampWidth):
                            covered[i + x][j + y] = True
        
        # Step 4: Check if all empty cells are covered.
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 0 and not covered[i][j]:
                    return False
        
        return True