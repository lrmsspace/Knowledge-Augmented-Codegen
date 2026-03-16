// Source: https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/   |   Difficulty: Hard
//
// Problem Description:
// You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colors: Red, Yellow, or Green while making sure that no two adjacent cells have the same color (i.e., no two cells that share vertical or horizontal sides have the same color).
//
// Given n the number of rows of the grid, return the number of ways you can paint this grid. As the answer may grow large, the answer must be computed modulo 109 + 7.
//
// Example:
// Input: n = 1
// Output: 12
// Explanation: There are 12 possible way to paint the grid as shown.
//
// Constraints:
// n == grid.length
// 	1 <= n <= 5000
//

/**
 * @param {number} n
 * @return {number}
 */
var numOfWays = function(n) {
    const MOD = 1e9 + 7;
    const dp = Array.from({ length: n }, () => new Array(6).fill(0));
    for (let i = 0; i < 6; i++) {
        dp[0][i] = 1;
    }
    for (let i = 1; i < n; i++) {
        dp[i][0] = (dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][3] + dp[i - 1][4]) % MOD;
        dp[i][1] = (dp[i - 1][0] + dp[i - 1][2] + dp[i - 1][3] + dp[i - 1][5]) % MOD;
        dp[i][2] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][4] + dp[i - 1][5]) % MOD;
        dp[i][3] = (dp[i - 1][0] + dp[i - 1][2] + dp[i - 1][3] + dp[i - 1][5]) % MOD;
        dp[i][4] = (dp[i - 1][0
] + dp[i - 1][1] + dp[i - 1][4] + dp[i - 1][5]) % MOD;
        dp[i][5] = (dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][3] + dp[i - 1][4]) % MOD;
    }
    let totalWays = 0;
    for (let i = 0; i < 6; i++) {
        totalWays = (totalWays + dp[n - 1][i]) % MOD;
    }
    return totalWays;   
};
