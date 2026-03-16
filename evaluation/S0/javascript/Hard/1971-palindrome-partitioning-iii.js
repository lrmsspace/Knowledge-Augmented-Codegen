// Source: https://leetcode.com/problems/palindrome-partitioning-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s containing lowercase letters and an integer k. You need to :
//
//
// 	First, change some characters of s to other lowercase English letters.
// 	Then divide s into k non-empty disjoint substrings such that each substring is a palindrome.
//
//
// Return the minimal number of characters that you need to change to divide the string.
//
// Example:
// Input: s = "abc", k = 2
// Output: 1
// Explanation: You can split the string into "ab" and "c", and change 1 character in "ab" to make it palindrome.
//
// Constraints:
// 1 <= k <= s.length <= 100.
// 	s only contains lowercase English letters.
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var palindromePartition = function(s, k) {
    const n = s.length;
    const dp = Array.from({ length: n }, () => new Array(n).fill(0));
    for (let i = n - 1; i >= 0; i--) {
        for (let j = i + 1; j < n; j++) {
            dp[i][j] = s[i] === s[j] ? dp[i + 1][j - 1] : dp[i + 1][j - 1] + 1;
        }
    }
    const memo = new Map();
    function dfs(start, k) {
        if (k === 1) {
            return dp[start][n - 1];
        }
        const key = `${start}-${k}`;
        if (memo.has(key)) {
            return memo.get(key);
        }
        let minChanges = Infinity;
        for (let end = start; end < n - k + 1; end++) {
            minChanges = Math.min(minChanges, dp[start][end] + dfs(end + 1, k - 1));
        }
        memo.set(key, minChanges);
        return minChanges;
    }
    return dfs(0, k);
};
