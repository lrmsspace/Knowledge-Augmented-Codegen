# Source: https://leetcode.com/problems/transform-to-chessboard/   |   Difficulty: Hard
#
# Problem Description:
# You are given an n x n binary grid board. In each move, you can swap any two rows with each other, or any two columns with each other.
#
# Return the minimum number of moves to transform the board into a chessboard board. If the task is impossible, return -1.
#
# A chessboard board is a board where no 0's and no 1's are 4-directionally adjacent.
#
# Example:
# Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
# Output: 2
# Explanation: One potential sequence of moves is shown.
# The first move swaps the first and second column.
# The second move swaps the second and third row.
#
# Constraints:
# n == board.length
#  n == board[i].length
#  2 <= n <= 30
#  board[i][j] is either 0 or 1.
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
    def movesToChessboard(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        n = len(board)
        row_sum = [0] * n
        col_sum = [0] * n
        row_pattern = {}
        col_pattern = {}

        for i in range(n):
            for j in range(n):
                row_sum[i] += board[i][j]
                col_sum[j] += board[i][j]
                row_pattern[i] = row_pattern.get(i, 0) + (board[i][j] << j)
                col_pattern[j] = col_pattern.get(j, 0) + (board[i][j] << i)

        if not self.is_valid(row_sum, n) or not self.is_valid(col_sum, n):
            return -1

        row_moves = self.count_moves(row_pattern, n)
        col_moves = self.count_moves(col_pattern, n)

        return row_moves + col_moves