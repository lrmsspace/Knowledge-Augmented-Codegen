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

class Solution(object):
    def movesToChessboard(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        n = len(board)
        
        row_sum = sum(board[0])
        col_sum = sum(board[i][0] for i in range(n))
        
        row_swap = sum(board[0][i] == i % 2 for i in range(n))
        col_swap = sum(board[i][0] == i % 2 for i in range(n))
        
        for i in range(n):
            for j in range(n):
                if board[0][0] ^ board[i][0] ^ board[0][j] ^ board[i][j]:
                    return -1
        
        if n % 2:
            if row_sum not in [n // 2, n // 2 + 1]:
                return -1
            if col_sum not in [n // 2, n // 2 + 1]:
                return -1
            if row_swap % 2:
                row_swap = n - row_swap
            if col_swap % 2:
                col_swap = n - col_swap
        else:
            if row_sum != n // 2 or col_sum != n // 2:
                return -1
            row_swap = min(row_swap, n - row_swap)
            col_swap = min(col_swap, n - col_swap)
        
        return (row_swap + col_swap) // 2