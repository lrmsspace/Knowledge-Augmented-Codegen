// Source: https://leetcode.com/problems/circular-array-loop/   |   Difficulty: Medium
//
// Problem Description:
// You are playing a game involving a circular array of non-zero integers nums. Each nums[i] denotes the number of indices forward/backward you must move if you are located at index i:
//
//
// 	If nums[i] is positive, move nums[i] steps forward, and
// 	If nums[i] is negative, move nums[i] steps backward.
//
//
// Since the array is circular, you may assume that moving forward from the last element puts you on the first element, and moving backwards from the first element puts you on the last element.
//
// A cycle in the array consists of a sequence of indices seq of length k where:
//
//
// 	Following the movement rules above results in the repeating index sequence seq[0] -> seq[1] -> ... -> seq[k - 1] -> seq[0] -> ...
// 	Every nums[seq[j]] is either all positive or all negative.
// 	k > 1
//
//
// Return true if there is a cycle in nums, or false otherwise.
//
// Example:
// Input: nums = [2,-1,1,2,2]
// Output: true
// Explanation: The graph shows how the indices are connected. White nodes are jumping forward, while red is jumping backward.
// We can see the cycle 0 --> 2 --> 3 --> 0 --> ..., and all of its nodes are white (jumping in the same direction).
//
// Constraints:
// 1 <= nums.length <= 5000
// 	-1000 <= nums[i] <= 1000
// 	nums[i] != 0
//
//
//  
// Follow up: Could you solve it in O(n) time complexity and O(1) extra space complexity?
//
// Helpful references (internal KB):
// - Floyd's Linked List Cycle Finding Algorithm (linked-list, two-pointers, simulation)
//   • When to use: Use this algorithm to efficiently detect if a linked list contains a cycle and, optionally, find the entry point of that cycle, using only constant extra space.
//   • Idea: This algorithm uses two pointers, one moving faster than the other, to detect if a cycle exists in a linked list. If a cycle is found, it can then determine the cycle's starting node in O(N) time complexity and O(1) space complexity.
//   • Invariants: The slow and fast pointers are always valid nodes or null.; In the detection phase, the fast pointer always covers twice the distance of the slow pointer.
//   • Tips: Initialize both slow and fast pointers at the head of the list.; Move the slow pointer by one step and the fast pointer by two steps in each iteration.
//   • Pitfalls: Forgetting to check for null on 'fast' and 'fast.next' before dereferencing them.; Incorrectly assuming the list is non-empty or has at least two nodes.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Josephus Problem (number, simulation, recursion)
//   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
//   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
//   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
//   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
//   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
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
var circularArrayLoop = function(nums) {
	const n = nums.length;

	for (let i = 0; i < n; i++) {
		if (nums[i] === 0) continue;

		let slow = i;
		let fast = i;
		const direction = nums[i] > 0; // true for positive, false for negative

		while (true) {
			slow = getNextIndex(nums, slow, direction);
			fast = getNextIndex(nums, getNextIndex(nums, fast, direction), direction);

			if (slow === -1 || fast === -1) break; // No cycle
			if (slow === fast) return true; // Cycle found
		}
	}

	return false;

	function getNextIndex(nums, index, direction) {
		const n = nums.length;
		const nextDirection = nums[index] > 0;

		if (direction !== nextDirection) return -1; // Change in direction

		return (index + nums[index] + n) % n; // Handle circular indexing
	}
};
