// Source: https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, where each element is either 0, 1, or 2.
//
// A V-shaped diagonal segment is defined as:
//
//
// 	The segment starts with 1.
// 	The subsequent elements follow this infinite sequence: 2, 0, 2, 0, ....
// 	The segment:
// 	
// 		Starts along a diagonal direction (top-left to bottom-right, bottom-right to top-left, top-right to bottom-left, or bottom-left to top-right).
// 		Continues the sequence in the same diagonal direction.
// 		Makes at most one clockwise 90-degree turn to another diagonal direction while maintaining the sequence.
// 	
// 	
//
//
// Return the length of the longest V-shaped diagonal segment. If no valid segment exists, return 0.
//
// Example:
// Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
//
// Output: 5
//
// Explanation:
//
//
//
// The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: (0,2) → (1,3) → (2,4), takes a 90-degree clockwise turn at (2,4), and continues as (3,3) → (4,2).
//
// Constraints:
// n == grid.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	grid[i][j] is either 0, 1 or 2.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} grid
 * @return {number}
 */
var lenOfVDiagonal = function(grid) {
	const n = grid.length;
	const m = grid[0].length;
	const size = n * m;

	const start2 = [new Int32Array(size), new Int32Array(size), new Int32Array(size), new Int32Array(size)];
	const start0 = [new Int32Array(size), new Int32Array(size), new Int32Array(size), new Int32Array(size)];
	const end2 = [new Int32Array(size), new Int32Array(size), new Int32Array(size), new Int32Array(size)];
	const end0 = [new Int32Array(size), new Int32Array(size), new Int32Array(size), new Int32Array(size)];

	// Direction 0: down-right (1, 1)
	for (let i = n - 1; i >= 0; i--) {
		const row = grid[i];
		for (let j = m - 1; j >= 0; j--) {
			const idx = i * m + j;
			const val = row[j];
			const ni = i + 1;
			const nj = j + 1;
			const nextIdx = (ni < n && nj < m) ? (ni * m + nj) : -1;
			if (val === 2) start2[0][idx] = 1 + (nextIdx >= 0 ? start0[0][nextIdx] : 0);
			if (val === 0) start0[0][idx] = 1 + (nextIdx >= 0 ? start2[0][nextIdx] : 0);
		}
	}

	// Direction 1: down-left (1, -1)
	for (let i = n - 1; i >= 0; i--) {
		const row = grid[i];
		for (let j = 0; j < m; j++) {
			const idx = i * m + j;
			const val = row[j];
			const ni = i + 1;
			const nj = j - 1;
			const nextIdx = (ni < n && nj >= 0) ? (ni * m + nj) : -1;
			if (val === 2) start2[1][idx] = 1 + (nextIdx >= 0 ? start0[1][nextIdx] : 0);
			if (val === 0) start0[1][idx] = 1 + (nextIdx >= 0 ? start2[1][nextIdx] : 0);
		}
	}

	// Direction 2: up-left (-1, -1)
	for (let i = 0; i < n; i++) {
		const row = grid[i];
		for (let j = 0; j < m; j++) {
			const idx = i * m + j;
			const val = row[j];
			const ni = i - 1;
			const nj = j - 1;
			const nextIdx = (ni >= 0 && nj >= 0) ? (ni * m + nj) : -1;
			if (val === 2) start2[2][idx] = 1 + (nextIdx >= 0 ? start0[2][nextIdx] : 0);
			if (val === 0) start0[2][idx] = 1 + (nextIdx >= 0 ? start2[2][nextIdx] : 0);
		}
	}

	// Direction 3: up-right (-1, 1)
	for (let i = 0; i < n; i++) {
		const row = grid[i];
		for (let j = m - 1; j >= 0; j--) {
			const idx = i * m + j;
			const val = row[j];
			const ni = i - 1;
			const nj = j + 1;
			const nextIdx = (ni >= 0 && nj < m) ? (ni * m + nj) : -1;
			if (val === 2) start2[3][idx] = 1 + (nextIdx >= 0 ? start0[3][nextIdx] : 0);
			if (val === 0) start0[3][idx] = 1 + (nextIdx >= 0 ? start2[3][nextIdx] : 0);
		}
	}

	// End DP for each direction
	// Direction 0: down-right (1, 1)
	for (let i = 0; i < n; i++) {
		const row = grid[i];
		for (let j = 0; j < m; j++) {
			const idx = i * m + j;
			const val = row[j];
			if (val === 2) {
				if (i > 0 && j > 0) {
					const prevIdx = (i - 1) * m + (j - 1);
					const prevEnd0 = end0[0][prevIdx];
					const prevEnd1 = grid[i - 1][j - 1] === 1 ? 1 : 0;
					const maxPrev = prevEnd0 > prevEnd1 ? prevEnd0 : prevEnd1;
					end2[0][idx] = maxPrev > 0 ? maxPrev + 1 : 0;
				}
			} else if (val === 0) {
				if (i > 0 && j > 0) {
					const prevIdx = (i - 1) * m + (j - 1);
					const prevEnd2 = end2[0][prevIdx];
					end0[0][idx] = prevEnd2 > 0 ? prevEnd2 + 1 : 0;
				}
			}
		}
	}

	// Direction 1: down-left (1, -1)
	for (let i = 0; i < n; i++) {
		const row = grid[i];
		for (let j = m - 1; j >= 0; j--) {
			const idx = i * m + j;
			const val = row[j];
			if (val === 2) {
				if (i > 0 && j + 1 < m) {
					const prevIdx = (i - 1) * m + (j + 1);
					const prevEnd0 = end0[1][prevIdx];
					const prevEnd1 = grid[i - 1][j + 1] === 1 ? 1 : 0;
					const maxPrev = prevEnd0 > prevEnd1 ? prevEnd0 : prevEnd1;
					end2[1][idx] = maxPrev > 0 ? maxPrev + 1 : 0;
				}
			} else if (val === 0) {
				if (i > 0 && j + 1 < m) {
					const prevIdx = (i - 1) * m + (j + 1);
					const prevEnd2 = end2[1][prevIdx];
					end0[1][idx] = prevEnd2 > 0 ? prevEnd2 + 1 : 0;
				}
			}
		}
	}

	// Direction 2: up-left (-1, -1)
	for (let i = n - 1; i >= 0; i--) {
		const row = grid[i];
		for (let j = m - 1; j >= 0; j--) {
			const idx = i * m + j;
			const val = row[j];
			if (val === 2) {
				if (i + 1 < n && j + 1 < m) {
					const prevIdx = (i + 1) * m + (j + 1);
					const prevEnd0 = end0[2][prevIdx];
					const prevEnd1 = grid[i + 1][j + 1] === 1 ? 1 : 0;
					const maxPrev = prevEnd0 > prevEnd1 ? prevEnd0 : prevEnd1;
					end2[2][idx] = maxPrev > 0 ? maxPrev + 1 : 0;
				}
			} else if (val === 0) {
				if (i + 1 < n && j + 1 < m) {
					const prevIdx = (i + 1) * m + (j + 1);
					const prevEnd2 = end2[2][prevIdx];
					end0[2][idx] = prevEnd2 > 0 ? prevEnd2 + 1 : 0;
				}
			}
		}
	}

	// Direction 3: up-right (-1, 1)
	for (let i = n - 1; i >= 0; i--) {
		const row = grid[i];
		for (let j = 0; j < m; j++) {
			const idx = i * m + j;
			const val = row[j];
			if (val === 2) {
				if (i + 1 < n && j > 0) {
					const prevIdx = (i + 1) * m + (j - 1);
					const prevEnd0 = end0[3][prevIdx];
					const prevEnd1 = grid[i + 1][j - 1] === 1 ? 1 : 0;
					const maxPrev = prevEnd0 > prevEnd1 ? prevEnd0 : prevEnd1;
					end2[3][idx] = maxPrev > 0 ? maxPrev + 1 : 0;
				}
			} else if (val === 0) {
				if (i + 1 < n && j > 0) {
					const prevIdx = (i + 1) * m + (j - 1);
					const prevEnd2 = end2[3][prevIdx];
					end0[3][idx] = prevEnd2 > 0 ? prevEnd2 + 1 : 0;
				}
			}
		}
	}

	const dr = [1, 1, -1, -1];
	const dc = [1, -1, -1, 1];
	let maxLen = 0;

	for (let i = 0; i < n; i++) {
		const row = grid[i];
		for (let j = 0; j < m; j++) {
			if (row[j] !== 1) continue;
			const idx = i * m + j;
			maxLen = maxLen < 1 ? 1 : maxLen;
			for (let d = 0; d < 4; d++) {
				const ni = i + dr[d];
				const nj = j + dc[d];
				const len = (ni >= 0 && ni < n && nj >= 0 && nj < m)
					? 1 + start2[d][ni * m + nj]
					: 1;
				if (len > maxLen) maxLen = len;
			}
		}
	}

	for (let i = 0; i < n; i++) {
		const row = grid[i];
		for (let j = 0; j < m; j++) {
			const idx = i * m + j;
			for (let d1 = 0; d1 < 4; d1++) {
				const d2 = (d1 + 1) % 4;
				const ni = i + dr[d2];
				const nj = j + dc[d2];
				const cont2 = (ni >= 0 && ni < n && nj >= 0 && nj < m) ? start2[d2][ni * m + nj] : 0;
				const cont0 = (ni >= 0 && ni < n && nj >= 0 && nj < m) ? start0[d2][ni * m + nj] : 0;

				const base1 = row[j] === 1 ? 1 : 0;
				const base0 = end0[d1][idx];
				const base2 = end2[d1][idx];

				const baseA = base0 > base1 ? base0 : base1;
				if (baseA > 0) {
					const total = baseA + cont2;
					if (total > maxLen) maxLen = total;
				}
				if (base2 > 0) {
					const total = base2 + cont0;
					if (total > maxLen) maxLen = total;
				}
			}
		}
	}

	return maxLen;
};
