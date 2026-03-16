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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numRookCaptures(char** board, int boardSize, int* boardColSize) {
    int rookRow = -1, rookCol = -1;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            if (board[i][j] == 'R') {
                rookRow = i;
                rookCol = j;
                break;
            }
        }
        if (rookRow != -1) break;
    }

    int captures = 0;

    // Check upwards
    for (int i = rookRow - 1; i >= 0; i--) {
        if (board[i][rookCol] == 'B') break; // Blocked by a bishop
        if (board[i][rookCol] == 'p') {
            captures++;
            break; // Captured a pawn, stop checking in this direction
        }
    }

    // Check downwards
    for (int i = rookRow + 1; i < boardSize; i++) {
        if (board[i][rookCol] == 'B') break; // Blocked by a bishop
        if (board[i][rookCol] == 'p') {
            captures++;
            break; // Captured a pawn, stop checking in this direction
        }
    }

    // Check leftwards
    for (int j = rookCol - 1; j >= 0; j--) {
        if (board[rookRow][j] == 'B') break; // Blocked by a bishop
        if (board[rookRow][j] == 'p') {
            captures++;
            break; // Captured a pawn, stop checking in this direction
        }
    }

    // Check rightwards
    for (int j = rookCol + 1; j < boardColSize[0]; j++) {
        if (board[rookRow][j] == 'B') break; // Blocked by a bishop
        if (board[rookRow][j] == 'p') {
            captures++;
            break; // Captured a pawn, stop checking in this direction
        }
    }

    return captures;        
}
