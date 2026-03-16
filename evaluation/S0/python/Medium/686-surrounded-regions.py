# Source: https://leetcode.com/problems/surrounded-regions/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n matrix board containing letters 'X' and 'O', capture regions that are surrounded:
#
#
# 	Connect: A cell is connected to adjacent cells horizontally or vertically.
# 	Region: To form a region connect every 'O' cell.
# 	Surround: The region is surrounded with 'X' cells if you can connect the region with 'X' cells and none of the region cells are on the edge of the board.
#
#
# To capture a surrounded region, replace all 'O's with 'X's in-place within the original board. You do not need to return anything.
#
# Example:
# Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
#
# Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
#
# Explanation:
#
# In the above diagram, the bottom region is not captured because it is on the edge of the board and cannot be surrounded.
#
# Constraints:
# m == board.length
# 	n == board[i].length
# 	1 <= m, n <= 200
# 	board[i][j] is 'X' or 'O'.
#

class Solution(object):
    def solve(self, board):
        """
        :type board: List[List[str]]
        :rtype: None Do not return anything, modify board in-place instead.
        """
        if not board:
            return
        rows, cols = len(board), len(board[0])

        def dfs(r, c):
            if r < 0 or c < 0 or r >= rows or c >= cols or board[r][c] != 'O':
                return
            board[r][c] = 'E'  # Mark as escaped
            dfs(r + 1, c)
            dfs(r - 1, c)
            dfs(r, c + 1)
            dfs(r, c - 1)

        # Start from the borders and mark all connected 'O's as 'E'
        for r in range(rows):
            if board[r][0] == 'O':
                dfs(r, 0)
            if board[r][cols - 1] == 'O':
                dfs(r, cols - 1)

        for c in range(cols):
            if board[0][c] == 'O':
                dfs(0, c)
            if board[rows - 1][c] == 'O':
                dfs(rows - 1, c)

        # Flip all remaining 'O's to 'X's and 'E's back to 'O's
        for r in range(rows):
            for c in range(cols):
                if board[r][c] == 'O':
                    board[r][c] = 'X'
                elif board[r][c] == 'E':
                    board[r][c] = 'O'