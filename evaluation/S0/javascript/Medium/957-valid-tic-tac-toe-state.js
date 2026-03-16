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

/**
 * @param {string[]} board
 * @return {boolean}
 */
var validTicTacToe = function(board) {
    const count = { 'X': 0, 'O': 0 };
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            const cell = board[i][j];
            if (cell === 'X' || cell === 'O') {
                count[cell]++;
            }
        }
    }
    if (count['O'] > count['X'] || count['X'] - count['O'] > 1) {
        return false;
    }

    const win = (player) => {
        for (let i = 0; i < 3; i++) {
            if (board[i][0] === player && board[i][1] === player && board[i][2] === player) {
                return true;
            }
            if (board[0][i] === player && board[1][i] === player && board[2][i] === player) {
                return true;
            }
        }
        if (board[0][0] === player && board[1][1] === player && board[2][2] === player) {
            return true;
        }
        if (board[0][2] === player && board[1][1] === player && board[2][0] === player) {
            return true;
        }
        return false;
    };

    if (win('X') && count['X'] !== count['O'] + 1) {
        return false;
    }
    if (win('O') && count['X'] !== count['O']) {
        return false;
    }

    return true;
};