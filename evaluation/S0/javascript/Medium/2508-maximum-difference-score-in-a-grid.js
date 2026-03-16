// Source: https://leetcode.com/problems/maximum-difference-score-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix grid consisting of positive integers. You can move from a cell in the matrix to any other cell that is either to the bottom or to the right (not necessarily adjacent). The score of a move from a cell with the value c1 to a cell with the value c2 is c2 - c1.
//
// You can start at any cell, and you have to make at least one move.
//
// Return the maximum total score you can achieve.
//
// Example:
// Input: grid = [[9,5,7,3],[8,9,6,1],[6,7,14,3],[2,5,3,1]]
//
// Output: 9
//
// Explanation: We start at the cell (0, 1), and we perform the following moves:
// - Move from the cell (0, 1) to (2, 1) with a score of 7 - 5 = 2.
// - Move from the cell (2, 1) to (2, 2) with a score of 14 - 7 = 7.
// The total score is 2 + 7 = 9.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 1000
// 	4 <= m * n <= 105
// 	1 <= grid[i][j] <= 105
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var maxScore = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const dp = Array.from({ length: m }, () => Array(n).fill(0));
    for (let i = m - 1; i >= 0; i--) {
        for (let j = n - 1; j >= 0; j--) {
            if (i === m - 1 && j === n - 1) {
                dp[i][j] = 0;
            }
            else if (i === m - 1) {
                dp[i][j] = grid[i][j + 1] - grid[i][j] + dp[i][j + 1];
            }
            else if (j === n - 1) {
                dp[i][j] = grid[i + 1][j] - grid[i][j] + dp[i + 1][j];
            }
            else {
                dp[i][j] = Math.max(grid[i + 1][j] - grid[i][j] + dp[i + 1][j], grid[i][j + 1] - grid[i][j] + dp[i][j + 1]);
            }
        }
    }
    let maxScore = 0;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            maxScore = Math.max(maxScore, dp[i][j]);
        }
    }
    return maxScore;    
};
