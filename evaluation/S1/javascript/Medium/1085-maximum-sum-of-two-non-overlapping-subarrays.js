// Source: https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and two integers firstLen and secondLen, return the maximum sum of elements in two non-overlapping subarrays with lengths firstLen and secondLen.
//
// The array with length firstLen could occur before or after the array with length secondLen, but they have to be non-overlapping.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
// Output: 20
// Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.
//
// Constraints:
// 1 <= firstLen, secondLen <= 1000
// 	2 <= firstLen + secondLen <= 1000
// 	firstLen + secondLen <= nums.length <= 1000
// 	0 <= nums[i] <= 1000
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
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
 * @param {number[]} nums
 * @param {number} firstLen
 * @param {number} secondLen
 * @return {number}
 */
var maxSumTwoNoOverlap = function(nums, firstLen, secondLen) {
	const n = nums.length;
	const prefixSums = new Array(n + 1).fill(0);

	for (let i = 0; i < n; i++) {
		prefixSums[i + 1] = prefixSums[i] + nums[i];
	}

	let maxSum = 0;

	for (let i = firstLen + secondLen; i <= n; i++) {
		const firstSubarraySum = prefixSums[i - secondLen] - prefixSums[i - secondLen - firstLen];
		const secondSubarraySum = prefixSums[i] - prefixSums[i - secondLen];
		maxSum = Math.max(maxSum, firstSubarraySum + secondSubarraySum);
	}

	for (let i = firstLen + secondLen; i <= n; i++) {
		const secondSubarraySum = prefixSums[i - firstLen] - prefixSums[i - firstLen - secondLen];
		const firstSubarraySum = prefixSums[i] - prefixSums[i - firstLen];
		maxSum = Math.max(maxSum, firstSubarraySum + secondSubarraySum);
	}

	return maxSum;
};
