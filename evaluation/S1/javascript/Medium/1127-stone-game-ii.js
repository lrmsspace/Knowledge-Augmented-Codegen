// Source: https://leetcode.com/problems/stone-game-ii/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob continue their games with piles of stones. There are a number of piles arranged in a row, and each pile has a positive integer number of stones piles[i]. The objective of the game is to end with the most stones.
//
// Alice and Bob take turns, with Alice starting first.
//
// On each player's turn, that player can take all the stones in the first X remaining piles, where 1 <= X <= 2M. Then, we set M = max(M, X). Initially, M = 1.
//
// The game continues until all the stones have been taken.
//
// Assuming Alice and Bob play optimally, return the maximum number of stones Alice can get.
//
// Example:
// Input: piles = [2,7,9,4,4]
//
// Output: 10
//
// Explanation:
//
//
// 	If Alice takes one pile at the beginning, Bob takes two piles, then Alice takes 2 piles again. Alice can get 2 + 4 + 4 = 10 stones in total.
// 	If Alice takes two piles at the beginning, then Bob can take all three piles left. In this case, Alice get 2 + 7 = 9 stones in total.
//
//
// So we return 10 since it's larger.
//
// Constraints:
// 1 <= piles.length <= 100
// 	1 <= piles[i] <= 104
//
// Helpful references (internal KB):
// - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
//   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
//   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
//   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
//   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
//   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} piles
 * @return {number}
 */
var stoneGameII = function(piles) {
	const n = piles.length;
	const prefixSum = new Array(n + 1).fill(0);
	for (let i = 0; i < n; i++) {
		prefixSum[i + 1] = prefixSum[i] + piles[i];
	}

	const memo = new Map();

	function dfs(i, M) {
		if (i >= n) return 0;
		const key = `${i},${M}`;
		if (memo.has(key)) return memo.get(key);

		let maxStones = 0;
		for (let X = 1; X <= 2 * M; X++) {
			if (i + X > n) break;
			const currentStones = prefixSum[i + X] - prefixSum[i];
			const opponentStones = dfs(i + X, Math.max(M, X));
			maxStones = Math.max(maxStones, currentStones + opponentStones);
		}

		memo.set(key, maxStones);
		return maxStones;
	}

	return dfs(0, 1);
};
