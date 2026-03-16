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

/**
 * @param {character[][]} board
 * @return {number}
 */
var numRookCaptures = function(board) {
    let rookRow = -1;
    let rookCol = -1;
    for (let i = 0; i < 8; i++) {
        for (let j = 0; j < 8; j++) {
            if (board[i][j] === 'R') {
                rookRow = i;
                rookCol = j;
                break;
            }
        }
        if (rookRow !== -1) {
            break;
        }
    }

    let captures = 0;

    // Check upwards
    for (let i = rookRow - 1; i >= 0; i--) {
        if (board[i][rookCol] === 'B') break;
        if (board[i][rookCol] === 'p') {
            captures++;
            break;
        }
    }

    // Check downwards
    for (let i = rookRow + 1; i < 8; i++) {
        if (board[i][rookCol] === 'B') break;
        if (board[i][rookCol] === 'p') {
            captures++;
            break;
        }
    }

    // Check left
    for (let j = rookCol - 1; j >= 0; j--) {
        if (board[rookRow][j] === 'B') break;
        if (board[rookRow][j] === 'p') {
            captures++;
            break;
        }
    }

    // Check right
    for (let j = rookCol + 1; j < 8; j++) {
        if (board[rookRow][j] === 'B') break;
        if (board[rookRow][j] === 'p') {
            captures++;
            break;
        }
    }

    return captures;
};