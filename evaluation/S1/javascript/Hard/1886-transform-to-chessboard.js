// Source: https://leetcode.com/problems/transform-to-chessboard/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n binary grid board. In each move, you can swap any two rows with each other, or any two columns with each other.
//
// Return the minimum number of moves to transform the board into a chessboard board. If the task is impossible, return -1.
//
// A chessboard board is a board where no 0's and no 1's are 4-directionally adjacent.
//
// Example:
// Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
// Output: 2
// Explanation: One potential sequence of moves is shown.
// The first move swaps the first and second column.
// The second move swaps the second and third row.
//
// Constraints:
// n == board.length
//  n == board[i].length
//  2 <= n <= 30
//  board[i][j] is either 0 or 1.
//
// Helpful references (internal KB):
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} board
 * @return {number}
 */
var movesToChessboard = function(board) {
	const n = board.length;

	for (let i = 0; i < n; i += 1) {
		for (let j = 0; j < n; j += 1) {
			if ((board[0][0] ^ board[i][0] ^ board[0][j] ^ board[i][j]) !== 0) {
				return -1;
			}
		}
	}

	let rowSum = 0;
	let colSum = 0;
	let rowSwap = 0;
	let colSwap = 0;

	for (let i = 0; i < n; i += 1) {
		rowSum += board[0][i];
		colSum += board[i][0];
		if (board[i][0] === (i % 2)) {
			rowSwap += 1;
		}
		if (board[0][i] === (i % 2)) {
			colSwap += 1;
		}
	}

	const minOnes = Math.floor(n / 2);
	const maxOnes = Math.ceil(n / 2);
	if (rowSum < minOnes || rowSum > maxOnes) {
		return -1;
	}
	if (colSum < minOnes || colSum > maxOnes) {
		return -1;
	}

	if (n % 2 === 1) {
		if (rowSwap % 2 === 1) {
			rowSwap = n - rowSwap;
		}
		if (colSwap % 2 === 1) {
			colSwap = n - colSwap;
		}
	} else {
		rowSwap = Math.min(rowSwap, n - rowSwap);
		colSwap = Math.min(colSwap, n - colSwap);
	}

	return (rowSwap + colSwap) / 2;
};
