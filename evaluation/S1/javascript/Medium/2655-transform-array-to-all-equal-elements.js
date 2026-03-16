// Source: https://leetcode.com/problems/transform-array-to-all-equal-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of size n containing only 1 and -1, and an integer k.
//
// You can perform the following operation at most k times:
//
//
// 	
// 	Choose an index i (0 <= i < n - 1), and multiply both nums[i] and nums[i + 1] by -1.
// 	
//
//
// Note that you can choose the same index i more than once in different operations.
//
// Return true if it is possible to make all elements of the array equal after at most k operations, and false otherwise.
//
// Example:
// Input: nums = [1,-1,1,-1,1], k = 3
//
// Output: true
//
// Explanation:
//
// We can make all elements in the array equal in 2 operations as follows:
//
//
// 	Choose index i = 1, and multiply both nums[1] and nums[2] by -1. Now nums = [1,1,-1,-1,1].
// 	Choose index i = 2, and multiply both nums[2] and nums[3] by -1. Now nums = [1,1,1,1,1].
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	nums[i] is either -1 or 1.
// 	1 <= k <= n
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
//   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
//   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
//   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
//   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {boolean}
 */
var canMakeEqual = function(nums, k) {
	const minOpsToTarget = (target) => {
		const arr = nums.slice();
		let ops = 0;

		for (let i = 0; i < arr.length - 1; i++) {
			if (arr[i] !== target) {
				ops++;
				if (ops > k) {
					return Number.POSITIVE_INFINITY;
				}
				arr[i] = -arr[i];
				arr[i + 1] = -arr[i + 1];
			}
		}

		return arr[arr.length - 1] === target ? ops : Number.POSITIVE_INFINITY;
	};

	if (nums.length === 0) {
		return true;
	}

	const opsAllOne = minOpsToTarget(1);
	if (opsAllOne <= k) {
		return true;
	}

	const opsAllNegOne = minOpsToTarget(-1);
	return opsAllNegOne <= k;
};
