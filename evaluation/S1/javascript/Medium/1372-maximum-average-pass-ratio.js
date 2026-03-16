// Source: https://leetcode.com/problems/maximum-average-pass-ratio/   |   Difficulty: Medium
//
// Problem Description:
// There is a school that has classes of students and each class will be having a final exam. You are given a 2D integer array classes, where classes[i] = [passi, totali]. You know beforehand that in the ith class, there are totali total students, but only passi number of students will pass the exam.
//
// You are also given an integer extraStudents. There are another extraStudents brilliant students that are guaranteed to pass the exam of any class they are assigned to. You want to assign each of the extraStudents students to a class in a way that maximizes the average pass ratio across all the classes.
//
// The pass ratio of a class is equal to the number of students of the class that will pass the exam divided by the total number of students of the class. The average pass ratio is the sum of pass ratios of all the classes divided by the number of the classes.
//
// Return the maximum possible average pass ratio after assigning the extraStudents students. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
// Output: 0.78333
// Explanation: You can assign the two extra students to the first class. The average pass ratio will be equal to (3/4 + 3/5 + 2/2) / 3 = 0.78333.
//
// Constraints:
// 1 <= classes.length <= 105
// 	classes[i].length == 2
// 	1 <= passi <= totali <= 105
// 	1 <= extraStudents <= 105
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Priority Queues (heap, stack, heap-select)
//   • When to use: Use when you need to efficiently retrieve the element with the highest (or lowest) priority from a collection, especially when elements are added or removed frequently.
//   • Idea: A priority queue is a data structure that allows efficient retrieval of the element with the highest or lowest priority, and efficient insertion of new elements. Operations typically run in logarithmic time, O(log N).
//   • Invariants: The priority queue maintains the heap property: parent nodes are always greater than/equal to (or less than/equal to) their children.; For a K-selection problem, the priority queue contains at most K elements, representing the K largest/smallest seen so far.
//   • Tips: Use a min-priority queue to find the K largest elements by keeping at most K elements.; Use a max-priority queue to find the K smallest elements by keeping at most K elements.
//   • Pitfalls: Confusing min-priority queue with max-priority queue for the desired extremum.; Inefficient underlying implementation leading to O(N) operations instead of O(log N).
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} classes
 * @param {number} extraStudents
 * @return {number}
 */
var maxAverageRatio = function(classes, extraStudents) {
	// helper: improvement of adding one passing student to class (p/t)
	const gain = (p, t) => (p + 1) / (t + 1) - p / t;

	// simple max-heap by gain
	class MaxHeap {
		constructor() { this.data = []; }
		size() { return this.data.length; }
		push(x) { this.data.push(x); this._siftUp(this.data.length - 1); }
		pop() {
			if (this.data.length === 0) return null;
			const top = this.data[0];
			const last = this.data.pop();
			if (this.data.length) {
				this.data[0] = last;
				this._siftDown(0);
			}
			return top;
		}
		_siftUp(i) {
			const d = this.data;
			while (i > 0) {
				const p = (i - 1) >> 1;
				if (d[p].gain >= d[i].gain) break;
				[d[p], d[i]] = [d[i], d[p]];
				i = p;
			}
		}
		_siftDown(i) {
			const d = this.data; const n = d.length;
			while (true) {
				let l = i * 2 + 1;
				if (l >= n) break;
				let r = l + 1;
				let largest = l;
				if (r < n && d[r].gain > d[l].gain) largest = r;
				if (d[largest].gain <= d[i].gain) break;
				[d[largest], d[i]] = [d[i], d[largest]];
				i = largest;
			}
		}
	}

	const heap = new MaxHeap();
	for (let i = 0; i < classes.length; i++) {
		const p = classes[i][0], t = classes[i][1];
		heap.push({ p: p, t: t, gain: gain(p, t) });
	}

	while (extraStudents > 0) {
		const top = heap.pop();
		// assign one brilliant student
		top.p += 1;
		top.t += 1;
		top.gain = gain(top.p, top.t);
		heap.push(top);
		extraStudents--;
	}

	let sum = 0;
	while (heap.size()) {
		const it = heap.pop();
		sum += it.p / it.t;
	}
	return sum / classes.length;
};
