// Source: https://leetcode.com/problems/minimum-falling-path-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.
//
// A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).
//
// Example:
// Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
// Output: 13
// Explanation: There are two falling paths with a minimum sum as shown.
//
// Constraints:
// n == matrix.length == matrix[i].length
// 	1 <= n <= 100
// 	-100 <= matrix[i][j] <= 100
//

/**
 * @param {number[][]} matrix
 * @return {number}
 */
var minFallingPathSum = function(matrix) {
    const n = matrix.length;
    const dp = Array.from({ length: n }, () => Array(n).fill(0));
    // Initialize the first row of dp with the first row of matrix
    for (let j = 0; j < n; j++) {
        dp[0][j] = matrix[0][j];
    }
    // Fill the dp table
    for (let i = 1; i < n; i++) {
        for (let j = 0; j < n; j++) {
            let minAbove = dp[i - 1][j];    
            
            if (j > 0) {
                minAbove = Math.min(minAbove, dp[i - 1][j - 1]);
            }
            if (j < n - 1) {
                minAbove = Math.min(minAbove, dp[i - 1][j + 1]);
            }
            dp[i][j] = matrix[i][j] + minAbove;
        }
    }
    // Find the minimum value in the last row of dp
    let minPathSum = Infinity;
    for (let j = 0; j < n; j++) {
        minPathSum = Math.min(minPathSum, dp[n - 1][j]);
    }
    return minPathSum;
    
};
