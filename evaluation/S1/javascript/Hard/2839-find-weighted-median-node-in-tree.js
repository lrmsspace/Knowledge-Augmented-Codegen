// Source: https://leetcode.com/problems/find-weighted-median-node-in-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an edge from node ui to vi with weight wi.
//
// The weighted median node is defined as the first node x on the path from ui to vi such that the sum of edge weights from ui to x is greater than or equal to half of the total path weight.
//
// You are given a 2D integer array queries. For each queries[j] = [uj, vj], determine the weighted median node along the path from uj to vj.
//
// Return an array ans, where ans[j] is the node index of the weighted median for queries[j].
//
// Example:
// Input: n = 2, edges = [[0,1,7]], queries = [[1,0],[0,1]]
//
// Output: [0,1]
//
// Explanation:
//
//
//
//
// 	
// 		
// 			Query
// 			Path
// 			Edge
// 			Weights
// 			Total
// 			Path
// 			Weight
// 			Half
// 			Explanation
// 			Answer
// 		
// 	
// 	
// 		
// 			[1, 0]
// 			1 → 0
// 			[7]
// 			7
// 			3.5
// 			Sum from 1 → 0 = 7 >= 3.5, median is node 0.
// 			0
// 		
// 		
// 			[0, 1]
// 			0 → 1
// 			[7]
// 			7
// 			3.5
// 			Sum from 0 → 1 = 7 >= 3.5, median is node 1.
// 			1
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	0 <= ui, vi < n
// 	1 <= wi <= 109
// 	1 <= queries.length <= 105
// 	queries[j] == [uj, vj]
// 	0 <= uj, vj < n
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
//   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
//   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
//   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
//   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
//   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
// - Minimum spanning tree - Prim's algorithm (graph, mst-prim, greedy)
//   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, undirected, weighted graph. It is often preferred for dense graphs due to its O(V^2) or O(E log V) complexity.
//   • Idea: Prim's algorithm is a greedy algorithm that builds a minimum spanning tree by iteratively adding the cheapest edge connecting a vertex in the growing tree to one outside it. It typically runs in O(E log V) time with a binary heap or O(V^2) with an adjacency matrix.
//   • Invariants: The set of vertices already included in the MST forms a connected component.; For any vertex not yet in the MST, its associated key/distance stores the minimum weight of an edge connecting it to a vertex already in the MST.
//   • Tips: Use a priority queue to efficiently retrieve the minimum weight edge connecting to the MST.; Initialize distances for all vertices to infinity, except the starting vertex (0).
//   • Pitfalls: Not suitable for disconnected graphs; it will only find an MST for the component of the starting vertex.; Forgetting to handle edge cases like graphs with no edges or a single vertex.
// - Lowest Common Ancestor (tree, segment-tree)
//   • When to use: Use this approach to efficiently answer multiple Lowest Common Ancestor queries on a static tree. It is suitable when precomputation time is acceptable for faster subsequent queries.
//   • Idea: This method transforms the LCA problem into a Range Minimum Query (RMQ) problem by constructing an Euler tour of the tree. It achieves O(N log N) precomputation and O(log N) query time by building a segment tree over the depths of nodes in the Euler tour.
//   • Invariants: The Euler tour array correctly records nodes in DFS entry and exit order.; The depth array stores the depth of each node as it appears in the Euler tour.
//   • Tips: Perform a DFS to generate an Euler tour of the tree, recording nodes and their depths.; Store the first occurrence index of each node in the Euler tour array.
//   • Pitfalls: Incorrectly constructing the Euler tour or depth array, leading to wrong ranges for RMQ.; Off-by-one errors when mapping node indices to Euler tour indices or defining segment tree query ranges.
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
 * @param {number[][]} queries
 * @return {number[]}
 */
var findMedian = function(n, edges, queries) {
	const adj = Array.from({ length: n }, () => []);
	for (const [u, v, w] of edges) {
		adj[u].push([v, w]);
		adj[v].push([u, w]);
	}

	const LOG = Math.ceil(Math.log2(Math.max(2, n))) + 1;
	const up = Array.from({ length: LOG }, () => new Array(n).fill(0));
	const upW = Array.from({ length: LOG }, () => new Array(n).fill(0));
	const depth = new Array(n).fill(0);
	const dist = new Array(n).fill(0);

	const stack = [0];
	const parent = new Array(n).fill(0);
	const weightToParent = new Array(n).fill(0);
	parent[0] = 0;
	weightToParent[0] = 0;
	depth[0] = 0;
	dist[0] = 0;

	while (stack.length) {
		const node = stack.pop();
		for (const [next, w] of adj[node]) {
			if (next === parent[node]) {
				continue;
			}
			parent[next] = node;
			weightToParent[next] = w;
			depth[next] = depth[node] + 1;
			dist[next] = dist[node] + w;
			stack.push(next);
		}
	}

	for (let i = 0; i < n; i += 1) {
		up[0][i] = parent[i];
		upW[0][i] = weightToParent[i];
	}

	for (let k = 1; k < LOG; k += 1) {
		for (let i = 0; i < n; i += 1) {
			const mid = up[k - 1][i];
			up[k][i] = up[k - 1][mid];
			upW[k][i] = upW[k - 1][i] + upW[k - 1][mid];
		}
	}

	const lca = (a, b) => {
		let u = a;
		let v = b;
		if (depth[u] < depth[v]) {
			const tmp = u;
			u = v;
			v = tmp;
		}
		let diff = depth[u] - depth[v];
		for (let k = LOG - 1; k >= 0; k -= 1) {
			if ((diff >> k) & 1) {
				u = up[k][u];
			}
		}
		if (u === v) {
			return u;
		}
		for (let k = LOG - 1; k >= 0; k -= 1) {
			if (up[k][u] !== up[k][v]) {
				u = up[k][u];
				v = up[k][v];
			}
		}
		return up[0][u];
	};

	const liftWithin = (start, ancestorLimit, limit) => {
		let node = start;
		let moved = 0;
		for (let k = LOG - 1; k >= 0; k -= 1) {
			const next = up[k][node];
			const step = upW[k][node];
			if (depth[next] >= depth[ancestorLimit] && moved + step <= limit) {
				moved += step;
				node = next;
			}
		}
		return { node, moved };
	};

	const ans = new Array(queries.length);
	for (let i = 0; i < queries.length; i += 1) {
		const [u, v] = queries[i];
		const w = lca(u, v);
		const du = dist[u] - dist[w];
		const dv = dist[v] - dist[w];
		const total = du + dv;
		const half = total / 2;

		if (half <= du) {
			const lifted = liftWithin(u, w, half);
			if (lifted.moved === half) {
				ans[i] = lifted.node;
			} else {
				ans[i] = up[0][lifted.node];
			}
		} else {
			const rem = half - du;
			const limit = dv - rem;
			const lifted = liftWithin(v, w, limit);
			ans[i] = lifted.node;
		}
	}

	return ans;
};
