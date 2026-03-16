# Source: https://leetcode.com/problems/n-queens/   |   Difficulty: Hard
#
# Problem Description:
# The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
#
# Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
#
# Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.
#
# Example:
# Input: n = 4
# Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
# Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
#
# Constraints:
# 1 <= n <= 9
#

class Solution(object):
    def solveNQueens(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """
        def backtrack(row, diagonals, anti_diagonals, cols, state):
            if row == n:
                board = []
                for r in state:
                    board.append("".join(r))
                result.append(board)
                return
            
            for col in range(n):
                curr_diagonal = row - col
                curr_anti_diagonal = row + col
                
                if (col in cols or 
                    curr_diagonal in diagonals or 
                    curr_anti_diagonal in anti_diagonals):
                    continue
                
                cols.add(col)
                diagonals.add(curr_diagonal)
                anti_diagonals.add(curr_anti_diagonal)
                state[row][col] = 'Q'
                
                backtrack(row + 1, diagonals, anti_diagonals, cols, state)
                
                cols.remove(col)
                diagonals.remove(curr_diagonal)
                anti_diagonals.remove(curr_anti_diagonal)
                state[row][col] = '.'
        
        result = []
        empty_board = [['.' for _ in range(n)] for _ in range(n)]
        backtrack(0, set(), set(), set(), empty_board)
        return result