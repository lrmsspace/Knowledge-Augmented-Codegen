// Source: https://leetcode.com/problems/minimum-cost-good-caption/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string caption of length n. A good caption is a string where every character appears in groups of at least 3 consecutive occurrences.
//
// For example:
//
//
// 	"aaabbb" and "aaaaccc" are good captions.
// 	"aabbb" and "ccccd" are not good captions.
//
//
// You can perform the following operation any number of times:
//
// Choose an index i (where 0 <= i < n) and change the character at that index to either:
//
//
// 	The character immediately before it in the alphabet (if caption[i] != 'a').
// 	The character immediately after it in the alphabet (if caption[i] != 'z').
//
//
// Your task is to convert the given caption into a good caption using the minimum number of operations, and return it. If there are multiple possible good captions, return the lexicographically smallest one among them. If it is impossible to create a good caption, return an empty string "".
//
// Example:
// Input: caption = "cdcd"
//
// Output: "cccc"
//
// Explanation:
//
// It can be shown that the given caption cannot be transformed into a good caption with fewer than 2 operations. The possible good captions that can be created using exactly 2 operations are:
//
//
// 	"dddd": Change caption[0] and caption[2] to their next character 'd'.
// 	"cccc": Change caption[1] and caption[3] to their previous character 'c'.
//
//
// Since "cccc" is lexicographically smaller than "dddd", return "cccc".
//
// Constraints:
// 1 <= caption.length <= 5 * 104
// 	caption consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
// - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
//   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
//   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
//   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
//   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
//   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} caption
 * @return {string}
 */
var minCostGoodCaption = function(caption) {
	const n = caption.length;
	if (n === 0) {
		return "";
	}

	const INF = 1e15;
	const ALPHA = 26;
	const PREV_NONE = 26;
	const STATES = 27 * 3;
	const dp = new Float64Array((n + 1) * STATES);
	dp.fill(INF);

	const idx = (i, prev, run) => (i * 27 + prev) * 3 + run;

	for (let prev = 0; prev <= PREV_NONE; prev += 1) {
		dp[idx(n, prev, 2)] = 0;
	}

	for (let i = n - 1; i >= 0; i -= 1) {
		const code = caption.charCodeAt(i) - 97;
		for (let prev = 0; prev <= PREV_NONE; prev += 1) {
			for (let run = 0; run <= 2; run += 1) {
				if (prev === PREV_NONE && run !== 2) {
					dp[idx(i, prev, run)] = INF;
					continue;
				}

				let best = INF;
				for (let c = 0; c < ALPHA; c += 1) {
					let nextRun;
					if (prev === PREV_NONE) {
						nextRun = 0;
					} else if (c === prev) {
						nextRun = run === 0 ? 1 : 2;
					} else {
						if (run !== 2) {
							continue;
						}
						nextRun = 0;
					}

					const cost = Math.abs(code - c) + dp[idx(i + 1, c, nextRun)];
					if (cost < best) {
						best = cost;
					}
				}

				dp[idx(i, prev, run)] = best;
			}
		}
	}

	if (dp[idx(0, PREV_NONE, 2)] >= INF / 2) {
		return "";
	}

	const result = new Array(n);
	let prev = PREV_NONE;
	let run = 2;
	for (let i = 0; i < n; i += 1) {
		const code = caption.charCodeAt(i) - 97;
		const targetCost = dp[idx(i, prev, run)];
		let chosen = 0;
		let nextRun = 0;

		for (let c = 0; c < ALPHA; c += 1) {
			let candidateRun;
			if (prev === PREV_NONE) {
				candidateRun = 0;
			} else if (c === prev) {
				candidateRun = run === 0 ? 1 : 2;
			} else {
				if (run !== 2) {
					continue;
				}
				candidateRun = 0;
			}

			const cost = Math.abs(code - c) + dp[idx(i + 1, c, candidateRun)];
			if (cost === targetCost) {
				chosen = c;
				nextRun = candidateRun;
				break;
			}
		}

		result[i] = String.fromCharCode(97 + chosen);
		prev = chosen;
		run = nextRun;
	}

	return result.join("");
};
