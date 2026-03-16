// Source: https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given 3 positive integers zero, one, and limit.
//
// A binary array arr is called stable if:
//
//
// 	The number of occurrences of 0 in arr is exactly zero.
// 	The number of occurrences of 1 in arr is exactly one.
// 	Each subarray of arr with a size greater than limit must contain both 0 and 1.
//
//
// Return the total number of stable binary arrays.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: zero = 1, one = 1, limit = 2
//
// Output: 2
//
// Explanation:
//
// The two possible stable binary arrays are [1,0] and [0,1].
//
// Constraints:
// 1 <= zero, one, limit <= 1000
//

/**
 * @param {number} zero
 * @param {number} one
 * @param {number} limit
 * @return {number}
 */
var numberOfStableArrays = function(zero, one, limit) {
    const mod = 1e9 + 7;
    const n = zero + one;
    const dp = new Array(n + 1).fill(0).map(() => new Array(one + 1).fill(0));
    dp[0][0] = 1;
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j <= Math.min(i, one); j++) {
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod;
            }
            if (i - j > 0) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
            }
        }
    }
    let result = 0;
    for (let i = 1; i <= n; i++) {
        if (i > limit) {
            result = (result + dp[i][one]) % mod;
        }
    }
    return result;
};
