// Source: https://leetcode.com/problems/shortest-common-supersequence/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them.
//
// A string s is a subsequence of string t if deleting some number of characters from t (possibly 0) results in the string s.
//
// Example:
// Input: str1 = "abac", str2 = "cab"
// Output: "cabac"
// Explanation: 
// str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
// str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
// The answer provided is the shortest such string that satisfies these properties.
//
// Constraints:
// 1 <= str1.length, str2.length <= 1000
// 	str1 and str2 consist of lowercase English letters.
//

/**
 * @param {string} str1
 * @param {string} str2
 * @return {string}
 */
var shortestCommonSupersequence = function(str1, str2) {
    const m = str1.length;
    const n = str2.length;
    const dp = Array.from({ length: m + 1 }, () => new Array(n + 1).fill(0));
    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            if (str1[i - 1] === str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    let i = m, j = n;
    const result = [];
    while (i > 0 && j > 0) {
        if (str1[i - 1] === str2[j - 1]) {
            result.push(str1[i - 1]);
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            result.push(str1[i - 1]);
            i--;
        }
        else {
            result.push(str2[j - 1]);
            j--;
        }
    }
    while (i > 0) {
        result.push(str1[i - 1]);
        i--;
    }
    while (j > 0) {
        result.push(str2[j - 1]);
        j--;
    }
    return result.reverse().join('');   
};
