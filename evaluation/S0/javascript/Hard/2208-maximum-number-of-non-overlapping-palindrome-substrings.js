// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and a positive integer k.
//
// Select a set of non-overlapping substrings from the string s that satisfy the following conditions:
//
//
// 	The length of each substring is at least k.
// 	Each substring is a palindrome.
//
//
// Return the maximum number of substrings in an optimal selection.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "abaccdbbd", k = 3
// Output: 2
// Explanation: We can select the substrings underlined in s = "abaccdbbd". Both "aba" and "dbbd" are palindromes and have a length of at least k = 3.
// It can be shown that we cannot find a selection with more than two valid substrings.
//
// Constraints:
// 1 <= k <= s.length <= 2000
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var maxPalindromes = function(s, k) {
    const n = s.length;
    const isPalindrome = Array.from({ length: n }, () => new Array(n).fill(false));
    for (let i = 0; i < n; i++) {
        isPalindrome[i][i] = true;
    }
    for (let length = 2; length <= n; length++) {
        for (let i = 0; i <= n - length; i++) {
            const j = i + length - 1;
            if (s[i] === s[j]) {
                isPalindrome[i][j] = length === 2 || isPalindrome[i + 1][j - 1];
            }
        }
    }
    const dp = new Array(n).fill(0);
    for (let i = 0; i < n; i++) {
        dp[i] = i > 0 ? dp[i - 1] : 0;
        for (let j = 0; j <= i - k + 1; j++) {
            if (isPalindrome[j][i]) {
                dp[i] = Math.max(dp[i], (j > 0 ? dp[j - 1] : 0) + 1);
            }
        }
    }
    return dp[n - 1];
};
