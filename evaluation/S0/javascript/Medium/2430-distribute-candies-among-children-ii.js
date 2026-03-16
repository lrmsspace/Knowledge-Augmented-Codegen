// Source: https://leetcode.com/problems/distribute-candies-among-children-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers n and limit.
//
// Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.
//
// Example:
// Input: n = 5, limit = 2
// Output: 3
// Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).
//
// Constraints:
// 1 <= n <= 106
// 	1 <= limit <= 106
//

/**
 * @param {number} n
 * @param {number} limit
 * @return {number}
 */
var distributeCandies = function(n, limit) {
    const MOD = 1e9 + 7;
    const dp = Array.from({ length: 4 }, () => Array(n + 1).fill(0));
    dp[0][0] = 1;
    for (let i = 1; i <= 3; i++) {
        for (let j = 0; j <= n; j++) {
            for (let k = 0; k <= Math.min(limit, j); k++) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % MOD;
            }
        }
    }
    return dp[3][n];
};