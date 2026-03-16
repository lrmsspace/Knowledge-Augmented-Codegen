# Source: https://leetcode.com/problems/available-captures-for-rook/   |   Difficulty: Easy
#
# Problem Description:
# You are given an 8 x 8 matrix representing a chessboard. There is exactly one white rook represented by 'R', some number of white bishops 'B', and some number of black pawns 'p'. Empty squares are represented by '.'.
#
# A rook can move any number of squares horizontally or vertically (up, down, left, right) until it reaches another piece or the edge of the board. A rook is attacking a pawn if it can move to the pawn's square in one move.
#
# Note: A rook cannot move through other pieces, such as bishops or pawns. This means a rook cannot attack a pawn if there is another piece blocking the path.
#
# Return the number of pawns the white rook is attacking.
#
# Example:
# Input: board = [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","R",".",".",".","p"],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
#
# Output: 3
#
# Explanation:
#
# In this example, the rook is attacking all the pawns.
#
# Constraints:
# board.length == 8
# 	board[i].length == 8
# 	board[i][j] is either 'R', '.', 'B', or 'p'
# 	There is exactly one cell with board[i][j] == 'R'
#

class Solution(object):
    def numRookCaptures(self, board):
        """
        :type board: List[List[str]]
        :rtype: int
        """
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        rook_position = None
        
        # Find the position of the rook
        for i in range(8):
            for j in range(8):
                if board[i][j] == 'R':
                    rook_position = (i, j)
                    break
            if rook_position:
                break
        
        captures = 0
        
        # Check each direction for pawns
        for direction in directions:
            x, y = rook_position
            dx, dy = direction
            
            while 0 <= x < 8 and 0 <= y < 8:
                if board[x][y] == 'B':  # Bishop blocks the path
                    break
                if board[x][y] == 'p':  # Pawn can be captured
                    captures += 1
                    break
                x += dx
                y += dy
        
        return captures