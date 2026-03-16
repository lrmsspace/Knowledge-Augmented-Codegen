# Source: https://leetcode.com/problems/cherry-pickup-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a rows x cols matrix grid representing a field of cherries where grid[i][j] represents the number of cherries that you can collect from the (i, j) cell.
#
# You have two robots that can collect cherries for you:
#
#
# 	Robot #1 is located at the top-left corner (0, 0), and
# 	Robot #2 is located at the top-right corner (0, cols - 1).
#
#
# Return the maximum number of cherries collection using both robots by following the rules below:
#
#
# 	From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
# 	When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.
# 	When both robots stay in the same cell, only one takes the cherries.
# 	Both robots cannot move outside of the grid at any moment.
# 	Both robots should reach the bottom row in grid.
#
# Example:
# Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
# Output: 24
# Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
# Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
# Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
# Total of cherries: 12 + 12 = 24.
#
# Constraints:
# rows == grid.length
# 	cols == grid[i].length
# 	2 <= rows, cols <= 70
# 	0 <= grid[i][j] <= 100
#
# Helpful references (internal KB):
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
    def cherryPickup(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        rows, cols = len(grid), len(grid[0])
        dp = [[[-1] * cols for _ in range(cols)] for _ in range(rows)]
        
        def dfs(r, c1, c2):
            if c1 < 0 or c1 >= cols or c2 < 0 or c2 >= cols:
                return 0
            if dp[r][c1][c2] != -1:
                return dp[r][c1][c2]
            
            cherries = grid[r][c1]
            if c1 != c2:
                cherries += grid[r][c2]
            
            if r == rows - 1:
                dp[r][c1][c2] = cherries
                return cherries
            
            max_cherries = 0
            for new_c1 in [c1 - 1, c1, c1 + 1]:
                for new_c2 in [c2 - 1, c2, c2 + 1]:
                    max_cherries = max(max_cherries, dfs(r + 1, new_c1, new_c2))
            
            dp[r][c1][c2] = cherries + max_cherries
            return dp[r][c1][c2]
        
        return dfs(0, 0, cols - 1)