// Source: https://leetcode.com/problems/fruit-into-baskets/   |   Difficulty: Medium
//
// Problem Description:
// You are visiting a farm that has a single row of fruit trees arranged from left to right. The trees are represented by an integer array fruits where fruits[i] is the type of fruit the ith tree produces.
//
// You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:
//
//
// 	You only have two baskets, and each basket can only hold a single type of fruit. There is no limit on the amount of fruit each basket can hold.
// 	Starting from any tree of your choice, you must pick exactly one fruit from every tree (including the start tree) while moving to the right. The picked fruits must fit in one of your baskets.
// 	Once you reach a tree with fruit that cannot fit in your baskets, you must stop.
//
//
// Given the integer array fruits, return the maximum number of fruits you can pick.
//
// Example:
// Input: fruits = [1,2,1]
// Output: 3
// Explanation: We can pick from all 3 trees.
//
// Constraints:
// 1 <= fruits.length <= 105
// 	0 <= fruits[i] < fruits.length
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
//   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
//   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
//   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
//   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
//   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} fruits
 * @return {number}
 */
var totalFruit = function(fruits) {
	const basket = new Map();
	let maxFruits = 0;
	let left = 0;

	for (let right = 0; right < fruits.length; right++) {
		const fruit = fruits[right];
		basket.set(fruit, (basket.get(fruit) || 0) + 1);

		while (basket.size > 2) {
			const leftFruit = fruits[left];
			basket.set(leftFruit, basket.get(leftFruit) - 1);

			if (basket.get(leftFruit) === 0) {
				basket.delete(leftFruit);
			}
			left++;
		}

		maxFruits = Math.max(maxFruits, right - left + 1);
	}

	return maxFruits;
};
