// Source: https://leetcode.com/problems/count-square-submatrices-with-all-ones/   |   Difficulty: Medium
//
// Problem Description:
// Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.
//
// Example:
// Input: matrix =
// [
//   [0,1,1,1],
//   [1,1,1,1],
//   [0,1,1,1]
// ]
// Output: 15
// Explanation: 
// There are 10 squares of side 1.
// There are 4 squares of side 2.
// There is  1 square of side 3.
// Total number of squares = 10 + 4 + 1 = 15.
//
// Constraints:
// 1 <= arr.length <= 300
// 	1 <= arr[0].length <= 300
// 	0 <= arr[i][j] <= 1
//

/**
 * @param {number[][]} matrix
 * @return {number}
 */
var countSquares = function(matrix) {
    const rows = matrix.length;
    const cols = matrix[0].length;
    let totalSquares = 0;
    const dp = Array.from({ length: rows }, () => Array(cols).fill(0));
    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            if (matrix[r][c] === 1) {
                if (r === 0 || c === 0) {
                    dp[r][c] = 1;
                } else {
                    dp[r][c] = Math.min(dp[r - 1][c], dp[r][c - 1], dp[r - 1][c - 1]) + 1;
                }
                totalSquares += dp[r][c];
            }
        }
    }
    return totalSquares;
        
};
