// Source: https://leetcode.com/problems/strange-printer/   |   Difficulty: Hard
//
// Problem Description:
// There is a strange printer with the following two special properties:
//
//
// 	The printer can only print a sequence of the same character each time.
// 	At each turn, the printer can print new characters starting from and ending at any place and will cover the original existing characters.
//
//
// Given a string s, return the minimum number of turns the printer needed to print it.
//
// Example:
// Input: s = "aaabbb"
// Output: 2
// Explanation: Print "aaa" first and then print "bbb".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var strangePrinter = function(s) {
    


    const n = s.length;
    const dp = Array.from({ length: n }, () => Array(n).fill(0));
    for (let i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    for (let len = 2; len <= n; len++) {
        for (let i = 0; i <= n - len; i++) {
            const j = i + len - 1;
            dp[i][j] = dp[i][j - 1] + 1;
            for (let k = i; k < j; k++) {
                if (s[k] === s[j]) {
                    dp[i][j] = Math.min(dp[i][j], dp[i][k] + dp[k + 1][j - 1]);
                }
            }
        }
    }
    return dp[0][n - 1];
    
};
