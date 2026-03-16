// Source: https://leetcode.com/problems/the-k-strongest-values-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr and an integer k.
//
// A value arr[i] is said to be stronger than a value arr[j] if |arr[i] - m| > |arr[j] - m| where m is the centre of the array.
// If |arr[i] - m| == |arr[j] - m|, then arr[i] is said to be stronger than arr[j] if arr[i] > arr[j].
//
// Return a list of the strongest k values in the array. return the answer in any arbitrary order.
//
// The centre is the middle value in an ordered integer list. More formally, if the length of the list is n, the centre is the element in position ((n - 1) / 2) in the sorted list (0-indexed).
//
//
// 	For arr = [6, -3, 7, 2, 11], n = 5 and the centre is obtained by sorting the array arr = [-3, 2, 6, 7, 11] and the centre is arr[m] where m = ((5 - 1) / 2) = 2. The centre is 6.
// 	For arr = [-7, 22, 17, 3], n = 4 and the centre is obtained by sorting the array arr = [-7, 3, 17, 22] and the centre is arr[m] where m = ((4 - 1) / 2) = 1. The centre is 3.
//
// Example:
// Input: arr = [1,2,3,4,5], k = 2
// Output: [5,1]
// Explanation: Centre is 3, the elements of the array sorted by the strongest are [5,1,4,2,3]. The strongest 2 elements are [5, 1]. [1, 5] is also accepted answer.
// Please note that although |5 - 3| == |1 - 3| but 5 is stronger than 1 because 5 > 1.
//
// Constraints:
// 1 <= arr.length <= 105
// 	-105 <= arr[i] <= 105
// 	1 <= k <= arr.length
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} arr
 * @param {number} k
 * @return {number[]}
 */
var getStrongest = function(arr, k) {
	arr.sort((a, b) => a - b);
	const m = arr[Math.floor((arr.length - 1) / 2)];
	let left = 0;
	let right = arr.length - 1;
	const strongest = [];

	while (strongest.length < k) {
		const leftStrength = Math.abs(arr[left] - m);
		const rightStrength = Math.abs(arr[right] - m);

		if (leftStrength > rightStrength || (leftStrength === rightStrength && arr[left] > arr[right])) {
			strongest.push(arr[left]);
			left++;
		} else {
			strongest.push(arr[right]);
			right--;
		}
	}

	return strongest;
};
