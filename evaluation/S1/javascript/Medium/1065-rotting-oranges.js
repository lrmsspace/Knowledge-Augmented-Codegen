// Source: https://leetcode.com/problems/rotting-oranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid where each cell can have one of three values:
//
//
// 	0 representing an empty cell,
// 	1 representing a fresh orange, or
// 	2 representing a rotten orange.
//
//
// Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
//
// Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.
//
// Example:
// Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
// Output: 4
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 10
// 	grid[i][j] is 0, 1, or 2.
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
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
var orangesRotting = function(grid) {
	const rows = grid.length;
	const cols = grid[0].length;
	const queue = [];
	let freshCount = 0;

	// Initialize the queue with all rotten oranges and count fresh oranges
	for (let r = 0; r < rows; r++) {
		for (let c = 0; c < cols; c++) {
			if (grid[r][c] === 2) {
				queue.push([r, c]);
			} else if (grid[r][c] === 1) {
				freshCount++;
			}
		}
	}

	if (freshCount === 0) return 0; // No fresh oranges to rot

	let minutes = 0;
	const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];

	while (queue.length > 0) {
		const size = queue.length;
		let rottedThisMinute = false;

		for (let i = 0; i < size; i++) {
			const [r, c] = queue.shift();

			for (const [dr, dc] of directions) {
				const newRow = r + dr;
				const newCol = c + dc;

				if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] === 1) {
					grid[newRow][newCol] = 2; // Mark as rotten
					queue.push([newRow, newCol]);
					freshCount--;
					rottedThisMinute = true;
				}
			}
		}

		if (rottedThisMinute) minutes++;
	}

 return freshCount === 0 ? minutes : -1;
};
