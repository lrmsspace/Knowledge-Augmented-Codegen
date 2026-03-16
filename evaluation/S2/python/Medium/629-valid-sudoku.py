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
# - N/A
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
        # Check rows
        for row in board:
            if not self.is_valid_group(row):
                return False

        # Check columns
        for col in zip(*board):
            if not self.is_valid_group(col):
                return False

        # Check 3x3 sub-boxes
        for i in range(3):
            for j in range(3):
                box = [board[x][y] for x in range(i*3, (i+1)*3) for y in range(j*3, (j+1)*3)]
                if not self.is_valid_group(box):
                    return False

        return True