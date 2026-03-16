// Source: https://leetcode.com/problems/string-compression-ii/   |   Difficulty: Hard
//
// Problem Description:
// Run-length encoding is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string "aabccc" we replace "aa" by "a2" and replace "ccc" by "c3". Thus the compressed string becomes "a2bc3".
//
// Notice that in this problem, we are not adding '1' after single characters.
//
// Given a string s and an integer k. You need to delete at most k characters from s such that the run-length encoded version of s has minimum length.
//
// Find the minimum length of the run-length encoded version of s after deleting at most k characters.
//
// Example:
// Input: s = "aaabcccd", k = 2
// Output: 4
// Explanation: Compressing s without deleting anything will give us "a3bc3d" of length 6. Deleting any of the characters 'a' or 'c' would at most decrease the length of the compressed string to 5, for instance delete 2 'a' then we will have s = "abcccd" which compressed is abc3d. Therefore, the optimal way is to delete 'b' and 'd', then the compressed version of s will be "a3c3" of length 4.
//
// Constraints:
// 1 <= s.length <= 100
// 	0 <= k <= s.length
// 	s contains only lowercase English letters.
//
// Helpful references (internal KB):
// - Longest Increasing Subsequence (array, dp-1d)
//   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
//   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
//   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
//   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var getLengthOfOptimalCompression = function(s, k) {
	const n = s.length;
	const memo = Array.from({ length: n }, () => Array(k + 1).fill(-1));

	const digitsLen = (count) => {
		if (count >= 100) return 3;
		if (count >= 10) return 2;
		if (count >= 2) return 1;
		return 0;
	};

	const dfs = (i, del) => {
		if (del < 0) return Number.POSITIVE_INFINITY;
		if (i >= n) return 0;
		if (memo[i][del] !== -1) return memo[i][del];

		// Option 1: delete current character
		let best = dfs(i + 1, del - 1);

		// Option 2: keep current character and form a run
		let same = 0;
		let removed = 0;
		for (let j = i; j < n; j++) {
			if (s[j] === s[i]) {
				same++;
			} else {
				removed++;
				if (removed > del) break;
			}

			const cost = 1 + digitsLen(same) + dfs(j + 1, del - removed);
			if (cost < best) best = cost;
		}

		memo[i][del] = best;
		return best;
	};

	return dfs(0, k);
};
