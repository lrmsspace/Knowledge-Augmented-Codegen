// Source: https://leetcode.com/problems/maximize-count-of-distinct-primes-after-split/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums having length n and a 2D integer array queries where queries[i] = [idx, val].
//
// For each query:
//
//
// 	Update nums[idx] = val.
// 	Choose an integer k with 1 <= k < n to split the array into the non-empty prefix nums[0..k-1] and suffix nums[k..n-1] such that the sum of the counts of distinct prime values in each part is maximum.
//
//
// Note: The changes made to the array in one query persist into the next query.
//
// Return an array containing the result for each query, in the order they are given.
//
// Example:
// Input: nums = [2,1,3,1,2], queries = [[1,2],[3,3]]
//
// Output: [3,4]
//
// Explanation:
//
//
// 	Initially nums = [2, 1, 3, 1, 2].
// 	After 1st query, nums = [2, 2, 3, 1, 2]. Split nums into [2] and [2, 3, 1, 2]. [2] consists of 1 distinct prime and [2, 3, 1, 2] consists of 2 distinct primes. Hence, the answer for this query is 1 + 2 = 3.
// 	After 2nd query, nums = [2, 2, 3, 3, 2]. Split nums into [2, 2, 3] and [3, 2] with an answer of 2 + 2 = 4.
// 	The output is [3, 4].
//
// Constraints:
// 2 <= n == nums.length <= 5 * 104
// 	1 <= queries.length <= 5 * 104
// 	1 <= nums[i] <= 105
// 	0 <= queries[i][0] < nums.length
// 	1 <= queries[i][1] <= 105
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Segment Tree (tree, array, segment-tree, divide-and-conquer)
//   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
//   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
//   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
//   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
// - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
//   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
//   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
//   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @return {number[]}
 */
var maximumCount = function(nums, queries) {
	const n = nums.length;
	const maxVal = getMaxValue(nums, queries);
	const isPrime = buildPrimeSieve(maxVal);
	const counts = new Array(maxVal + 1).fill(0);
	const minHeaps = new Array(maxVal + 1);
	const maxHeaps = new Array(maxVal + 1);
	const splitCount = n - 1;
	const segTree = new SegmentTree(splitCount);

	for (let i = 0; i < n; i++) {
		const v = nums[i];
		if (!isPrime[v]) continue;
		ensureHeaps(v, minHeaps, maxHeaps);
		minHeaps[v].push(i);
		maxHeaps[v].push(i);
		counts[v] += 1;
	}

	let distinctPrimeCount = 0;
	for (let v = 2; v <= maxVal; v++) {
		if (!isPrime[v] || counts[v] === 0) continue;
		distinctPrimeCount += 1;
		const minIdx = getValidMinIndex(v, minHeaps, nums);
		const maxIdx = getValidMaxIndex(v, maxHeaps, nums);
		applyInterval(segTree, minIdx, maxIdx, 1);
	}

	const results = new Array(queries.length);
	for (let qi = 0; qi < queries.length; qi++) {
		const idx = queries[qi][0];
		const val = queries[qi][1];
		const oldVal = nums[idx];

		if (oldVal !== val) {
			let oldMinBefore = null;
			let oldMaxBefore = null;
			let newMinBefore = null;
			let newMaxBefore = null;

			if (isPrime[oldVal]) {
				oldMinBefore = getValidMinIndex(oldVal, minHeaps, nums);
				oldMaxBefore = getValidMaxIndex(oldVal, maxHeaps, nums);
			}

			if (isPrime[val]) {
				newMinBefore = getValidMinIndex(val, minHeaps, nums);
				newMaxBefore = getValidMaxIndex(val, maxHeaps, nums);
			}

			nums[idx] = val;

			if (isPrime[oldVal]) {
				const before = counts[oldVal];
				counts[oldVal] -= 1;
				if (before === 1) distinctPrimeCount -= 1;
			}

			if (isPrime[val]) {
				const before = counts[val];
				counts[val] += 1;
				if (before === 0) distinctPrimeCount += 1;
			}

			if (isPrime[oldVal]) {
				const oldMinAfter = getValidMinIndex(oldVal, minHeaps, nums);
				const oldMaxAfter = getValidMaxIndex(oldVal, maxHeaps, nums);
				applyInterval(segTree, oldMinBefore, oldMaxBefore, -1);
				applyInterval(segTree, oldMinAfter, oldMaxAfter, 1);
			}

			if (isPrime[val]) {
				ensureHeaps(val, minHeaps, maxHeaps);
				minHeaps[val].push(idx);
				maxHeaps[val].push(idx);
				const newMinAfter = getValidMinIndex(val, minHeaps, nums);
				const newMaxAfter = getValidMaxIndex(val, maxHeaps, nums);
				applyInterval(segTree, newMinBefore, newMaxBefore, -1);
				applyInterval(segTree, newMinAfter, newMaxAfter, 1);
			}
		}

		results[qi] = distinctPrimeCount + segTree.queryMax();
	}

	return results;
};

