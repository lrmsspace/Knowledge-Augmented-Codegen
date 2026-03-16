// Source: https://leetcode.com/problems/find-the-original-typed-string-ii/   |   Difficulty: Hard
//
// Problem Description:
// Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.
//
// You are given a string word, which represents the final output displayed on Alice's screen. You are also given a positive integer k.
//
// Return the total number of possible original strings that Alice might have intended to type, if she was trying to type a string of size at least k.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: word = "aabbccdd", k = 7
//
// Output: 5
//
// Explanation:
//
// The possible strings are: "aabbccdd", "aabbccd", "aabbcdd", "aabccdd", and "abbccdd".
//
// Constraints:
// 1 <= word.length <= 5 * 105
//  word consists only of lowercase English letters.
//  1 <= k <= 2000
//

/**
 * @param {string} word
 * @param {number} k
 * @return {number}
 */
var possibleStringCount = function(word, k) {
    const MOD = 1e9 + 7;
    const n = word.length;
    const dp = Array(n + 1).fill(0);
    dp[0] = 1;
    let count = 1;
    for (let i = 1; i < n; i++) {
        if (word[i] === word[i - 1]) {
            count++;
        } else {
            count = 1;
        }
        for (let j = 1; j <= Math.min(count, k); j++) {
            dp[i + 1] = (dp[i + 1] + dp[i + 1 - j]) % MOD;
        }
    }
    let result = 0;
    for (let i = k; i <= n; i++) {
        result = (result + dp[i]) % MOD;
    }
    return result;  
};
