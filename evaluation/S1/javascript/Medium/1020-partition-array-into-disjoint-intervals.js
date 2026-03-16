// Source: https://leetcode.com/problems/partition-array-into-disjoint-intervals/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, partition it into two (contiguous) subarrays left and right so that:
//
//
// 	Every element in left is less than or equal to every element in right.
// 	left and right are non-empty.
// 	left has the smallest possible size.
//
//
// Return the length of left after such a partitioning.
//
// Test cases are generated such that partitioning exists.
//
// Example:
// Input: nums = [5,0,3,8,6]
// Output: 3
// Explanation: left = [5,0,3], right = [8,6]
//
// Constraints:
// 2 <= nums.length <= 105
// 	0 <= nums[i] <= 106
// 	There is at least one valid answer for the given input.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Range Minimum Query (array, sparse-table)
//   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
//   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
//   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
//   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
//   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
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
var partitionDisjoint = function(nums) {
	let maxLeft = nums[0];
	let maxSoFar = nums[0];
	let partitionIndex = 0;

	for (let i = 1; i < nums.length; i++) {
		if (nums[i] < maxLeft) {
			partitionIndex = i;
			maxLeft = maxSoFar;
		} else {
			maxSoFar = Math.max(maxSoFar, nums[i]);
		}
	}

	return partitionIndex + 1;
};
