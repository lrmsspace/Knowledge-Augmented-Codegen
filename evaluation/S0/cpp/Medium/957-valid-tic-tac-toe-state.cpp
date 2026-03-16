// Source: https://leetcode.com/problems/valid-tic-tac-toe-state/   |   Difficulty: Medium
//
// Problem Description:
// Given a Tic-Tac-Toe board as a string array board, return true if and only if it is possible to reach this board position during the course of a valid tic-tac-toe game.
//
// The board is a 3 x 3 array that consists of characters ' ', 'X', and 'O'. The ' ' character represents an empty square.
//
// Here are the rules of Tic-Tac-Toe:
//
//
// 	Players take turns placing characters into empty squares ' '.
// 	The first player always places 'X' characters, while the second player always places 'O' characters.
// 	'X' and 'O' characters are always placed into empty squares, never filled ones.
// 	The game ends when there are three of the same (non-empty) character filling any row, column, or diagonal.
// 	The game also ends if all squares are non-empty.
// 	No more moves can be played if the game is over.
//
// Example:
// Input: board = ["O  ","   ","   "]
// Output: false
// Explanation: The first player always plays "X".
//
// Constraints:
// board.length == 3
// 	board[i].length == 3
// 	board[i][j] is either 'X', 'O', or ' '.
//

class Solution {
public:
    bool validTicTacToe(vector<string>& board) {
        int xCount = 0, oCount = 0;
        for (const auto& row : board) {
            for (const auto& cell : row) {
                if (cell == 'X') xCount++;
                else if (cell == 'O') oCount++;
            }
        }

        if (oCount > xCount || xCount > oCount + 1) return false;

        auto isWinner = [&](char player) {
            for (int i = 0; i < 3; ++i) {
                if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
                if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
            }
            if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
            if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
            return false;
        };

        bool xWins = isWinner('X');
        bool oWins = isWinner('O');

        if (xWins && oWins) return false;
        if (xWins && xCount != oCount + 1) return false;
        if (oWins && xCount != oCount) return false;

        return true;            
    }
};
