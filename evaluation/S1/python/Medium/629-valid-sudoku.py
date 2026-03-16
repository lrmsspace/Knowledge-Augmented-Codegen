# Source: https://leetcode.com/problems/valid-sudoku/   |   Difficulty: Medium
#
# Problem Description:
# Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
#
#
# 	Each row must contain the digits 1-9 without repetition.
# 	Each column must contain the digits 1-9 without repetition.
# 	Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
#
#
# Note:
#
#
# 	A Sudoku board (partially filled) could be valid but is not necessarily solvable.
# 	Only the filled cells need to be validated according to the mentioned rules.
#
# Example:
# Input: board = 
# [["5","3",".",".","7",".",".",".","."]
# ,["6",".",".","1","9","5",".",".","."]
# ,[".","9","8",".",".",".",".","6","."]
# ,["8",".",".",".","6",".",".",".","3"]
# ,["4",".",".","8",".","3",".",".","1"]
# ,["7",".",".",".","2",".",".",".","6"]
# ,[".","6",".",".",".",".","2","8","."]
# ,[".",".",".","4","1","9",".",".","5"]
# ,[".",".",".",".","8",".",".","7","9"]]
# Output: true
#
# Constraints:
# board.length == 9
# 	board[i].length == 9
# 	board[i][j] is a digit 1-9 or '.'.
#
# Helpful references (internal KB):
# - Submask Enumeration
#  (number, bitset, enumeration, bitmask-dp)
#   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
#   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
#   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
#   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
#   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
# - Gauss method for solving system of linea (bitset, matrix, simulation)
#   • When to use: Use when determining the number of solutions (zero, one, or infinite) for a system of linear equations, or to find the unique solution if it exists. It is suitable for solving systems represented as an augmented matrix.
#   • Idea: Gaussian elimination systematically transforms an augmented matrix into row echelon form using elementary row operations to solve a system of linear equations. It determines the existence and values of solutions in O(N^3) time for an N x N system.
#   • Invariants: The submatrix formed by rows 0 to current_row - 1 is in row echelon form.; For the current column, all elements below the pivot in previous columns are zero.
#   • Tips: Use a small epsilon for floating-point comparisons to handle precision issues.; Implement partial pivoting to enhance numerical stability by selecting the largest absolute value.
#   • Pitfalls: Failing to account for floating-point precision errors can lead to incorrect results.; Improper handling of free variables can misrepresent infinite solution sets.
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
    def isValidSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        """
        rows = [set() for _ in range(9)]
        cols = [set() for _ in range(9)]
        boxes = [set() for _ in range(9)]
        
        for r in range(9):
            for c in range(9):
                num = board[r][c]
                if num == '.':
                    continue
                
                box_index = (r // 3) * 3 + (c // 3)
                
                if (num in rows[r]) or (num in cols[c]) or (num in boxes[box_index]):
                    return False
                
                rows[r].add(num)
                cols[c].add(num)
                boxes[box_index].add(num)
        
        return True