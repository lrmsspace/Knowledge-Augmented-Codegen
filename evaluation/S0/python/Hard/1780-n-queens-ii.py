# Source: https://leetcode.com/problems/n-queens-ii/   |   Difficulty: Hard
#
# Problem Description:
# The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
#
# Given an integer n, return the number of distinct solutions to the n-queens puzzle.
#
# Example:
# Input: n = 4
# Output: 2
# Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
#
# Constraints:
# 1 <= n <= 9
#

class Solution(object):
    def totalNQueens(self, n):
        """
        :type n: int
        :rtype: int
        """
        def backtrack(row, diagonals, anti_diagonals, cols):
            if row == n:
                return 1
            solutions = 0
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
                solutions += backtrack(row + 1, diagonals, anti_diagonals, cols)
                cols.remove(col)
                diagonals.remove(curr_diagonal)
                anti_diagonals.remove(curr_anti_diagonal)
            return solutions

        return backtrack(0, set(), set(), set())