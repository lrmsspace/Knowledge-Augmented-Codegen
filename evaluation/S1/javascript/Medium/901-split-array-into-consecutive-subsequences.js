// Source: https://leetcode.com/problems/split-array-into-consecutive-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums that is sorted in non-decreasing order.
//
// Determine if it is possible to split nums into one or more subsequences such that both of the following conditions are true:
//
//
// 	Each subsequence is a consecutive increasing sequence (i.e. each integer is exactly one more than the previous integer).
// 	All subsequences have a length of 3 or more.
//
//
// Return true if you can split nums according to the above conditions, or false otherwise.
//
// A subsequence of an array is a new array that is formed from the original array by deleting some (can be none) of the elements without disturbing the relative positions of the remaining elements. (i.e., [1,3,5] is a subsequence of [1,2,3,4,5] while [1,3,2] is not).
//
// Example:
// Input: nums = [1,2,3,3,4,5]
// Output: true
// Explanation: nums can be split into the following subsequences:
// [1,2,3,3,4,5] --> 1, 2, 3
// [1,2,3,3,4,5] --> 3, 4, 5
//
// Constraints:
// 1 <= nums.length <= 104
// 	-1000 <= nums[i] <= 1000
// 	nums is sorted in non-decreasing order.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// - Longest increasing subsequence (array, greedy, dp-1d)
//   • When to use: Use when finding the longest sequence of elements in a given array such that each element is greater than the preceding one, without changing their relative order. It's applicable for optimizing problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of an array where elements are in strictly increasing order. It can be solved in O(N log N) time using a greedy approach with binary search, or O(N^2) using dynamic programming.
//   • Invariants: The 'tails' array elements are always in strictly increasing order.; tails[i] stores the smallest possible ending element of an increasing subsequence of length i+1.
//   • Tips: Prefer the O(N log N) greedy approach with binary search for better performance.; The 'tails' array in the greedy approach stores the smallest tail of all increasing subsequences of a certain length.
//   • Pitfalls: Confusing LIS with Longest Common Subsequence (LCS) or contiguous subarrays.; Incorrectly handling duplicate elements when 'strictly increasing' is required.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var isPossible = function(nums) {
	const freq = new Map(); // Frequency of each number
	const appendFreq = new Map(); // Frequency of subsequences that can be extended

	for (const num of nums) {
		freq.set(num, (freq.get(num) || 0) + 1);
	}

	for (const num of nums) {
		if (freq.get(num) === 0) {
			continue; // Skip if the number is already used
		}

		if (appendFreq.get(num - 1) > 0) {
			// Extend a subsequence ending with num-1
			appendFreq.set(num - 1, appendFreq.get(num - 1) - 1);
			appendFreq.set(num, (appendFreq.get(num) || 0) + 1);
		} else if (freq.get(num + 1) > 0 && freq.get(num + 2) > 0) {
			// Create a new subsequence num, num+1, num+2
			freq.set(num + 1, freq.get(num + 1) - 1);
			freq.set(num + 2, freq.get(num + 2) - 1);
			appendFreq.set(num + 2, (appendFreq.get(num + 2) || 0) + 1);
		} else {
			return false; // Cannot use num in any valid way
		}

		freq.set(num, freq.get(num) - 1); // Use the current number
	}

	return true;
};
