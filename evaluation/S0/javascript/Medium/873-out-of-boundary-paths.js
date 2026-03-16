// Source: https://leetcode.com/problems/out-of-boundary-paths/   |   Difficulty: Medium
//
// Problem Description:
// There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.
//
// Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
// Output: 6
//
// Constraints:
// 1 <= m, n <= 50
// 	0 <= maxMove <= 50
// 	0 <= startRow < m
// 	0 <= startColumn < n
//

/**
 * @param {number} m
 * @param {number} n
 * @param {number} maxMove
 * @param {number} startRow
 * @param {number} startColumn
 * @return {number}
 */
var findPaths = function(m, n, maxMove, startRow, startColumn) {
    const MOD = 1e9 + 7;
    const dp = Array.from({ length: m }, () => Array(n).fill(0));
    dp[startRow][startColumn] = 1;
    let result = 0;
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];

    for (let move = 1; move <= maxMove; move++) {   

        const temp = Array.from({ length: m }, () => Array(n).fill(0));
        for (let i = 0; i < m; i++) {
            for (let j = 0; j < n; j++) {
                for (const [dx, dy] of directions) {
                    const x = i + dx;
                    const y = j + dy;
                    if (x < 0 || x >= m || y < 0 || y >= n) {
                        result = (result + dp[i][j]) % MOD;
                    } else {
                        temp[x][y] = (temp[x][y] + dp[i][j]) % MOD;
                    }
                }
            }
        }
        for (let i = 0; i < m; i++) {
            for (let j = 0; j < n; j++) {
                dp[i][j] = temp[i][j];
            }
        }
    }
    return result;  
};
