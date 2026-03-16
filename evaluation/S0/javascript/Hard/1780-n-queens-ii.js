// Source: https://leetcode.com/problems/n-queens-ii/   |   Difficulty: Hard
//
// Problem Description:
// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
//
// Given an integer n, return the number of distinct solutions to the n-queens puzzle.
//
// Example:
// Input: n = 4
// Output: 2
// Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
//
// Constraints:
// 1 <= n <= 9
//

/**
 * @param {number} n
 * @return {number}
 */
var totalNQueens = function(n) {
    let count = 0;
    const cols = new Set();
    const diag1 = new Set(); // r - c
    const diag2 = new Set(); // r + c
    const backtrack = (row) => {
        if (row === n) {
            count++;
            return;
        }
        for (let col = 0; col < n; col++) {
            if (cols.has(col) || diag1.has(row - col) || diag2.has(row + col)) {
                continue;
            }
            cols.add(col);
            diag1.add(row - col);
            diag2.add(row + col);
            backtrack(row + 1);
            cols.delete(col);
            diag1.delete(row - col);
            diag2.delete(row + col);
        }
    };
    backtrack(0);
    return count;
                
};
