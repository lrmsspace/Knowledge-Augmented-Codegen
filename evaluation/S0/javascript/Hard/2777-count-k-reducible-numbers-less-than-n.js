// Source: https://leetcode.com/problems/count-k-reducible-numbers-less-than-n/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s representing a number n in its binary form.
//
// You are also given an integer k.
//
// An integer x is called k-reducible if performing the following operation at most k times reduces it to 1:
//
//
// 	Replace x with the count of set bits in its binary representation.
//
//
// For example, the binary representation of 6 is "110". Applying the operation once reduces it to 2 (since "110" has two set bits). Applying the operation again to 2 (binary "10") reduces it to 1 (since "10" has one set bit).
//
// Return an integer denoting the number of positive integers less than n that are k-reducible.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "111", k = 1
//
// Output: 3
//
// Explanation: 
//
// n = 7. The 1-reducible integers less than 7 are 1, 2, and 4.
//
// Constraints:
// 1 <= s.length <= 800
// 	s has no leading zeros.
// 	s consists only of the characters '0' and '1'.
// 	1 <= k <= 5
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var countKReducibleNumbers = function(s, k) {
    const MOD = 1e9 + 7;
    const n = s.length;
    const maxBits = 800;
    const dp = Array.from({ length: n + 1 }, () => Array(maxBits + 1).fill(0));
    dp[0][0] = 1;
    for (let i = 0; i < n; i++) {
        for (let j = 0; j <= maxBits; j++) {
            const bit = parseInt(s[i]);
            dp[i + 1][j + bit] = (dp[i + 1][j + bit] + dp[i][j]) % MOD;
            if (bit === 0) {
                dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % MOD;
            }
        }
    }
    const reducibleCount = Array(maxBits + 1).fill(0);
    reducibleCount[1] = 0;
    for (let i = 2; i <= maxBits; i++) {
        let count = 0;
        let x = i;
        while (x !== 1) {
            x = x.toString(2).split('0').join('').length;
            count++;
        }
        reducibleCount[i] = count;
    }
    let result = 0;
    for (let bits = 1; bits <= maxBits; bits++) {
        if (reducibleCount[bits] === k) {
            result = (result + dp[n][bits]) % MOD;
        }
    }
    if (k === 0) {
        result = (result - 1 + MOD) % MOD;
    }
    return result;  
};
