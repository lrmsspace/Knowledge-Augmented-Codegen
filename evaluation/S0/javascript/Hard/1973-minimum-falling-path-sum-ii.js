// Source: https://leetcode.com/problems/minimum-falling-path-sum-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given an n x n integer matrix grid, return the minimum sum of a falling path with non-zero shifts.
//
// A falling path with non-zero shifts is a choice of exactly one element from each row of grid such that no two elements chosen in adjacent rows are in the same column.
//
// Example:
// Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
// Output: 13
// Explanation: 
// The possible falling paths are:
// [1,5,9], [1,5,7], [1,6,7], [1,6,8],
// [2,4,8], [2,4,9], [2,6,7], [2,6,8],
// [3,4,8], [3,4,9], [3,5,7], [3,5,9]
// The falling path with the smallest sum is [1,5,7], so the answer is 13.
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 200
// 	-99 <= grid[i][j] <= 99
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var minFallingPathSum = function(grid) {
    const n = grid.length;
    const dp = Array.from({ length: n }, () => new Array(n).fill(0));
    for (let j = 0; j < n; j++) {
        dp[0][j] = grid[0][j];
    }
    for (let i = 1; i < n; i++) {
        for (let j = 0; j < n; j++) {
            dp[i][j] = Infinity;
            for (let k = 0; k < n; k++) {
                if (k !== j) {
                    dp[i][j] = Math.min(dp[i][j], dp[i - 1][k] + grid[i][j]);
                }
            }
        }
    }
    return Math.min(...dp[n - 1]);  
};
