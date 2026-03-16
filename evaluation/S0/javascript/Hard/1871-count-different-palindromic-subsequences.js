// Source: https://leetcode.com/problems/count-different-palindromic-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, return the number of different non-empty palindromic subsequences in s. Since the answer may be very large, return it modulo 109 + 7.
//
// A subsequence of a string is obtained by deleting zero or more characters from the string.
//
// A sequence is palindromic if it is equal to the sequence reversed.
//
// Two sequences a1, a2, ... and b1, b2, ... are different if there is some i for which ai != bi.
//
// Example:
// Input: s = "bccb"
// Output: 6
// Explanation: The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
// Note that 'bcb' is counted only once, even though it occurs twice.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either 'a', 'b', 'c', or 'd'.
//

/**
 * @param {string} s
 * @return {number}
 */
var countPalindromicSubsequences = function(s) {
    const MOD = 1e9 + 7;
    const n = s.length;
    const dp = Array.from({ length: n }, () => new Array(n).fill(0));
    for (let i = n - 1; i >= 0; i--) {
        dp[i][i] = 1;
        for (let j = i + 1; j < n; j++) {
            if (s[i] === s[j]) {
                let low = i + 1, high = j - 1;
                while (low <= high && s[low] !== s[i]) low++;
                while (low <= high && s[high] !== s[j]) high--;
                if (low > high) {
                    dp[i][j] = (2 * dp[i + 1][j - 1] + 2) % MOD;
                }   
                else if (low === high) {
                    dp[i][j] = (2 * dp[i + 1][j - 1] + 1) % MOD;
                }
                else {
                    dp[i][j] = (2 * dp[i + 1][j - 1] - dp[low + 1][high - 1] + MOD) % MOD;
                }
            } else {
                dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + MOD) % MOD;
            }
        }
    }
    return dp[0][n - 1];
           
};
