// Source: https://leetcode.com/problems/longest-valid-parentheses/   |   Difficulty: Hard
//
// Problem Description:
// Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses substring.
//
// Example:
// Input: s = "(()"
// Output: 2
// Explanation: The longest valid parentheses substring is "()".
//
// Constraints:
// 0 <= s.length <= 3 * 104
// 	s[i] is '(', or ')'.
//

/**
 * @param {string} s
 * @return {number}
 */
var longestValidParentheses = function(s) {
    const n = s.length;
    const dp = new Array(n).fill(0);
    let maxLen = 0;
    for (let i = 1; i < n; i++) {
        if (s[i] === ')') {
            if (s[i - 1] === '(') {
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            } else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] === '(') {
                dp[i] = dp[i - 1] + 2 + (i - dp[i - 1] - 2 >= 0 ? dp[i - dp[i - 1] - 2] : 0);
            }
            maxLen = Math.max(maxLen, dp[i]);
        }
    }
    return maxLen;
        
};
