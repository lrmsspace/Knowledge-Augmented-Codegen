// Source: https://leetcode.com/problems/number-of-distinct-roll-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n. You roll a fair 6-sided dice n times. Determine the total number of distinct sequences of rolls possible such that the following conditions are satisfied:
//
//
// 	The greatest common divisor of any adjacent values in the sequence is equal to 1.
// 	There is at least a gap of 2 rolls between equal valued rolls. More formally, if the value of the ith roll is equal to the value of the jth roll, then abs(i - j) > 2.
//
//
// Return the total number of distinct sequences possible. Since the answer may be very large, return it modulo 109 + 7.
//
// Two sequences are considered distinct if at least one element is different.
//
// Example:
// Input: n = 4
// Output: 184
// Explanation: Some of the possible sequences are (1, 2, 3, 4), (6, 1, 2, 3), (1, 2, 3, 1), etc.
// Some invalid sequences are (1, 2, 1, 3), (1, 2, 3, 6).
// (1, 2, 1, 3) is invalid since the first and third roll have an equal value and abs(1 - 3) = 2 (i and j are 1-indexed).
// (1, 2, 3, 6) is invalid since the greatest common divisor of 3 and 6 = 3.
// There are a total of 184 distinct sequences possible, so we return 184.
//
// Constraints:
// 1 <= n <= 104
//

/**
 * @param {number} n
 * @return {number}
 */
var distinctSequences = function(n) {
    const mod = 1e9 + 7;
    const gcd = (a, b) => b === 0 ? a : gcd(b, a % b);
    const dp = Array.from({ length: n }, () => new Array(7).fill(0));
    for (let i = 1; i <= 6; i++) {
        dp[0][i] = 1;
    }
    for (let i = 1; i < n; i++) {
        for (let j = 1; j <= 6; j++) {
            for (let k = 1; k <= 6; k++) {
                if (gcd(j, k) === 1) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k]) % mod;
                }
            }
        }
    }
    let result = 0;
    for (let i = 1; i <= 6; i++) {
        result = (result + dp[n - 1][i]) % mod;
    }
    return result;
};
