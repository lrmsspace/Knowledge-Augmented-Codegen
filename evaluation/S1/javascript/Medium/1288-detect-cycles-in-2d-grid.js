// Source: https://leetcode.com/problems/detect-cycles-in-2d-grid/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.
//
// A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.
//
// Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.
//
// Return true if any cycle of the same value exists in grid, otherwise, return false.
//
// Example:
// Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
// Output: true
// Explanation: There are two valid cycles shown in different colors in the image below:
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 500
// 	grid consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Depth-first search (graph, array, dfs, biconnected-components)
//   • When to use: Use when exploring all reachable nodes from a starting point, finding paths, or detecting cycles in a graph. It's suitable for problems requiring a deep, exhaustive search.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically running in O(V + E) time for graphs represented with adjacency lists.
//   • Invariants: Every node `v` is visited exactly once.; When `dfs(G, u, v)` is called, `v` is unvisited and `u` is its immediate predecessor in the current path.
//   • Tips: Maintain a visited set/array to avoid revisiting nodes and infinite loops.; Pass the parent node in recursive calls to correctly identify back-edges for cycle detection.
//   • Pitfalls: Failing to mark nodes as visited can lead to infinite loops in cyclic graphs.; Deep recursion can cause stack overflow errors on large graphs; use an iterative approach if needed.
// - Checking a graph for acyclicity and finding a cycle in O(M) (graph, array, dfs)
//   • When to use: Use when needing to determine if a graph contains any cycles or to identify one such cycle. It is applicable to both directed and undirected graphs.
//   • Idea: This algorithm uses Depth First Search to detect cycles in a graph by tracking visited states of nodes during traversal. It runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently on the DFS recursion stack are marked as 'gray' (or equivalent).; All nodes fully explored and not part of the current path are marked as 'black' (or equivalent).
//   • Tips: For directed graphs, use a three-color scheme (white, gray, black) to distinguish states.; For undirected graphs, a simple visited array and checking against the immediate parent is sufficient.
//   • Pitfalls: Incorrectly handling the parent edge in undirected graphs can lead to false cycle detections.; Failing to distinguish between nodes currently in the recursion stack (gray) and fully processed nodes (black) in directed graphs.
// - Finding the Eulerian path in O(M) (graph, eulerian-circuit, dfs)
//   • When to use: Use when you need to find a path or cycle that traverses every edge exactly once in a given graph. It's applicable when specific vertex degree conditions are met for path or cycle existence.
//   • Idea: This algorithm constructs an Eulerian path or cycle by first verifying vertex degree conditions and graph connectivity, then performing a recursive DFS-like traversal to build the path. It achieves a time complexity of O(M), where M is the number of edges.
//   • Invariants: Every edge in the constructed path has been traversed exactly once.; All edges incident to the current vertex have been explored or are part of the remaining graph.
//   • Tips: Verify graph connectivity, ignoring isolated vertices.; For an Eulerian path, ensure exactly two vertices have odd degrees.
//   • Pitfalls: Failing to check graph connectivity before starting.; Incorrectly counting odd degree vertices for path vs. cycle.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {character[][]} grid
 * @return {boolean}
 */
var containsCycle = function(grid) {
	const m = grid.length;
	const n = grid[0].length;
	const visited = new Array(m).fill(0).map(() => new Array(n).fill(false));

	const directions = [
		[-1, 0], // up
		[1, 0],  // down
		[0, -1], // left
		[0, 1],  // right
	];

	const dfs = (x, y, parentX, parentY) => {
		if (visited[x][y]) {
			return true;
		}

		visited[x][y] = true;

		for (const [dx, dy] of directions) {
			const newX = x + dx;
			const newY = y + dy;

			if (newX < 0 || newX >= m || newY < 0 || newY >= n || grid[newX][newY] !== grid[x][y]) {
				continue;
			}

			if (newX === parentX && newY === parentY) {
				continue;
			}

			if (dfs(newX, newY, x, y)) {
				return true;
			}
		}

		return false;
	};

	for (let i = 0; i < m; i++) {
		for (let j = 0; j < n; j++) {
			if (!visited[i][j] && dfs(i, j, -1, -1)) {
				return true;
			}
		}
	}

	return false;
};
