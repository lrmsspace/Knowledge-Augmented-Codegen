// Source: https://leetcode.com/problems/maximum-value-sum-by-placing-three-rooks-i/   |   Difficulty: Hard
//
// Problem Description:
// You are given a m x n 2D array board representing a chessboard, where board[i][j] represents the value of the cell (i, j).
//
// Rooks in the same row or column attack each other. You need to place three rooks on the chessboard such that the rooks do not attack each other.
//
// Return the maximum sum of the cell values on which the rooks are placed.
//
// Example:
// Input: board = [[-3,1,1,1],[-3,1,-3,1],[-3,2,1,1]]
//
// Output: 4
//
// Explanation:
//
//
//
// We can place the rooks in the cells (0, 2), (1, 3), and (2, 1) for a sum of 1 + 1 + 2 = 4.
//
// Constraints:
// 3 <= m == board.length <= 100
// 	3 <= n == board[i].length <= 100
// 	-109 <= board[i][j] <= 109
//

/**
 * @param {number[][]} board
 * @return {number}
 */
var maximumValueSum = function(board) {
    const m = board.length;
    const n = board[0].length;
    let maxSum = -Infinity;
    for (let r1 = 0; r1 < m; r1++) {
        for (let c1 = 0; c1 < n; c1++) {
            for (let r2 = 0; r2 < m; r2++) {
                if (r2 === r1) continue;
                for (let c2 = 0; c2 < n; c2++) {
                    if (c2 === c1) continue;
                    for (let r3 = 0; r3 < m; r3++) {
                        if (r3 === r1 || r3 === r2) continue;
                        for (let c3 = 0; c3 < n; c3++) {
                            if (c3 === c1 || c3 === c2) continue;
                            const currentSum = board[r1][c1] + board[r2][c2] + board[r3][c3];
                            maxSum = Math.max(maxSum, currentSum);
                        }
                    }
                }
            }
        }
    }
    return maxSum;  
};
