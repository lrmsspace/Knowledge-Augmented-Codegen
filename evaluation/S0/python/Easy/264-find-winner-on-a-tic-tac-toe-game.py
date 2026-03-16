# Source: https://leetcode.com/problems/find-winner-on-a-tic-tac-toe-game/   |   Difficulty: Easy
#
# Problem Description:
# Tic-tac-toe is played by two players A and B on a 3 x 3 grid. The rules of Tic-Tac-Toe are:
#
#
# 	Players take turns placing characters into empty squares ' '.
# 	The first player A always places 'X' characters, while the second player B always places 'O' characters.
# 	'X' and 'O' characters are always placed into empty squares, never on filled ones.
# 	The game ends when there are three of the same (non-empty) character filling any row, column, or diagonal.
# 	The game also ends if all squares are non-empty.
# 	No more moves can be played if the game is over.
#
#
# Given a 2D integer array moves where moves[i] = [rowi, coli] indicates that the ith move will be played on grid[rowi][coli]. return the winner of the game if it exists (A or B). In case the game ends in a draw return "Draw". If there are still movements to play return "Pending".
#
# You can assume that moves is valid (i.e., it follows the rules of Tic-Tac-Toe), the grid is initially empty, and A will play first.
#
# Example:
# Input: moves = [[0,0],[2,0],[1,1],[2,1],[2,2]]
# Output: "A"
# Explanation: A wins, they always play first.
#
# Constraints:
# 1 <= moves.length <= 9
# 	moves[i].length == 2
# 	0 <= rowi, coli <= 2
# 	There are no repeated elements on moves.
# 	moves follow the rules of tic tac toe.
#

class Solution(object):
    def tictactoe(self, moves):
        """
        :type moves: List[List[int]]
        :rtype: str
        """
        board = [[''] * 3 for _ in range(3)]
        
        for i, move in enumerate(moves):
            row, col = move
            if i % 2 == 0:
                board[row][col] = 'X'  # Player A
            else:
                board[row][col] = 'O'  # Player B
        
        # Check rows and columns
        for i in range(3):
            if board[i][0] == board[i][1] == board[i][2] != '':
                return 'A' if board[i][0] == 'X' else 'B'
            if board[0][i] == board[1][i] == board[2][i] != '':
                return 'A' if board[0][i] == 'X' else 'B'
        
        # Check diagonals
        if board[0][0] == board[1][1] == board[2][2] != '':
            return 'A' if board[0][0] == 'X' else 'B'
        if board[0][2] == board[1][1] == board[2][0] != '':
            return 'A' if board[0][2] == 'X' else 'B'
        
        # Check for draw or pending
        if len(moves) == 9:
            return "Draw"
        else:
            return "Pending"