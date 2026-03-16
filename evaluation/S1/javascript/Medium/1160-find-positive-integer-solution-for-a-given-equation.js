// Source: https://leetcode.com/problems/find-positive-integer-solution-for-a-given-equation/   |   Difficulty: Medium
//
// Problem Description:
// Given a callable function f(x, y) with a hidden formula and a value z, reverse engineer the formula and return all positive integer pairs x and y where f(x,y) == z. You may return the pairs in any order.
//
// While the exact formula is hidden, the function is monotonically increasing, i.e.:
//
//
// 	f(x, y) < f(x + 1, y)
// 	f(x, y) < f(x, y + 1)
//
//
// The function interface is defined like this:
//
//
// interface CustomFunction {
// public:
//   // Returns some positive integer f(x, y) for two positive integers x and y based on a formula.
//   int f(int x, int y);
// };
//
//
// We will judge your solution as follows:
//
//
// 	The judge has a list of 9 hidden implementations of CustomFunction, along with a way to generate an answer key of all valid pairs for a specific z.
// 	The judge will receive two inputs: a function_id (to determine which implementation to test your code with), and the target z.
// 	The judge will call your findSolution and compare your results with the answer key.
// 	If your results match the answer key, your solution will be Accepted.
//
// Example:
// Input: function_id = 1, z = 5
// Output: [[1,4],[2,3],[3,2],[4,1]]
// Explanation: The hidden formula for function_id = 1 is f(x, y) = x + y.
// The following positive integer values of x and y make f(x, y) equal to 5:
// x=1, y=4 -> f(1, 4) = 1 + 4 = 5.
// x=2, y=3 -> f(2, 3) = 2 + 3 = 5.
// x=3, y=2 -> f(3, 2) = 3 + 2 = 5.
// x=4, y=1 -> f(4, 1) = 4 + 1 = 5.
//
// Constraints:
// 1 <= function_id <= 9
// 	1 <= z <= 100
// 	It is guaranteed that the solutions of f(x, y) == z will be in the range 1 <= x, y <= 1000.
// 	It is also guaranteed that f(x, y) will fit in 32 bit signed integer if 1 <= x, y <= 1000.
//
// Helpful references (internal KB):
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Floyd's Linked List Cycle Finding Algorithm (linked-list, two-pointers, simulation)
//   • When to use: Use this algorithm to efficiently detect if a linked list contains a cycle and, optionally, find the entry point of that cycle, using only constant extra space.
//   • Idea: This algorithm uses two pointers, one moving faster than the other, to detect if a cycle exists in a linked list. If a cycle is found, it can then determine the cycle's starting node in O(N) time complexity and O(1) space complexity.
//   • Invariants: The slow and fast pointers are always valid nodes or null.; In the detection phase, the fast pointer always covers twice the distance of the slow pointer.
//   • Tips: Initialize both slow and fast pointers at the head of the list.; Move the slow pointer by one step and the fast pointer by two steps in each iteration.
//   • Pitfalls: Forgetting to check for null on 'fast' and 'fast.next' before dereferencing them.; Incorrectly assuming the list is non-empty or has at least two nodes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * // This is the CustomFunction's API interface.
 * // You should not implement it, or speculate about its implementation
 * function CustomFunction() {
 *     @param {integer, integer} x, y
 *     @return {integer}
 *     this.f = function(x, y) {
 *         ...
 *     };
 * };
 */

/**
 * @param {CustomFunction} customfunction
 * @param {integer} z
 * @return {integer[][]}
 */
var findSolution = function(customfunction, z) {
	const result = [];
	let x = 1;
	let y = 1000;

	while (x <= 1000 && y >= 1) {
		const val = customfunction.f(x, y);

		if (val === z) {
			result.push([x, y]);
			x++;
			y--;
		} else if (val < z) {
			x++;
		} else {
			y--;
		}
	}

	return result;
};
