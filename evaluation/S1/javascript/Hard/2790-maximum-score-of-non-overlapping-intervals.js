// Source: https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals, where intervals[i] = [li, ri, weighti]. Interval i starts at position li and ends at ri, and has a weight of weighti. You can choose up to 4 non-overlapping intervals. The score of the chosen intervals is defined as the total sum of their weights.
//
// Return the lexicographically smallest array of at most 4 indices from intervals with maximum score, representing your choice of non-overlapping intervals.
//
// Two intervals are said to be non-overlapping if they do not share any points. In particular, intervals sharing a left or right boundary are considered overlapping.
//
// Example:
// Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
//
// Output: [2,3]
//
// Explanation:
//
// You can choose the intervals with indices 2, and 3 with respective weights of 5, and 3.
//
// Constraints:
// 1 <= intevals.length <= 5 * 104
// 	intervals[i].length == 3
// 	intervals[i] = [li, ri, weighti]
// 	1 <= li <= ri <= 109
// 	1 <= weighti <= 109
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} intervals
 * @return {number[]}
 */
var maximumWeight = function(intervals) {
	const K = 4;
	const n = intervals.length;
	if (n === 0) {
		return [];
	}

	const items = intervals.map((it, idx) => ({
		l: it[0],
		r: it[1],
		w: it[2],
		idx
	}));
	items.sort((a, b) => (a.r - b.r) || (a.l - b.l));

	const ends = items.map(item => item.r);
	const prevIdx = new Array(n);
	for (let i = 0; i < n; i++) {
		const l = items[i].l;
		let lo = 0;
		let hi = i - 1;
		let ans = -1;
		while (lo <= hi) {
			const mid = (lo + hi) >> 1;
			if (ends[mid] < l) {
				ans = mid;
				lo = mid + 1;
			} else {
				hi = mid - 1;
			}
		}
		prevIdx[i] = ans;
	}

	const dpW = Array.from({ length: K + 1 }, () => Array(n).fill(0));
	const dpL = Array.from({ length: K + 1 }, () => Array(n));

	for (let i = 0; i < n; i++) {
		dpL[0][i] = [];
	}

	const lexCompare = (a, b) => {
		const len = Math.min(a.length, b.length);
		for (let i = 0; i < len; i++) {
			if (a[i] !== b[i]) {
				return a[i] - b[i];
			}
		}
		return a.length - b.length;
	};

	const insertSorted = (list, val) => {
		const res = list.slice();
		let pos = res.length;
		for (let i = 0; i < res.length; i++) {
			if (res[i] > val) {
				pos = i;
				break;
			}
		}
		res.splice(pos, 0, val);
		return res;
	};

	for (let k = 1; k <= K; k++) {
		for (let i = 0; i < n; i++) {
			const skipW = i > 0 ? dpW[k][i - 1] : 0;
			const skipL = i > 0 ? dpL[k][i - 1] : [];

			const p = prevIdx[i];
			const baseW = p >= 0 ? dpW[k - 1][p] : 0;
			const baseL = p >= 0 ? dpL[k - 1][p] : [];
			const takeW = baseW + items[i].w;
			const takeL = insertSorted(baseL, items[i].idx);

			if (takeW > skipW) {
				dpW[k][i] = takeW;
				dpL[k][i] = takeL;
			} else if (takeW < skipW) {
				dpW[k][i] = skipW;
				dpL[k][i] = skipL;
			} else {
				if (lexCompare(takeL, skipL) < 0) {
					dpW[k][i] = takeW;
					dpL[k][i] = takeL;
				} else {
					dpW[k][i] = skipW;
					dpL[k][i] = skipL;
				}
			}
		}
	}

	return dpL[K][n - 1];
};
