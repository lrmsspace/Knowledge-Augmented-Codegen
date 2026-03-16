// Source: https://leetcode.com/problems/disconnect-path-in-a-binary-matrix-by-at-most-one-flip/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed m x n binary matrix grid. You can move from a cell (row, col) to any of the cells (row + 1, col) or (row, col + 1) that has the value 1. The matrix is disconnected if there is no path from (0, 0) to (m - 1, n - 1).
//
// You can flip the value of at most one (possibly none) cell. You cannot flip the cells (0, 0) and (m - 1, n - 1).
//
// Return true if it is possible to make the matrix disconnect or false otherwise.
//
// Note that flipping a cell changes its value from 0 to 1 or from 1 to 0.
//
// Example:
// Input: grid = [[1,1,1],[1,0,0],[1,1,1]]
// Output: true
// Explanation: We can change the cell shown in the diagram above. There is no path from (0, 0) to (2, 2) in the resulting grid.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	grid[i][j] is either 0 or 1.
// 	grid[0][0] == grid[m - 1][n - 1] == 1
//
// Helpful references (internal KB):
// - Maximum flow - Dinic's algorithm (graph, bfs, dfs)
//   • When to use: Use Dinic's algorithm to find the maximum flow from a source to a sink in a flow network. It is efficient for dense graphs and particularly optimized for unit capacity networks.
//   • Idea: Dinic's algorithm computes the maximum flow by repeatedly constructing a layered network using BFS and then finding a blocking flow in this layered network using DFS. It offers a general time complexity of O(V^2 * E) and O(E * sqrt(V)) for unit capacity networks.
//   • Invariants: The flow on any edge (u, v) never exceeds its original capacity.; For any vertex v (excluding source and sink), the sum of flow into v equals the sum of flow out of v.
//   • Tips: Use BFS to construct the layered graph, assigning levels to nodes from the source.; Employ DFS to find augmenting paths within the layered graph, only traversing edges to higher levels.
//   • Pitfalls: Forgetting to update residual capacities for reverse edges, which can prevent finding valid augmenting paths.; Incorrectly constructing the layered graph or level assignments during the BFS phase.
// - Edge connectivity / Vertex connectivity (graph, enumeration)
//   • When to use: Used to quantify a graph's resilience by finding the minimum number of edges or vertices whose removal disconnects it, or separates a specific pair of nodes.
//   • Idea: Edge connectivity is the minimum edges to disconnect a graph, while vertex connectivity is for vertices. Both are often computed using max-flow min-cut theorems, typically in polynomial time.
//   • Invariants: The flow through any edge in the network does not exceed its capacity.; For any intermediate vertex (not source or sink), the total incoming flow equals the total outgoing flow.
//   • Tips: Edge connectivity between two specific vertices can be found using a max-flow min-cut algorithm.; To find global edge connectivity, iterate over all pairs of vertices or use specialized algorithms.
//   • Pitfalls: Confusing edge connectivity (edges) with vertex connectivity (vertices) requirements.; Incorrectly applying max-flow for global connectivity without considering all relevant source-sink pairs.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} grid
 * @return {boolean}
 */
var isPossibleToCutPath = function(grid) {
	var m = grid.length;
	var n = grid[0].length;

	var startIdx = 0;
	var endIdx = m * n - 1;

	var findAndErasePath = function() {
		var total = m * n;
		var prev = new Array(total).fill(-1);
		var visited = new Array(total).fill(false);
		var stack = [0];
		visited[0] = true;

		while (stack.length) {
			var idx = stack.pop();
			if (idx === endIdx) {
				break;
			}
			var r = Math.floor(idx / n);
			var c = idx % n;

			var downR = r + 1;
			var rightC = c + 1;

			if (downR < m && grid[downR][c] === 1) {
				var dIdx = downR * n + c;
				if (!visited[dIdx]) {
					visited[dIdx] = true;
					prev[dIdx] = idx;
					stack.push(dIdx);
				}
			}
			if (rightC < n && grid[r][rightC] === 1) {
				var rIdx = r * n + rightC;
				if (!visited[rIdx]) {
					visited[rIdx] = true;
					prev[rIdx] = idx;
					stack.push(rIdx);
				}
			}
		}

		if (!visited[endIdx]) {
			return false;
		}

		// Erase one internal path to check if another disjoint path exists.
		var cur = endIdx;
		while (cur !== startIdx && cur !== -1) {
			if (cur !== endIdx && cur !== startIdx) {
				var rr = Math.floor(cur / n);
				var cc = cur % n;
				grid[rr][cc] = 0;
			}
			cur = prev[cur];
		}
		return true;
	};

	var hasPath = function() {
		var total = m * n;
		var visited = new Array(total).fill(false);
		var stack = [0];
		visited[0] = true;

		while (stack.length) {
			var idx = stack.pop();
			if (idx === endIdx) {
				return true;
			}
			var r = Math.floor(idx / n);
			var c = idx % n;

			var downR = r + 1;
			var rightC = c + 1;

			if (downR < m && grid[downR][c] === 1) {
				var dIdx = downR * n + c;
				if (!visited[dIdx]) {
					visited[dIdx] = true;
					stack.push(dIdx);
				}
			}
			if (rightC < n && grid[r][rightC] === 1) {
				var rIdx = r * n + rightC;
				if (!visited[rIdx]) {
					visited[rIdx] = true;
					stack.push(rIdx);
				}
			}
		}
		return false;
	};

	if (!findAndErasePath()) {
		return true;
	}

	return !hasPath();
};
