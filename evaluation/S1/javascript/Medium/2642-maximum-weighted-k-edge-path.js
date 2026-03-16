// Source: https://leetcode.com/problems/maximum-weighted-k-edge-path/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n and a Directed Acyclic Graph (DAG) with n nodes labeled from 0 to n - 1. This is represented by a 2D array edges, where edges[i] = [ui, vi, wi] indicates a directed edge from node ui to vi with weight wi.
//
// You are also given two integers, k and t.
//
// Your task is to determine the maximum possible sum of edge weights for any path in the graph such that:
//
//
// 	The path contains exactly k edges.
// 	The total sum of edge weights in the path is strictly less than t.
//
//
// Return the maximum possible sum of weights for such a path. If no such path exists, return -1.
//
// Example:
// Input: n = 3, edges = [[0,1,1],[1,2,2]], k = 2, t = 4
//
// Output: 3
//
// Explanation:
//
//
//
//
// 	The only path with k = 2 edges is 0 -> 1 -> 2 with weight 1 + 2 = 3 < t.
// 	Thus, the maximum possible sum of weights less than t is 3.
//
// Constraints:
// 1 <= n <= 300
// 	0 <= edges.length <= 300
// 	edges[i] = [ui, vi, wi]
// 	0 <= ui, vi < n
// 	ui != vi
// 	1 <= wi <= 10
// 	0 <= k <= 300
// 	1 <= t <= 600
// 	The input graph is guaranteed to be a DAG.
// 	There are no duplicate edges.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number} k
 * @param {number} t
 * @return {number}
 */
var maxWeight = function(n, edges, k, t) {
	if (k === 0) {
		return 0;
	}

	let prev = Array.from({ length: n }, () => new Uint8Array(t));
	for (let i = 0; i < n; i++) {
		prev[i][0] = 1;
	}

	for (let step = 1; step <= k; step++) {
		const next = Array.from({ length: n }, () => new Uint8Array(t));

		for (let i = 0; i < edges.length; i++) {
			const u = edges[i][0];
			const v = edges[i][1];
			const w = edges[i][2];
			const src = prev[u];
			const dst = next[v];

			for (let s = 0; s + w < t; s++) {
				if (src[s]) {
					dst[s + w] = 1;
				}
			}
		}

		prev = next;
	}

	for (let s = t - 1; s >= 0; s--) {
		for (let node = 0; node < n; node++) {
			if (prev[node][s]) {
				return s;
			}
		}
	}

	return -1;
};
