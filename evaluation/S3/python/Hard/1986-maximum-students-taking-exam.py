# Source: https://leetcode.com/problems/maximum-students-taking-exam/   |   Difficulty: Hard
#
# Problem Description:
# Given a m * n matrix seats  that represent seats distributions in a classroom. If a seat is broken, it is denoted by '#' character otherwise it is denoted by a '.' character.
#
# Students can see the answers of those sitting next to the left, right, upper left and upper right, but he cannot see the answers of the student sitting directly in front or behind him. Return the maximum number of students that can take the exam together without any cheating being possible.
#
# Students must be placed in seats in good condition.
#
# Example:
# Input: seats = [["#",".","#","#",".","#"],
#                 [".","#","#","#","#","."],
#                 ["#",".","#","#",".","#"]]
# Output: 4
# Explanation: Teacher can place 4 students in available seats so they don't cheat on the exam.
#
# Constraints:
# seats contains only characters '.' and'#'.
# 	m == seats.length
# 	n == seats[i].length
# 	1 <= m <= 8
# 	1 <= n <= 8
#
# Helpful references (internal KB):
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
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
    def maxStudents(self, seats):
        """
        :type seats: List[List[str]]
        :rtype: int
        """
        m, n = len(seats), len(seats[0])
        dp = [[0] * (1 << n) for _ in range(m + 1)]
        for i in range(1, m + 1):
            for mask in range(1 << n):
                if any((mask & (1 << j)) and seats[i - 1][j] == '#' for j in range(n)):
                    continue
                if mask & (mask >> 1):
                    continue
                dp[i][mask] = max(dp[i][mask], dp[i - 1][0])
                for prev_mask in range(1 << n):
                    if any((prev_mask & (1 << j)) and seats[i - 2][j] == '#' for j in range(n)):
                        continue
                    if mask & (prev_mask << 1) or mask & (prev_mask >> 1):
                        continue
                    dp[i][mask] = max(dp[i][mask], dp[i - 1][prev_mask])
                dp[i][mask] += bin(mask).count('1')
        return max(dp[m])