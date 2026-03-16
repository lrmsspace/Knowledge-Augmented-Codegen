# Source: https://leetcode.com/problems/valid-tic-tac-toe-state/   |   Difficulty: Medium
#
# Problem Description:
# Given a Tic-Tac-Toe board as a string array board, return true if and only if it is possible to reach this board position during the course of a valid tic-tac-toe game.
#
# The board is a 3 x 3 array that consists of characters ' ', 'X', and 'O'. The ' ' character represents an empty square.
#
# Here are the rules of Tic-Tac-Toe:
#
#
# 	Players take turns placing characters into empty squares ' '.
# 	The first player always places 'X' characters, while the second player always places 'O' characters.
# 	'X' and 'O' characters are always placed into empty squares, never filled ones.
# 	The game ends when there are three of the same (non-empty) character filling any row, column, or diagonal.
# 	The game also ends if all squares are non-empty.
# 	No more moves can be played if the game is over.
#
# Example:
# Input: board = ["O  ","   ","   "]
# Output: false
# Explanation: The first player always plays "X".
#
# Constraints:
# board.length == 3
# 	board[i].length == 3
# 	board[i][j] is either 'X', 'O', or ' '.
#

class Solution(object):
    def validTicTacToe(self, board):
        """
        :type board: List[str]
        :rtype: bool
        """
        x_count = sum(row.count('X') for row in board)
        o_count = sum(row.count('O') for row in board)

        def win(player):
            for i in range(3):
                if all(board[i][j] == player for j in range(3)):
                    return True
                if all(board[j][i] == player for j in range(3)):
                    return True
            if all(board[i][i] == player for i in range(3)):
                return True
            if all(board[i][2 - i] == player for i in range(3)):
                return True
            return False

        if o_count not in {x_count - 1, x_count}:
            return False
        if win('X') and x_count != o_count + 1:
            return False
        if win('O') and x_count != o_count:
            return False
        return True