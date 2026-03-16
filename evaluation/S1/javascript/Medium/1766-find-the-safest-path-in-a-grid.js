// Source: https://leetcode.com/problems/find-the-safest-path-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:
//
//
// 	A cell containing a thief if grid[r][c] = 1
// 	An empty cell if grid[r][c] = 0
//
//
// You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in the grid, including cells containing thieves.
//
// The safeness factor of a path on the grid is defined as the minimum manhattan distance from any cell in the path to any thief in the grid.
//
// Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).
//
// An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.
//
// The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where |val| denotes the absolute value of val.
//
// Example:
// Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
// Output: 0
// Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves in cells (0, 0) and (n - 1, n - 1).
//
// Constraints:
// 1 <= grid.length == n <= 400
// 	grid[i].length == n
// 	grid[i][j] is either 0 or 1.
// 	There is at least one thief in the grid.
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Flows with demands (graph, binary-search-answer)
//   • When to use: Use when a problem involves finding a flow in a network where edges have both lower and upper capacity bounds, or nodes have supply/demand requirements, and an optimal value needs to be found.
//   • Idea: This technique transforms a network with lower and upper capacity bounds on edges (or node demands) into a standard max-flow problem. It often involves adding a new source and sink to handle demands, and then binary searching on the answer if an optimal value is sought, typically with O(MaxFlow * log(Range)) complexity.
//   • Invariants: The total flow out of the super source equals the total demand that needs to be satisfied.; For any node, the sum of incoming flow minus outgoing flow equals its net demand (0 for internal nodes in a circulation).
//   • Tips: Convert lower bounds to demands by adjusting capacities and adding a super source/sink.; A feasible flow exists if the max flow in the transformed network equals the total demand.
//   • Pitfalls: Incorrectly calculating residual capacities after demand satisfaction.; Forgetting to add a super source/sink for handling demands.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
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
var maximumSafenessFactor = function(grid) {
	const n = grid.length;
	const total = n * n;
	const dist = Array.from({ length: n }, () => Array(n).fill(-1));
	const queue = new Array(total);
	let head = 0;
	let tail = 0;

	for (let r = 0; r < n; r++) {
		for (let c = 0; c < n; c++) {
			if (grid[r][c] === 1) {
				dist[r][c] = 0;
				queue[tail++] = r * n + c;
			}
		}
	}

	const dr = [1, -1, 0, 0];
	const dc = [0, 0, 1, -1];

	// Multi-source BFS for distance to nearest thief.
	while (head < tail) {
		const idx = queue[head++];
		const r = Math.floor(idx / n);
		const c = idx % n;
		const base = dist[r][c];
		for (let k = 0; k < 4; k++) {
			const nr = r + dr[k];
			const nc = c + dc[k];
			if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
			if (dist[nr][nc] !== -1) continue;
			dist[nr][nc] = base + 1;
			queue[tail++] = nr * n + nc;
		}
	}

	class MaxHeap {
		constructor() {
			this.data = [];
		}
		size() {
			return this.data.length;
		}
		push(node) {
			this.data.push(node);
			this._siftUp(this.data.length - 1);
		}
		pop() {
			if (this.data.length === 0) return null;
			const top = this.data[0];
			const last = this.data.pop();
			if (this.data.length > 0) {
				this.data[0] = last;
				this._siftDown(0);
			}
			return top;
		}
		_siftUp(i) {
			while (i > 0) {
				const p = (i - 1) >> 1;
				if (this.data[p][0] >= this.data[i][0]) break;
				const tmp = this.data[p];
				this.data[p] = this.data[i];
				this.data[i] = tmp;
				i = p;
			}
		}
		_siftDown(i) {
			const n = this.data.length;
			while (true) {
				let best = i;
				const l = i * 2 + 1;
				const r = l + 1;
				if (l < n && this.data[l][0] > this.data[best][0]) best = l;
				if (r < n && this.data[r][0] > this.data[best][0]) best = r;
				if (best === i) break;
				const tmp = this.data[best];
				this.data[best] = this.data[i];
				this.data[i] = tmp;
				i = best;
			}
		}
	}

	// Maximize the minimum distance along the path (max-min path).
	const best = Array.from({ length: n }, () => Array(n).fill(-1));
	const heap = new MaxHeap();
	best[0][0] = dist[0][0];
	heap.push([best[0][0], 0, 0]);

	while (heap.size() > 0) {
		const [score, r, c] = heap.pop();
		if (r === n - 1 && c === n - 1) return score;
		if (score < best[r][c]) continue;
		for (let k = 0; k < 4; k++) {
			const nr = r + dr[k];
			const nc = c + dc[k];
			if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
			const nextScore = Math.min(score, dist[nr][nc]);
			if (nextScore > best[nr][nc]) {
				best[nr][nc] = nextScore;
				heap.push([nextScore, nr, nc]);
			}
		}
	}

	return 0;
};
