# Source: https://leetcode.com/problems/maximum-value-sum-by-placing-three-rooks-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a m x n 2D array board representing a chessboard, where board[i][j] represents the value of the cell (i, j).
#
# Rooks in the same row or column attack each other. You need to place three rooks on the chessboard such that the rooks do not attack each other.
#
# Return the maximum sum of the cell values on which the rooks are placed.
#
# Example:
# Input: board = [[-3,1,1,1],[-3,1,-3,1],[-3,2,1,1]]
#
# Output: 4
#
# Explanation:
#
#
#
# We can place the rooks in the cells (0, 2), (1, 3), and (2, 1) for a sum of 1 + 1 + 2 = 4.
#
# Constraints:
# 3 <= m == board.length <= 500
# 	3 <= n == board[i].length <= 500
# 	-109 <= board[i][j] <= 109
#

class Solution(object):
    def maximumValueSum(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        m, n = len(board), len(board[0])
        max_sum = float('-inf')
        for r1 in range(m):
            for r2 in range(r1 + 1, m):
                for r3 in range(r2 + 1, m):
                    row_values = []
                    for c in range(n):
                        total = board[r1][c] + board[r2][c] + board[r3][c]
                        row_values.append((total, c))
                    row_values.sort(reverse=True)
                    current_sum = row_values[0][0] + row_values[1][0] + row_values[2][0]
                    max_sum = max(max_sum, current_sum)
        return max_sum  