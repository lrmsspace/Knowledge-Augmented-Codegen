// Source: https://leetcode.com/problems/delete-operation-for-two-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings word1 and word2, return the minimum number of steps required to make word1 and word2 the same.
//
// In one step, you can delete exactly one character in either string.
//
// Example:
// Input: word1 = "sea", word2 = "eat"
// Output: 2
// Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
//
// Constraints:
// 1 <= word1.length, word2.length <= 500
// 	word1 and word2 consist of only lowercase English letters.
//

/**
 * @param {string} word1
 * @param {string} word2
 * @return {number}
 */
var minDistance = function(word1, word2) {
    const m = word1.length;
    const n = word2.length;
    const dp = Array(m + 1).fill(null).map(() => Array(n + 1).fill(0));

    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            if (word1[i - 1] === word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return m + n - 2 * dp[m][n];
};