// Source: https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums and an integer target.
//
// Return the number of non-empty subsequences of nums such that the sum of the minimum and maximum element on it is less or equal to target. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [3,5,6,7], target = 9
// Output: 4
// Explanation: There are 4 subsequences that satisfy the condition.
// [3] -> Min value + max value <= target (3 + 3 <= 9)
// [3,5] -> (3 + 5 <= 9)
// [3,5,6] -> (3 + 6 <= 9)
// [3,6] -> (3 + 6 <= 9)
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	1 <= target <= 106
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
// - Binary Exponentiation (number, mod-exp, recursion)
//   • When to use: Use this algorithm to efficiently compute large integer powers of a number, especially when results need to be taken modulo a specific value. It is crucial for problems requiring powers with large exponents.
//   • Idea: Binary exponentiation, also known as exponentiation by squaring, computes a^n by breaking down the exponent n into its binary representation. This method significantly reduces the number of multiplications required, achieving an O(log n) time complexity.
//   • Invariants: In the iterative approach, (current_result * (original_base ^ original_exponent)) remains constant.; The exponent n is always non-negative and decreases towards zero.
//   • Tips: Apply the modulo operation at each multiplication step to prevent intermediate overflow.; The iterative approach is generally preferred over recursion to avoid potential stack overflow for very large exponents.
//   • Pitfalls: Forgetting to apply modulo at each step can lead to integer overflow, especially with large bases.; Incorrectly handling the base case for n=0 or n=1.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
 */
var numSubseq = function(nums, target) {
	nums.sort((a, b) => a - b);
	const mod = 1e9 + 7;
	let left = 0;
	let right = nums.length - 1;
	let count = 0;

	while (left <= right) {
		if (nums[left] + nums[right] > target) {
			right--;
		} else {
			count = (count + powMod(2, right - left, mod)) % mod;
			left++;
		}
	}

	return count;
};
