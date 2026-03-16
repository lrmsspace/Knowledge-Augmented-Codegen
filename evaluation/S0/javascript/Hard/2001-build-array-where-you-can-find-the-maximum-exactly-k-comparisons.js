// Source: https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/   |   Difficulty: Hard
//
// Problem Description:
// You are given three integers n, m and k. Consider the following algorithm to find the maximum element of an array of positive integers:
//
// You should build the array arr which has the following properties:
//
//
// 	arr has exactly n integers.
// 	1 <= arr[i] <= m where (0 <= i < n).
// 	After applying the mentioned algorithm to arr, the value search_cost is equal to k.
//
//
// Return the number of ways to build the array arr under the mentioned conditions. As the answer may grow large, the answer must be computed modulo 109 + 7.
//
// Example:
// Input: n = 2, m = 3, k = 1
// Output: 6
// Explanation: The possible arrays are [1, 1], [2, 1], [2, 2], [3, 1], [3, 2] [3, 3]
//
// Constraints:
// 1 <= n <= 50
// 	1 <= m <= 100
// 	0 <= k <= n
//

/**
 * @param {number} n
 * @param {number} m
 * @param {number} k
 * @return {number}
 */
var numOfArrays = function(n, m, k) {
    const MOD = 1e9 + 7;
    const dp = Array.from({ length: n + 1 }, () => new Array(k + 1).fill(0));
    dp[0][0] = 1;

    for (let i = 1; i <= n; i++) {
        for (let j = 0; j <= k; j++) {
            dp[i][j] = (dp[i][j] + dp[i - 1][j] * Math.max(0, m - j)) % MOD;
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1] * Math.max(0, j)) % MOD;
            }
        }
    }
    return dp[n][k];    
};
