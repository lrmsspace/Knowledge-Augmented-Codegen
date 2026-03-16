// Source: https://leetcode.com/problems/edit-distance/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
//
// You have the following three operations permitted on a word:
//
//
// 	Insert a character
// 	Delete a character
// 	Replace a character
//
// Example:
// Input: word1 = "horse", word2 = "ros"
// Output: 3
// Explanation: 
// horse -> rorse (replace 'h' with 'r')
// rorse -> rose (remove 'r')
// rose -> ros (remove 'e')
//
// Constraints:
// 0 <= word1.length, word2.length <= 500
// 	word1 and word2 consist of lowercase English letters.
//

/**
 * @param {string} word1
 * @param {string} word2
 * @return {number}
 */
var minDistance = function(word1, word2) {
    const m = word1.length;
    const n = word2.length;
    const dp = Array.from({ length: m + 1 }, () => Array(n + 1).fill(0));

    for (let i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (let j = 0; j <= n; j++) {
        dp[0][j] = j;
    }

    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            if (word1[i - 1] === word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = Math.min(
                    dp[i - 1][j] + 1,    // Delete
                    dp[i][j - 1] + 1,    // Insert
                    dp[i - 1][j - 1] + 1 // Replace
                );
            }
        }
    }

    return dp[m][n];
};