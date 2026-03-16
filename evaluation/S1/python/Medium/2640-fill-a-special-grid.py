# Source: https://leetcode.com/problems/fill-a-special-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given a non-negative integer n representing a 2n x 2n grid. You must fill the grid with integers from 0 to 22n - 1 to make it special. A grid is special if it satisfies all the following conditions:
#
#
# 	All numbers in the top-right quadrant are smaller than those in the bottom-right quadrant.
# 	All numbers in the bottom-right quadrant are smaller than those in the bottom-left quadrant.
# 	All numbers in the bottom-left quadrant are smaller than those in the top-left quadrant.
# 	Each of its quadrants is also a special grid.
#
#
# Return the special 2n x 2n grid.
#
# Note: Any 1x1 grid is special.
#
# Example:
# Input: n = 0
#
# Output: [[0]]
#
# Explanation:
#
# The only number that can be placed is 0, and there is only one possible position in the grid.
#
# Constraints:
# 0 <= n <= 10
#
# Helpful references (internal KB):
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
# - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
#   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
#   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
#   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
#   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
#   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def specialGrid(self, n):
        """
        :type n: int
        :rtype: List[List[int]]
        """
        size = 2 ** n
        grid = [[0] * size for _ in range(size)]
        
        def fill_grid(x, y, length, start):
            if length == 1:
                grid[x][y] = start
                return
            
            half = length // 2
            fill_grid(x, y + half, half, start)  # Top-right
            fill_grid(x + half, y + half, half, start + half * half)  # Bottom-right
            fill_grid(x + half, y, half, start + 2 * half * half)  # Bottom-left
            fill_grid(x, y, half, start + 3 * half * half)  # Top-left
        
        fill_grid(0, 0, size, 0)
        return grid