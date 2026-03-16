// Source: https://leetcode.com/problems/shortest-path-in-binary-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
//
// A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
//
//
// 	All the visited cells of the path are 0.
// 	All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
//
//
// The length of a clear path is the number of visited cells of this path.
//
// Example:
// Input: grid = [[0,1],[1,0]]
// Output: 2
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 100
// 	grid[i][j] is 0 or 1
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - 0-1 BFS (graph, queue, 01-bfs, bfs)
//   • When to use: Use when finding shortest paths in a graph where edge weights are restricted to only 0 or 1. It efficiently determines minimum distances from a source to all reachable nodes, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds shortest paths from a single source in a graph where all edge weights are either 0 or 1. It achieves this in O(V + E) time complexity by using a deque to prioritize 0-weight edges.
//   • Invariants: All nodes in the deque have a distance value less than or equal to any node not yet processed.; Nodes added to the front of the deque (0-weight edges) always have a distance equal to the node they came from.
//   • Tips: Use a deque to maintain order: 0-weight edges go to front, 1-weight edges to back.; Initialize distances to infinity and source distance to 0.
//   • Pitfalls: Forgetting to update distances for 0-weight edges before adding to deque front.; Incorrectly handling visited states, leading to TLE or incorrect paths.
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
var shortestPathBinaryMatrix = function(grid) {
	const n = grid.length;
	if (grid[0][0] === 1 || grid[n - 1][n - 1] === 1) return -1;

	const directions = [
		[-1, -1], [-1, 0], [-1, 1],
		[0, -1],           [0, 1],
		[1, -1], [1, 0], [1, 1]
	];

	const queue = [[0, 0]];
	const visited = Array.from({ length: n }, () => Array(n).fill(false));
	visited[0][0] = true;
	let pathLength = 1;

	while (queue.length > 0) {
		const size = queue.length;
		for (let i = 0; i < size; i++) {
			const [x, y] = queue.shift();
			if (x === n - 1 && y === n - 1) return pathLength;

			for (const [dx, dy] of directions) {
				const newX = x + dx;
				const newY = y + dy;
				if (
					newX >= 0 && newX < n &&
					newY >= 0 && newY < n &&
					grid[newX][newY] === 0 &&
					!visited[newX][newY]
				) {
					queue.push([newX, newY]);
					visited[newX][newY] = true;
				}
			}
		}
		pathLength++;
	}

	return -1;
};
