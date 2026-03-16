// Source: https://leetcode.com/problems/count-special-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// A special subsequence is defined as a subsequence of length 4, represented by indices (p, q, r, s), where p < q < r < s. This subsequence must satisfy the following conditions:
//
//
//  nums[p] * nums[r] == nums[q] * nums[s]
//  There must be at least one element between each pair of indices. In other words, q - p > 1, r - q > 1 and s - r > 1.
//
//
// Return the number of different special subsequences in nums.
//
// Example:
// Input: nums = [1,2,3,4,3,6,1]
//
// Output: 1
//
// Explanation:
//
// There is one special subsequence in nums.
//
//
//  (p, q, r, s) = (0, 2, 4, 6):
//
//  
//   This corresponds to elements (1, 3, 3, 1).
//   nums[p] * nums[r] = nums[0] * nums[4] = 1 * 3 = 3
//   nums[q] * nums[s] = nums[2] * nums[6] = 3 * 1 = 3
//
// Constraints:
// 7 <= nums.length <= 1000
//  1 <= nums[i] <= 1000
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var numberOfSubsequences = function(nums) {
	const n = nums.length;
	const leftRatioCount = new Map();
	let total = 0;

	const gcd = (a, b) => {
		while (b !== 0) {
			const t = a % b;
			a = b;
			b = t;
		}
		return a;
	};

	const ratioKey = (num, den) => {
		const g = gcd(num, den);
		return `${num / g}/${den / g}`;
	};

	for (let r = 2; r <= n - 3; r++) {
		const q = r - 2;
		if (q >= 2) {
			for (let p = 0; p <= q - 2; p++) {
				const key = ratioKey(nums[p], nums[q]);
				leftRatioCount.set(key, (leftRatioCount.get(key) || 0) + 1);
			}
		}

		for (let s = r + 2; s < n; s++) {
			const key = ratioKey(nums[s], nums[r]);
			const count = leftRatioCount.get(key);
			if (count) {
				total += count;
			}
		}
	}

	return total;
};
