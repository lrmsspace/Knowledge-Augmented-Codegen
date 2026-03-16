// Source: https://leetcode.com/problems/valid-permutations-for-di-sequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s of length n where s[i] is either:
//
//
// 	'D' means decreasing, or
// 	'I' means increasing.
//
//
// A permutation perm of n + 1 integers of all the integers in the range [0, n] is called a valid permutation if for all valid i:
//
//
// 	If s[i] == 'D', then perm[i] > perm[i + 1], and
// 	If s[i] == 'I', then perm[i] < perm[i + 1].
//
//
// Return the number of valid permutations perm. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: s = "DID"
// Output: 5
// Explanation: The 5 valid permutations of (0, 1, 2, 3) are:
// (1, 0, 3, 2)
// (2, 0, 3, 1)
// (2, 1, 3, 0)
// (3, 0, 2, 1)
// (3, 1, 2, 0)
//
// Constraints:
// n == s.length
// 	1 <= n <= 200
// 	s[i] is either 'I' or 'D'.
//

/**
 * @param {string} s
 * @return {number}
 */
var numPermsDISequence = function(s) {
    const MOD = 1e9 + 7;
    const n = s.length;
    const dp = Array.from({ length: n + 1 }, () => new Array(n + 1).fill(0));
    dp[0][0] = 1;
    for (let i = 1; i <= n; i++) {
        if (s[i - 1] === 'D') {
            for (let j = 0; j < i; j++) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }
        } else {
            for (let j = 0; j < i; j++) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }
        }
    }
    let totalPermutations = 0;
    for (let j = 0; j <= n; j++) {
        totalPermutations = (totalPermutations + dp[n][j]) % MOD;
    }
    return totalPermutations;   
};
