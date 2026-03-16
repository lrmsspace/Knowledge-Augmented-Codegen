// Source: https://leetcode.com/problems/n-queens/   |   Difficulty: Hard
//
// Problem Description:
// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
//
// Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
//
// Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.
//
// Example:
// Input: n = 4
// Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
// Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
//
// Constraints:
// 1 <= n <= 9
//

/**
 * @param {number} n
 * @return {string[][]}
 */
var solveNQueens = function(n) {
    const results = [];
    const board = Array.from({ length: n }, () => '.'.repeat(n).split(''));
    const cols = new Set();
    const diag1 = new Set(); // r - c
    const diag2 = new Set(); // r + c
    const backtrack = (row) => {
        if (row === n) {
            results.push(board.map(r => r.join('')));
            return;
        }
        for (let col = 0; col < n; col++) {
            if (cols.has(col) || diag1.has(row - col) || diag2.has(row + col)) {
                continue;
            }
            board[row][col] = 'Q';
            cols.add(col);
            diag1.add(row - col);
            diag2.add(row + col);
            backtrack(row + 1);
            board[row][col] = '.';
            cols.delete(col);
            diag1.delete(row - col);
            diag2.delete(row + col);
        }
    };
    backtrack(0);
    return results;
                
};
