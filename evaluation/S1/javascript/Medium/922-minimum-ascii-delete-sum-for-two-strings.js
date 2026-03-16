// Source: https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two strings equal.
//
// Example:
// Input: s1 = "sea", s2 = "eat"
// Output: 231
// Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
// Deleting "t" from "eat" adds 116 to the sum.
// At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
//
// Constraints:
// 1 <= s1.length, s2.length <= 1000
// 	s1 and s2 consist of lowercase English letters.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s1
 * @param {string} s2
 * @return {number}
 */
var minimumDeleteSum = function(s1, s2) {
	const m = s1.length;
	const n = s2.length;

	// Create a 2D array for dynamic programming
	const dp = Array.from({ length: m + 1 }, () => new Array(n + 1).fill(0));

	// Base cases: if one string is empty, the cost is the sum of ASCII values of the other string
	for (let i = 1; i <= m; i++) {
		dp[i][0] = dp[i - 1][0] + s1.charCodeAt(i - 1);
	}
	for (let j = 1; j <= n; j++) {
		dp[0][j] = dp[0][j - 1] + s2.charCodeAt(j - 1);
	}

	// Fill the DP table
	for (let i = 1; i <= m; i++) {
		for (let j = 1; j <= n; j++) {
			if (s1[i - 1] === s2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1]; // No cost if characters are the same
			} else {
				dp[i][j] = Math.min(
					dp[i - 1][j] + s1.charCodeAt(i - 1), // Delete from s1
					dp[i][j - 1] + s2.charCodeAt(j - 1) // Delete from s2
				);
			}
		}
	}

	return dp[m][n]; // The answer is in the bottom-right cell
};
