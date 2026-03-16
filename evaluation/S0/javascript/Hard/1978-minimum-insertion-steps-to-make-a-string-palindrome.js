// Source: https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s. In one step you can insert any character at any index of the string.
//
// Return the minimum number of steps to make s palindrome.
//
// A Palindrome String is one that reads the same backward as well as forward.
//
// Example:
// Input: s = "zzazz"
// Output: 0
// Explanation: The string "zzazz" is already palindrome we do not need any insertions.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var minInsertions = function(s) {
    const n = s.length;
    const dp = Array.from({ length: n }, () => new Array(n).fill(0));
    for (let length = 2; length <= n; length++) {
        for (let i = 0; i <= n - length; i++) {
            const j = i + length - 1;
            if (s[i] === s[j]) {
                dp[i][j] = dp[i + 1][j - 1];
            } else {
                dp[i][j] = Math.min(dp[i + 1][j], dp[i][j - 1]) + 1;
            }
        }
    }
    return dp[0][n - 1];
};
