// Source: https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed m x n integer matrix grid and an integer k. You are currently at position (0, 0) and you want to reach position (m - 1, n - 1) moving only down or right.
//
// Return the number of paths where the sum of the elements on the path is divisible by k. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
// Output: 2
// Explanation: There are two paths where the sum of the elements on the path is divisible by k.
// The first path highlighted in red has a sum of 5 + 2 + 4 + 5 + 2 = 18 which is divisible by 3.
// The second path highlighted in blue has a sum of 5 + 3 + 0 + 5 + 2 = 15 which is divisible by 3.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 5 * 104
// 	1 <= m * n <= 5 * 104
// 	0 <= grid[i][j] <= 100
// 	1 <= k <= 50
//

/**
 * @param {number[][]} grid
 * @param {number} k
 * @return {number}
 */
var numberOfPaths = function(grid, k) {
    const mod = 1e9 + 7;
    const m = grid.length;
    const n = grid[0].length;
    const dp = Array.from({ length: m }, () => new Array(n).fill(0).map(() => new Array(k).fill(0)));
    dp[0][0][grid[0][0] % k] = 1;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            for (let r = 0; r < k; r++) {
                if (dp[i][j][r] > 0) {
                    if (i + 1 < m) {
                        const newR = (r + grid[i + 1][j]) % k;
                        dp[i + 1][j][newR] = (dp[i + 1][j][newR] + dp[i][j][r]) % mod;
                    }
                    if (j + 1 < n) {
                        const newR = (r + grid[i][j + 1]) % k;
                        dp[i][j + 1][newR] = (dp[i][j + 1][newR] + dp[i][j][r]) % mod;
                    }
                }
            }
        }
    }
    return dp[m - 1][n - 1][0]; 
};
