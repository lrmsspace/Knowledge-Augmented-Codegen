// Source: https://leetcode.com/problems/k-th-symbol-in-grammar/   |   Difficulty: Medium
//
// Problem Description:
// We build a table of n rows (1-indexed). We start by writing 0 in the 1st row. Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.
//
//
// 	For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the 3rd row is 0110.
//
//
// Given two integer n and k, return the kth (1-indexed) symbol in the nth row of a table of n rows.
//
// Example:
// Input: n = 1, k = 1
// Output: 0
// Explanation: row 1: 0
//
// Constraints:
// 1 <= n <= 30
// 	1 <= k <= 2n - 1
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
 * @param {number} k
 * @return {number}
 */
var kthGrammar = function(n, k) {
	if (n === 1) {
		return 0;
	}

	const mid = Math.pow(2, n - 2);
	if (k <= mid) {
		return kthGrammar(n - 1, k);
	} else {
		return kthGrammar(n - 1, k - mid) ^ 1;
	}
};