function getMaxValue(nums, queries) {
	let maxVal = 0;
	for (let i = 0; i < nums.length; i++) maxVal = Math.max(maxVal, nums[i]);
	for (let i = 0; i < queries.length; i++) maxVal = Math.max(maxVal, queries[i][1]);
	return maxVal;
}

function buildPrimeSieve(limit) {
	const isPrime = new Array(limit + 1).fill(true);
	if (limit >= 0) isPrime[0] = false;
	if (limit >= 1) isPrime[1] = false;
	for (let i = 2; i * i <= limit; i++) {
		if (!isPrime[i]) continue;
		for (let j = i * i; j <= limit; j += i) isPrime[j] = false;
	}
	return isPrime;
}

function ensureHeaps(value, minHeaps, maxHeaps) {
	if (!minHeaps[value]) {
		minHeaps[value] = new Heap((a, b) => a - b);
		maxHeaps[value] = new Heap((a, b) => b - a);
	}
}

function getValidMinIndex(value, minHeaps, nums) {
	const heap = minHeaps[value];
	if (!heap) return null;
	while (heap.size() > 0) {
		const idx = heap.peek();
		if (nums[idx] === value) return idx;
		heap.pop();
	}
	return null;
}

function getValidMaxIndex(value, maxHeaps, nums) {
	const heap = maxHeaps[value];
	if (!heap) return null;
	while (heap.size() > 0) {
		const idx = heap.peek();
		if (nums[idx] === value) return idx;
		heap.pop();
	}
	return null;
}

function applyInterval(segTree, minIdx, maxIdx, delta) {
	if (minIdx === null || maxIdx === null) return;
	if (minIdx < maxIdx) segTree.add(minIdx + 1, maxIdx, delta);
}

class Heap {
	constructor(compare) {
		this.data = [];
		this.compare = compare;
	}

	size() {
		return this.data.length;
	}

	peek() {
		return this.data[0];
	}

	push(value) {
		const data = this.data;
		data.push(value);
		let idx = data.length - 1;
		while (idx > 0) {
			const parent = (idx - 1) >> 1;
			if (this.compare(data[idx], data[parent]) >= 0) break;
			[data[idx], data[parent]] = [data[parent], data[idx]];
			idx = parent;
		}
	}

	pop() {
		const data = this.data;
		if (data.length === 0) return undefined;
		const top = data[0];
		const last = data.pop();
		if (data.length > 0) {
			data[0] = last;
			this._heapifyDown(0);
		}
		return top;
	}

	_heapifyDown(idx) {
		const data = this.data;
		const length = data.length;
		while (true) {
			let left = idx * 2 + 1;
			let right = idx * 2 + 2;
			let smallest = idx;
			if (left < length && this.compare(data[left], data[smallest]) < 0) smallest = left;
			if (right < length && this.compare(data[right], data[smallest]) < 0) smallest = right;
			if (smallest === idx) break;
			[data[idx], data[smallest]] = [data[smallest], data[idx]];
			idx = smallest;
		}
	}
}

class SegmentTree {
	constructor(n) {
		this.n = n;
		this.max = new Array(n * 4 + 4).fill(0);
		this.lazy = new Array(n * 4 + 4).fill(0);
	}

	add(l, r, val, idx = 1, lo = 1, hi = this.n) {
		if (this.n === 0 || l > hi || r < lo) return;
		if (l <= lo && hi <= r) {
			this.max[idx] += val;
			this.lazy[idx] += val;
			return;
		}
		this._pushDown(idx);
		const mid = (lo + hi) >> 1;
		if (l <= mid) this.add(l, r, val, idx * 2, lo, mid);
		if (r > mid) this.add(l, r, val, idx * 2 + 1, mid + 1, hi);
		this.max[idx] = Math.max(this.max[idx * 2], this.max[idx * 2 + 1]);
	}

	queryMax() {
		if (this.n === 0) return 0;
		return this.max[1];
	}

	_pushDown(idx) {
		const delta = this.lazy[idx];
		if (delta === 0) return;
		const left = idx * 2;
		const right = idx * 2 + 1;
		this.max[left] += delta;
		this.lazy[left] += delta;
		this.max[right] += delta;
		this.lazy[right] += delta;
		this.lazy[idx] = 0;
	}
}
