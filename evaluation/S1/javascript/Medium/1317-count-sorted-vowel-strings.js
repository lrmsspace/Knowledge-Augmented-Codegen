// Source: https://leetcode.com/problems/count-sorted-vowel-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.
//
// A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.
//
// Example:
// Input: n = 1
// Output: 5
// Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
//
// Constraints:
// 1 <= n <= 50
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
 * @param {number} n
 * @return {number}
 */
var countVowelStrings = function(n) {
	// dp[i][j] := number of sorted vowel strings of length i that end with the j-th vowel
	const dp = Array.from({length: n+1}, () => Array(5).fill(0));
	for (let j = 0; j < 5; j++) dp[1][j] = 1;

	for (let i = 2; i <= n; i++) {
		for (let j = 0; j < 5; j++) {
			dp[i][j] = dp[i-1][j];
			if (j > 0) dp[i][j] += dp[i][j-1];
		}
	}

	return dp[n].reduce((a,b) => a+b, 0);
};
