// Source: https://leetcode.com/problems/painting-a-grid-with-three-different-colors/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers m and n. Consider an m x n grid where each cell is initially white. You can paint each cell red, green, or blue. All cells must be painted.
//
// Return the number of ways to color the grid with no two adjacent cells having the same color. Since the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: m = 1, n = 1
// Output: 3
// Explanation: The three possible colorings are shown in the image above.
//
// Constraints:
// 1 <= m <= 5
// 	1 <= n <= 1000
//

/**
 * @param {number} m
 * @param {number} n
 * @return {number}
 */
var colorTheGrid = function(m, n) {
    const MOD = 1e9 + 7;
    const colors = [0, 1, 2];
    const validPatterns = [];
    const generatePatterns = (pattern) => {
        if (pattern.length === m) {
            validPatterns.push(pattern);
            return;
        }
        for (const color of colors) {
            if (pattern.length === 0 || pattern[pattern.length - 1] !== color) {
                generatePatterns([...pattern, color]);
            }
        }
    }
    generatePatterns([]);
    const patternCount = validPatterns.length;
    const dp = new Array(n).fill(0).map(() => new Array(patternCount).fill(0));
    for (let i = 0; i < patternCount; i++) {
        dp[0][i] = 1;
    }
    for (let col = 1; col < n; col++) {
        for (let i = 0; i < patternCount; i++) {
            for (let j = 0; j < patternCount; j++) {
                if (isValidTransition(validPatterns[i], validPatterns[j])) {
                    dp[col][j] = (dp[col][j] + dp[col - 1][i]) % MOD;
                }
            }
        }
    }
    return dp[n - 1].reduce((acc, val) => (acc + val) % MOD, 0);
};
