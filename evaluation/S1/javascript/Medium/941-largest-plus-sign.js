// Source: https://leetcode.com/problems/largest-plus-sign/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. You have an n x n binary grid grid with all values initially 1's except for some indices given in the array mines. The ith element of the array mines is defined as mines[i] = [xi, yi] where grid[xi][yi] == 0.
//
// Return the order of the largest axis-aligned plus sign of 1's contained in grid. If there is none, return 0.
//
// An axis-aligned plus sign of 1's of order k has some center grid[r][c] == 1 along with four arms of length k - 1 going up, down, left, and right, and made of 1's. Note that there could be 0's or 1's beyond the arms of the plus sign, only the relevant area of the plus sign is checked for 1's.
//
// Example:
// Input: n = 5, mines = [[4,2]]
// Output: 2
// Explanation: In the above grid, the largest plus sign can only be of order 2. One of them is shown.
//
// Constraints:
// 1 <= n <= 500
// 	1 <= mines.length <= 5000
// 	0 <= xi, yi < n
// 	All the pairs (xi, yi) are unique.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} mines
 * @return {number}
 */
var orderOfLargestPlusSign = function(n, mines) {
	const grid = Array.from({ length: n }, () => Array(n).fill(1));
	for (const [x, y] of mines) {
		grid[x][y] = 0; // Mark mines on the grid
	}

	const left = Array.from({ length: n }, () => Array(n).fill(0));
	const right = Array.from({ length: n }, () => Array(n).fill(0));
	const up = Array.from({ length: n }, () => Array(n).fill(0));
	const down = Array.from({ length: n }, () => Array(n).fill(0));

	// Fill left and up arrays
	for (let i = 0; i < n; i++) {
		for (let j = 0; j < n; j++) {
			if (grid[i][j] === 1) {
				left[i][j] = (j > 0 ? left[i][j - 1] : 0) + 1;
				up[i][j] = (i > 0 ? up[i - 1][j] : 0) + 1;
			}
		}
	}

	// Fill right and down arrays
	for (let i = n - 1; i >= 0; i--) {
		for (let j = n - 1; j >= 0; j--) {
			if (grid[i][j] === 1) {
				right[i][j] = (j < n - 1 ? right[i][j + 1] : 0) + 1;
				down[i][j] = (i < n - 1 ? down[i + 1][j] : 0) + 1;
			}
		}
	}

	let maxOrder = 0;
	for (let i = 0; i < n; i++) {
		for (let j = 0; j < n; j++) {
			if (grid[i][j] === 1) {
				const order = Math.min(left[i][j], right[i][j], up[i][j], down[i][j]);
				maxOrder = Math.max(maxOrder, order);
			}
		}
	}

	return maxOrder;
};
