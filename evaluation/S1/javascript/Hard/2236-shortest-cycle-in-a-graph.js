// Source: https://leetcode.com/problems/shortest-cycle-in-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1. The edges in the graph are represented by a given 2D integer array edges, where edges[i] = [ui, vi] denotes an edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.
//
// Return the length of the shortest cycle in the graph. If no cycle exists, return -1.
//
// A cycle is a path that starts and ends at the same node, and each edge in the path is used only once.
//
// Example:
// Input: n = 7, edges = [[0,1],[1,2],[2,0],[3,4],[4,5],[5,6],[6,3]]
// Output: 3
// Explanation: The cycle with the smallest length is : 0 -> 1 -> 2 -> 0
//
// Constraints:
// 2 <= n <= 1000
// 	1 <= edges.length <= 1000
// 	edges[i].length == 2
// 	0 <= ui, vi < n
// 	ui != vi
// 	There are no repeated edges.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs)
//   • When to use: Use when finding the shortest path or minimum number of edges between nodes in an unweighted graph, or to explore a graph layer by layer. It is also suitable for finding shortest cycles or identifying all components of shortest paths.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring the shortest path in terms of edges is found from a source node to all reachable nodes. It operates in O(V + E) time complexity for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at depth `k` or `k+1` from the source.; The distance recorded for any visited node is its shortest path length from the source.
//   • Tips: Run multiple BFS from different sources to find global properties like shortest cycles.; Maintain a distance array to record the shortest path length from the source to each node.
//   • Pitfalls: Applying BFS directly to weighted graphs will not yield shortest paths.; Failing to mark visited nodes can lead to infinite loops in cyclic graphs or incorrect path lengths.
// - Edge connectivity / Vertex connectivity (graph, enumeration)
//   • When to use: Used to quantify a graph's resilience by finding the minimum number of edges or vertices whose removal disconnects it, or separates a specific pair of nodes.
//   • Idea: Edge connectivity is the minimum edges to disconnect a graph, while vertex connectivity is for vertices. Both are often computed using max-flow min-cut theorems, typically in polynomial time.
//   • Invariants: The flow through any edge in the network does not exceed its capacity.; For any intermediate vertex (not source or sink), the total incoming flow equals the total outgoing flow.
//   • Tips: Edge connectivity between two specific vertices can be found using a max-flow min-cut algorithm.; To find global edge connectivity, iterate over all pairs of vertices or use specialized algorithms.
//   • Pitfalls: Confusing edge connectivity (edges) with vertex connectivity (vertices) requirements.; Incorrectly applying max-flow for global connectivity without considering all relevant source-sink pairs.
// - Finding faces of a planar graph (graph, array, dfs, enumeration)
//   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
//   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
//   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
//   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
//   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
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
 * @return {number}
 */
var findShortestCycle = function(n, edges) {
	var graph = Array.from({ length: n }, function() { return []; });
	for (var i = 0; i < edges.length; i++) {
		var a = edges[i][0];
		var b = edges[i][1];
		graph[a].push(b);
		graph[b].push(a);
	}

	var best = Infinity;

	for (var start = 0; start < n; start++) {
		var dist = new Array(n).fill(-1);
		var parent = new Array(n).fill(-1);
		var queue = new Array(n);
		var head = 0;
		var tail = 0;

		dist[start] = 0;
		queue[tail++] = start;

		while (head < tail) {
			var u = queue[head++];
			if (dist[u] + 1 >= best) {
				continue;
			}
			var neighbors = graph[u];
			for (var j = 0; j < neighbors.length; j++) {
				var v = neighbors[j];
				if (dist[v] === -1) {
					dist[v] = dist[u] + 1;
					parent[v] = u;
					queue[tail++] = v;
				} else if (parent[u] !== v) {
					var cycleLen = dist[u] + dist[v] + 1;
					if (cycleLen < best) {
						best = cycleLen;
					}
				}
			}
		}
	}

	return best === Infinity ? -1 : best;
};
