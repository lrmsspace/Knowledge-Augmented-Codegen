// Source: https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given three integers n, m, k. A good array arr of size n is defined as follows:
//
//
// 	Each element in arr is in the inclusive range [1, m].
// 	Exactly k indices i (where 1 <= i < n) satisfy the condition arr[i - 1] == arr[i].
//
//
// Return the number of good arrays that can be formed.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, m = 2, k = 1
//
// Output: 4
//
// Explanation:
//
//
// 	There are 4 good arrays. They are [1, 1, 2], [1, 2, 2], [2, 1, 1] and [2, 2, 1].
// 	Hence, the answer is 4.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= m <= 105
// 	0 <= k <= n - 1
//

/**
 * @param {number} n
 * @param {number} m
 * @param {number} k
 * @return {number}
 */
var countGoodArrays = function(n, m, k) {
    const MOD = 1e9 + 7;
    const dp = Array.from({ length: n }, () => Array(k + 1).fill(0));
    dp[0][0] = m;
    for (let i = 1; i < n; i++) {
        for (let j = 0; j <= k; j++) {
            dp[i][j] = (dp[i - 1][j] * (m - 1)) % MOD;
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
            }
        }
    }
    return dp[n - 1][k];
};
