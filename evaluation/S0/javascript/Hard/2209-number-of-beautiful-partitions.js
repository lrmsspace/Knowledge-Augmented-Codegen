// Source: https://leetcode.com/problems/number-of-beautiful-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s that consists of the digits '1' to '9' and two integers k and minLength.
//
// A partition of s is called beautiful if:
//
//
// 	s is partitioned into k non-intersecting substrings.
// 	Each substring has a length of at least minLength.
// 	Each substring starts with a prime digit and ends with a non-prime digit. Prime digits are '2', '3', '5', and '7', and the rest of the digits are non-prime.
//
//
// Return the number of beautiful partitions of s. Since the answer may be very large, return it modulo 109 + 7.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "23542185131", k = 3, minLength = 2
// Output: 3
// Explanation: There exists three ways to create a beautiful partition:
// "2354 | 218 | 5131"
// "2354 | 21851 | 31"
// "2354218 | 51 | 31"
//
// Constraints:
// 1 <= k, minLength <= s.length <= 1000
// 	s consists of the digits '1' to '9'.
//

/**
 * @param {string} s
 * @param {number} k
 * @param {number} minLength
 * @return {number}
 */
var beautifulPartitions = function(s, k, minLength) {
    const mod = 1e9 + 7;
    const n = s.length;
    const isPrime = (digit) => ['2', '3', '5', '7'].includes(digit);
    if (!isPrime(s[0]) || isPrime(s[n - 1])) {
        return 0;
    }
    const dp = Array.from({ length: n }, () => new Array(k + 1).fill(0));
    dp[0][1] = 1;
    for (let i = 1; i < n; i++) {
        for (let j = 1; j <= k; j++) {
            if (isPrime(s[i]) && i >= minLength) {
                dp[i][j] = (dp[i][j] + dp[i - minLength][j - 1]) % mod;
            }
            if (!isPrime(s[i])) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
            }
        }
    }
    return dp[n - 1][k];
};
