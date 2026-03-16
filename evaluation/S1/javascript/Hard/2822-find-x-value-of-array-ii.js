// Source: https://leetcode.com/problems/find-x-value-of-array-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums and a positive integer k. You are also given a 2D array queries, where queries[i] = [indexi, valuei, starti, xi].
//
// You are allowed to perform an operation once on nums, where you can remove any suffix from nums such that nums remains non-empty.
//
// The x-value of nums for a given x is defined as the number of ways to perform this operation so that the product of the remaining elements leaves a remainder of x modulo k.
//
// For each query in queries you need to determine the x-value of nums for xi after performing the following actions:
//
//
// 	Update nums[indexi] to valuei. Only this step persists for the rest of the queries.
// 	Remove the prefix nums[0..(starti - 1)] (where nums[0..(-1)] will be used to represent the empty prefix).
//
//
// Return an array result of size queries.length where result[i] is the answer for the ith query.
//
// A prefix of an array is a subarray that starts from the beginning of the array and extends to any point within it.
//
// A suffix of an array is a subarray that starts at any point within the array and extends to the end of the array.
//
// Note that the prefix and suffix to be chosen for the operation can be empty.
//
// Note that x-value has a different definition in this version.
//
// Example:
// Input: nums = [1,2,3,4,5], k = 3, queries = [[2,2,0,2],[3,3,3,0],[0,1,0,1]]
//
// Output: [2,2,2]
//
// Explanation:
//
//
// 	For query 0, nums becomes [1, 2, 2, 4, 5], and the empty prefix must be removed. The possible operations are:
//
// 	
// 		Remove the suffix [2, 4, 5]. nums becomes [1, 2].
// 		Remove the empty suffix. nums becomes [1, 2, 2, 4, 5] with a product 80, which gives remainder 2 when divided by 3.
// 	
// 	
// 	For query 1, nums becomes [1, 2, 2, 3, 5], and the prefix [1, 2, 2] must be removed. The possible operations are:
// 	
// 		Remove the empty suffix. nums becomes [3, 5].
// 		Remove the suffix [5]. nums becomes [3].
// 	
// 	
// 	For query 2, nums becomes [1, 2, 2, 3, 5], and the empty prefix must be removed. The possible operations are:
// 	
// 		Remove the suffix [2, 2, 3, 5]. nums becomes [1].
// 		Remove the suffix [3, 5]. nums becomes [1, 2, 2].
//
// Constraints:
// 1 <= nums[i] <= 109
// 	1 <= nums.length <= 105
// 	1 <= k <= 5
// 	1 <= queries.length <= 2 * 104
// 	queries[i] == [indexi, valuei, starti, xi]
// 	0 <= indexi <= nums.length - 1
// 	1 <= valuei <= 109
// 	0 <= starti <= nums.length - 1
// 	0 <= xi <= k - 1
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
//   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
//   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
//   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
// - MEX (minimal excluded) of a sequence (tree, binary-search)
//   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
//   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
//   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
//   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
//   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
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
 * @param {number[][]} queries
 * @return {number[]}
 */
var resultArray = function(nums, k, queries) {
	const n = nums.length;
	const size = (() => {
		let s = 1;
		while (s < n) s <<= 1;
		return s;
	})();

	const emptyNode = () => ({
		prod: 1 % k,
		pref: new Array(k).fill(0)
	});

	const makeLeaf = (value) => {
		const pref = new Array(k).fill(0);
		const modVal = value % k;
		pref[modVal] = 1;
		return { prod: modVal, pref };
	};

	const combine = (left, right) => {
		if (!left) return right;
		if (!right) return left;
		const pref = new Array(k).fill(0);
		for (let m = 0; m < k; m++) {
			pref[m] += left.pref[m];
		}
		for (let m = 0; m < k; m++) {
			const idx = (left.prod * m) % k;
			pref[idx] += right.pref[m];
		}
		const prod = (left.prod * right.prod) % k;
		return { prod, pref };
	};

	const tree = new Array(size * 2);
	for (let i = 0; i < size; i++) {
		tree[size + i] = i < n ? makeLeaf(nums[i]) : emptyNode();
	}
	for (let i = size - 1; i > 0; i--) {
		tree[i] = combine(tree[i * 2], tree[i * 2 + 1]);
	}

	const update = (index, value) => {
		let pos = size + index;
		tree[pos] = makeLeaf(value);
		pos >>= 1;
		while (pos > 0) {
			tree[pos] = combine(tree[pos * 2], tree[pos * 2 + 1]);
			pos >>= 1;
		}
	};

	const query = (node, left, right, ql, qr) => {
		if (ql > right || qr < left) return null;
		if (ql <= left && right <= qr) return tree[node];
		const mid = (left + right) >> 1;
		const leftRes = query(node * 2, left, mid, ql, qr);
		const rightRes = query(node * 2 + 1, mid + 1, right, ql, qr);
		return combine(leftRes, rightRes);
	};

	const result = new Array(queries.length);
	for (let i = 0; i < queries.length; i++) {
		const [index, value, start, x] = queries[i];
		update(index, value);
		const node = query(1, 0, size - 1, start, n - 1);
		result[i] = node ? node.pref[x] : 0;
	}

	return result;
};
