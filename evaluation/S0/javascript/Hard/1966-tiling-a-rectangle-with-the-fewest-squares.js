// Source: https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/   |   Difficulty: Hard
//
// Problem Description:
// Given a rectangle of size n x m, return the minimum number of integer-sided squares that tile the rectangle.
//
// Example:
// Input: n = 2, m = 3
// Output: 3
// Explanation: 3 squares are necessary to cover the rectangle.
// 2 (squares of 1x1)
// 1 (square of 2x2)
//
// Constraints:
// 1 <= n, m <= 13
//

/**
 * @param {number} n
 * @param {number} m
 * @return {number}
 */
var tilingRectangle = function(n, m) {
    const dp = Array.from({ length: n + 1 }, () => new Array(m + 1).fill(Infinity));
    for (let i = 0; i <= n; i++) {
        for (let j = 0; j <= m; j++) {
            if (i === j) {
                dp[i][j] = 1;
            }
        }
    }
    for (let i = 1; i <= n; i++) {
        for (let j = 1; j <= m; j++) {
            if (dp[i][j] === 1) continue;
            for (let k = 1; k < Math.min(i, j); k++) {
                dp[i][j] = Math.min(dp[i][j], dp[k][j] + dp[i - k][j]);
                dp[i][j] = Math.min(dp[i][j], dp[i][k] + dp[i][j - k]);
            }
        }
    }
    return dp[n][m];
};
