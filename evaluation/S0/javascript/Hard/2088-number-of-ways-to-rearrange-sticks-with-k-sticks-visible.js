// Source: https://leetcode.com/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/   |   Difficulty: Hard
//
// Problem Description:
// There are n uniquely-sized sticks whose lengths are integers from 1 to n. You want to arrange the sticks such that exactly k sticks are visible from the left. A stick is visible from the left if there are no longer sticks to the left of it.
//
//
// 	For example, if the sticks are arranged [1,3,2,5,4], then the sticks with lengths 1, 3, and 5 are visible from the left.
//
//
// Given n and k, return the number of such arrangements. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, k = 2
// Output: 3
// Explanation: [1,3,2], [2,3,1], and [2,1,3] are the only arrangements such that exactly 2 sticks are visible.
// The visible sticks are underlined.
//
// Constraints:
// 1 <= n <= 1000
// 	1 <= k <= n
//

/**
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
var rearrangeSticks = function(n, k) {
    const MOD = 1e9 + 7;
    const dp = Array.from({ length: n + 1 }, () => new Array(k + 1).fill(0));
    dp[0][0] = 1;
    for (let i = 1; i <= n; i++) {
        for (let j = 1; j <= Math.min(i, k); j++) {
            dp[i][j] = (dp[i - 1][j - 1] + (i - 1) * dp[i - 1][j]) % MOD;
        }
    }
    return dp[n][k];
};
