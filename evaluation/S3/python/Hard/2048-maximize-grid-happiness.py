# Source: https://leetcode.com/problems/maximize-grid-happiness/   |   Difficulty: Hard
#
# Problem Description:
# You are given four integers, m, n, introvertsCount, and extrovertsCount. You have an m x n grid, and there are two types of people: introverts and extroverts. There are introvertsCount introverts and extrovertsCount extroverts.
#
# You should decide how many people you want to live in the grid and assign each of them one grid cell. Note that you do not have to have all the people living in the grid.
#
# The happiness of each person is calculated as follows:
#
#
# 	Introverts start with 120 happiness and lose 30 happiness for each neighbor (introvert or extrovert).
# 	Extroverts start with 40 happiness and gain 20 happiness for each neighbor (introvert or extrovert).
#
#
# Neighbors live in the directly adjacent cells north, east, south, and west of a person's cell.
#
# The grid happiness is the sum of each person's happiness. Return the maximum possible grid happiness.
#
# Example:
# Input: m = 2, n = 3, introvertsCount = 1, extrovertsCount = 2
# Output: 240
# Explanation: Assume the grid is 1-indexed with coordinates (row, column).
# We can put the introvert in cell (1,1) and put the extroverts in cells (1,3) and (2,3).
# - Introvert at (1,1) happiness: 120 (starting happiness) - (0 * 30) (0 neighbors) = 120
# - Extrovert at (1,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
# - Extrovert at (2,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
# The grid happiness is 120 + 60 + 60 = 240.
# The above figure shows the grid in this example with each person's happiness. The introvert stays in the light green cell while the extroverts live on the light purple cells.
#
# Constraints:
# 1 <= m, n <= 5
# 	0 <= introvertsCount, extrovertsCount <= min(m * n, 6)
#
# Helpful references (internal KB):
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
# - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
#   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
#   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
#   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
#   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
#   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
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
    def getMaxGridHappiness(self, m, n, introvertsCount, extrovertsCount):
        """
        :type m: int
        :type n: int
        :type introvertsCount: int
        :type extrovertsCount: int
        :rtype: int
        """
        # 0: empty, 1: introvert, 2: extrovert
        @lru_cache(None)
        def dfs(i, j, introverts_left, extroverts_left, prev_row):
            if i == m:
                return 0
            if j == n:
                return dfs(i + 1, 0, introverts_left, extroverts_left, prev_row)

            max_happiness = dfs(i, j + 1, introverts_left, extroverts_left, prev_row)  # Skip cell

            for person in (1, 2):  # Try placing introvert or extrovert
                if (person == 1 and introverts_left == 0) or (person == 2 and extroverts_left == 0):
                    continue

                happiness = 120 if person == 1 else 40
                if j > 0:  # Check left neighbor
                    if prev_row[j - 1] == 1: happiness -= 30 if person == 1 else -20
                    elif prev_row[j - 1] == 2: happiness -= -20 if person == 1 else -20
                if i > 0:  # Check upper neighbor
                    if prev_row[j] == 1: happiness -= 30 if person == 1 else -20
                    elif prev_row[j] == 2: happiness -= -20 if person == 1 else -20

                new_prev_row = list(prev_row)
                new_prev_row[j] = person
                max_happiness = max(max_happiness,
                                    happiness + dfs(i, j + 1,
                                                    introverts_left - (person == 1),
                                                    extroverts_left - (person == 2),
                                                    tuple(new_prev_row)))

            return max_happiness

        return dfs(0, 0, introvertsCount, extrovertsCount, tuple([0] * n))