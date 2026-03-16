// Source: https://leetcode.com/problems/maximum-points-after-collecting-coins-from-all-nodes/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree rooted at node 0 with n nodes labeled from 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree. You are also given a 0-indexed array coins of size n where coins[i] indicates the number of coins in the vertex i, and an integer k.
//
// Starting from the root, you have to collect all the coins such that the coins at a node can only be collected if the coins of its ancestors have been already collected.
//
// Coins at nodei can be collected in one of the following ways:
//
//
// 	Collect all the coins, but you will get coins[i] - k points. If coins[i] - k is negative then you will lose abs(coins[i] - k) points.
// 	Collect all the coins, but you will get floor(coins[i] / 2) points. If this way is used, then for all the nodej present in the subtree of nodei, coins[j] will get reduced to floor(coins[j] / 2).
//
//
// Return the maximum points you can get after collecting the coins from all the tree nodes.
//
// Example:
// Input: edges = [[0,1],[1,2],[2,3]], coins = [10,10,3,3], k = 5
// Output: 11                        
// Explanation: 
// Collect all the coins from node 0 using the first way. Total points = 10 - 5 = 5.
// Collect all the coins from node 1 using the first way. Total points = 5 + (10 - 5) = 10.
// Collect all the coins from node 2 using the second way so coins left at node 3 will be floor(3 / 2) = 1. Total points = 10 + floor(3 / 2) = 11.
// Collect all the coins from node 3 using the second way. Total points = 11 + floor(1 / 2) = 11.
// It can be shown that the maximum points we can get after collecting coins from all the nodes is 11.
//
// Constraints:
// n == coins.length
// 	2 <= n <= 105
// 	0 <= coins[i] <= 104
// 	edges.length == n - 1
// 	0 <= edges[i][0], edges[i][1] < n
// 	0 <= k <= 104
//
// Helpful references (internal KB):
// - Finding faces of a planar graph (graph, array, dfs, enumeration)
//   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
//   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
//   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
//   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
//   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
// - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
//   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
//   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
//   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
//   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
//   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} edges
 * @param {number[]} coins
 * @param {number} k
 * @return {number}
 */
var maximumPoints = function(edges, coins, k) {
	const n = coins.length;
	if (n === 0) {
		return 0;
	}

	const adj = Array.from({ length: n }, () => []);
	for (const [u, v] of edges) {
		adj[u].push(v);
		adj[v].push(u);
	}

	let maxCoin = 0;
	for (const c of coins) {
		if (c > maxCoin) {
			maxCoin = c;
		}
	}

	let maxHalves = 0;
	let temp = maxCoin;
	while (temp > 0) {
		maxHalves += 1;
		temp = Math.floor(temp / 2);
	}
	const L = maxHalves + 1; // extra level to safely clamp halving

	const coinVals = Array.from({ length: n }, () => new Array(L + 1));
	for (let i = 0; i < n; i += 1) {
		coinVals[i][0] = coins[i];
		for (let t = 1; t <= L; t += 1) {
			coinVals[i][t] = Math.floor(coinVals[i][t - 1] / 2);
		}
	}

	const parent = new Array(n).fill(-1);
	const order = [];
	const stack = [0];
	parent[0] = 0;
	while (stack.length > 0) {
		const u = stack.pop();
		order.push(u);
		for (const v of adj[u]) {
			if (v === parent[u]) {
				continue;
			}
			parent[v] = u;
			stack.push(v);
		}
	}

	const dp = Array.from({ length: n }, () => new Array(L + 1).fill(0));

	for (let idx = order.length - 1; idx >= 0; idx -= 1) {
		const u = order[idx];
		const children = [];
		for (const v of adj[u]) {
			if (v !== parent[u]) {
				children.push(v);
			}
		}

		for (let t = 0; t <= L; t += 1) {
			const tNext = t < L ? t + 1 : L;
			let option1 = coinVals[u][t] - k;
			let option2 = coinVals[u][tNext];
			for (const v of children) {
				option1 += dp[v][t];
				option2 += dp[v][tNext];
			}
			dp[u][t] = Math.max(option1, option2);
		}
	}

	return dp[0][0];
};
