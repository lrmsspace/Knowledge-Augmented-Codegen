// Source: https://leetcode.com/problems/available-captures-for-rook/   |   Difficulty: Easy
//
// Problem Description:
// You are given an 8 x 8 matrix representing a chessboard. There is exactly one white rook represented by 'R', some number of white bishops 'B', and some number of black pawns 'p'. Empty squares are represented by '.'.
//
// A rook can move any number of squares horizontally or vertically (up, down, left, right) until it reaches another piece or the edge of the board. A rook is attacking a pawn if it can move to the pawn's square in one move.
//
// Note: A rook cannot move through other pieces, such as bishops or pawns. This means a rook cannot attack a pawn if there is another piece blocking the path.
//
// Return the number of pawns the white rook is attacking.
//
// Example:
// Input: board = [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","R",".",".",".","p"],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
//
// Output: 3
//
// Explanation:
//
// In this example, the rook is attacking all the pawns.
//
// Constraints:
// board.length == 8
// 	board[i].length == 8
// 	board[i][j] is either 'R', '.', 'B', or 'p'
// 	There is exactly one cell with board[i][j] == 'R'
//

class Solution {
    public int numRookCaptures(char[][] board) {
        int rookRow = -1, rookCol = -1;

        // Locate the rook's position
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] == 'R') {
                    rookRow = i;
                    rookCol = j;
                    break;
                }
            }
            if (rookRow != -1) break;
        }

        int captures = 0;

        // Directions: up, down, left, right
        int[][] directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int[] dir : directions) {
            int x = rookRow;
            int y = rookCol;

            while (true) {
                x += dir[0];
                y += dir[1];

                // Check boundaries
                if (x < 0 || x >= 8 || y < 0 || y >= 8) break;

                // If we encounter a bishop, stop searching in this direction
                if (board[x][y] == 'B') break;

                // If we encounter a pawn, increment captures and stop searching in this direction
                if (board[x][y] == 'p') {
                    captures++;
                    break;
                }
            }
        }

        return captures;            
    }
}
