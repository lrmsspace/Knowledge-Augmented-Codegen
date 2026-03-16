// Source: https://leetcode.com/problems/restore-the-array/   |   Difficulty: Hard
//
// Problem Description:
// A program was supposed to print an array of integers. The program forgot to print whitespaces and the array is printed as a string of digits s and all we know is that all integers in the array were in the range [1, k] and there are no leading zeros in the array.
//
// Given the string s and the integer k, return the number of the possible arrays that can be printed as s using the mentioned program. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "1000", k = 10000
// Output: 1
// Explanation: The only possible array is [1000]
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only digits and does not contain leading zeros.
// 	1 <= k <= 109
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var numberOfArrays = function(s, k) {
    const MOD = 1e9 + 7;
    const n = s.length;
    const dp = new Array(n + 1).fill(0);
    dp[0] = 1;
    for (let i = 1; i <= n; i++) {
        for (let j = i - 1; j >= 0; j--) {
            if (s[j] === '0') continue;
            const num = Number(s.substring(j, i));
            if (num > k) break;
            dp[i] = (dp[i] + dp[j]) % MOD;
        }
    }
    return dp[n];
};
