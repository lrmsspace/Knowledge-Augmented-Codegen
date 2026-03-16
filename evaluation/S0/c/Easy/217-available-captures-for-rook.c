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

int numRookCaptures(char** board, int boardSize, int* boardColSize) {
    int rookX = -1, rookY = -1;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            if (board[i][j] == 'R') {
                rookX = i;
                rookY = j;
                break;
            }
        }
        if (rookX != -1) break;
    }

    int captures = 0;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // up, down, left, right

    for (int d = 0; d < 4; d++) {
        int x = rookX;
        int y = rookY;

        while (true) {
            x += directions[d][0];
            y += directions[d][1];

            if (x < 0 || x >= boardSize || y < 0 || y >= boardColSize[0]) {
                break; // Out of bounds
            }

            if (board[x][y] == 'B') {
                break; // Blocked by a bishop
            }

            if (board[x][y] == 'p') {
                captures++;
                break; // Captured a pawn
            }
        }
    }

    return captures;        
}
