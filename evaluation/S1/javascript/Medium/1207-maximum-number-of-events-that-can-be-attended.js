// Source: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of events where events[i] = [startDayi, endDayi]. Every event i starts at startDayi and ends at endDayi.
//
// You can attend an event i at any day d where startDayi <= d <= endDayi. You can only attend one event at any time d.
//
// Return the maximum number of events you can attend.
//
// Example:
// Input: events = [[1,2],[2,3],[3,4]]
// Output: 3
// Explanation: You can attend all the three events.
// One way to attend them all is as shown.
// Attend the first event on day 1.
// Attend the second event on day 2.
// Attend the third event on day 3.
//
// Constraints:
// 1 <= events.length <= 105
// 	events[i].length == 2
// 	1 <= startDayi <= endDayi <= 105
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Suffix Array (string, array, merge-sort)
//   • When to use: Use when needing to efficiently query properties of all suffixes or substrings of a given text, especially for pattern matching or finding repeated structures. It is particularly useful for problems requiring lexicographical ordering of all suffixes.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices. It enables efficient string operations like pattern searching and finding longest common prefixes, typically constructed in O(N log N) time.
//   • Invariants: After k iterations, suffixes are sorted correctly up to a certain length (e.g., 2^k).; All suffixes of the original string are represented by their starting indices in the array.
//   • Tips: Append a unique sentinel character (e.g., '$') smaller than any other character to the string.; Utilize the LCP array, often built alongside, for advanced string queries and optimizations.
//   • Pitfalls: Naive sorting of suffixes by string comparison leads to an inefficient O(N^2 log N) complexity.; High memory usage for very long strings due to storing all suffixes implicitly or explicitly.
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} events
 * @return {number}
 */
var maxEvents = function(events) {
	events.sort((a, b) => a[0] - b[0]);

	const minHeap = new MinPriorityQueue({ priority: x => x });
	let eventIndex = 0;
	let attendedCount = 0;

	for (let day = 1; day <= 100000; day++) {
		while (!minHeap.isEmpty() && minHeap.front().element < day) {
			minHeap.dequeue();
		}

		while (eventIndex < events.length && events[eventIndex][0] === day) {
			minHeap.enqueue(events[eventIndex][1]);
			eventIndex++;
		}

		if (!minHeap.isEmpty()) {
			minHeap.dequeue();
			attendedCount++;
		}
	}

	return attendedCount;
};
