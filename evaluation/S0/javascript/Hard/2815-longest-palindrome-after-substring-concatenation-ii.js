// Source: https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings, s and t.
//
// You can create a new string by selecting a substring from s (possibly empty) and a substring from t (possibly empty), then concatenating them in order.
//
// Return the length of the longest palindrome that can be formed this way.
//
// Example:
// Input: s = "a", t = "a"
//
// Output: 2
//
// Explanation:
//
// Concatenating "a" from s and "a" from t results in "aa", which is a palindrome of length 2.
//
// Constraints:
// 1 <= s.length, t.length <= 1000
//  s and t consist of lowercase English letters.
//

/**
 * @param {string} s
 * @param {string} t
 * @return {number}
 */
var longestPalindrome = function(s, t) {
    const combined = s + t;
    const n = combined.length;
    const dp = Array.from({ length: n }, () => Array(n).fill(0));
    let maxLength = 0;
    for (let length = 1; length <= n; length++) {
        for (let i = 0; i <= n - length; i++) {
            const j = i + length - 1;
            if (combined[i] === combined[j]) {
                dp[i][j] = (length <= 2) ? length : dp[i + 1][j - 1] + 2;
            }
            else {
                dp[i][j] = Math.max(dp[i + 1][j], dp[i][j - 1]);
            }
            if (i < s.length && j >= s.length) {
                maxLength = Math.max(maxLength, dp[i][j]);
            }
        }
    }
    return maxLength;
};
