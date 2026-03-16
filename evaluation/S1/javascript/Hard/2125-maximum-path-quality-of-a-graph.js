// Source: https://leetcode.com/problems/maximum-path-quality-of-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph with n nodes numbered from 0 to n - 1 (inclusive). You are given a 0-indexed integer array values where values[i] is the value of the ith node. You are also given a 0-indexed 2D integer array edges, where each edges[j] = [uj, vj, timej] indicates that there is an undirected edge between the nodes uj and vj, and it takes timej seconds to travel between the two nodes. Finally, you are given an integer maxTime.
//
// A valid path in the graph is any path that starts at node 0, ends at node 0, and takes at most maxTime seconds to complete. You may visit the same node multiple times. The quality of a valid path is the sum of the values of the unique nodes visited in the path (each node's value is added at most once to the sum).
//
// Return the maximum quality of a valid path.
//
// Note: There are at most four edges connected to each node.
//
// Example:
// Input: values = [0,32,10,43], edges = [[0,1,10],[1,2,15],[0,3,10]], maxTime = 49
// Output: 75
// Explanation:
// One possible path is 0 -> 1 -> 0 -> 3 -> 0. The total time taken is 10 + 10 + 10 + 10 = 40 <= 49.
// The nodes visited are 0, 1, and 3, giving a maximal path quality of 0 + 32 + 43 = 75.
//
// Constraints:
// n == values.length
// 	1 <= n <= 1000
// 	0 <= values[i] <= 108
// 	0 <= edges.length <= 2000
// 	edges[j].length == 3 
// 	0 <= uj < vj <= n - 1
// 	10 <= timej, maxTime <= 100
// 	All the pairs [uj, vj] are unique.
// 	There are at most four edges connected to each node.
// 	The graph may not be connected.
//
// Helpful references (internal KB):
// - Dijkstra on sparse graphs (heap, queue, dijkstra)
//   • When to use: When you need to find the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights, especially efficient for sparse graphs.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source to all other vertices in a weighted graph with non-negative edge weights. It uses a priority queue to greedily explore vertices, achieving O(E log V) complexity with a binary heap.
//   • Invariants: At the start of each iteration, dist[u] holds the shortest distance found so far from the source to u.; All vertices already extracted from the priority queue have their final shortest distance determined.
//   • Tips: Use a priority queue (min-heap) to efficiently retrieve the unvisited vertex with the smallest distance.; Initialize all distances to infinity and the source distance to zero.
//   • Pitfalls: Does not work correctly with negative edge weights; Bellman-Ford or SPFA is needed.; Forgetting to mark vertices as visited or handle duplicate entries in the priority queue can lead to incorrectness or TLE.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Finding bridges in a graph in O(N+M) (graph, array, dfs)
//   • When to use: Use this algorithm when you need to identify edges whose removal would increase the number of connected components in an undirected graph. It's suitable for analyzing network robustness or critical connections.
//   • Idea: This algorithm uses Depth First Search (DFS) to find bridges in an undirected graph by tracking discovery times and the lowest reachable discovery time from a node or its descendants. It operates in linear time, O(N+M), where N is the number of vertices and M is the number of edges.
//   • Invariants: For any node `u` currently in the DFS stack, `tin[u]` is its unique discovery time.; For any node `u` and its child `v` in the DFS tree, `low[v]` represents the earliest discovery time reachable from `v`'s subtree (including `v`) using at most one back-edge.
//   • Tips: Initialize discovery times (tin) and lowest reachable times (low) arrays, along with a visited array.; Pass the parent vertex to the DFS function to avoid treating the parent edge as a back-edge.
//   • Pitfalls: Forgetting to pass the parent node or incorrectly handling the parent edge, leading to false bridge detections.; Failing to initialize `low` values correctly, especially for leaf nodes or isolated components.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} values
 * @param {number[][]} edges
 * @param {number} maxTime
 * @return {number}
 */
var maximalPathQuality = function(values, edges, maxTime) {
	var n = values.length;
	var graph = Array.from({ length: n }, function() { return []; });
	for (var i = 0; i < edges.length; i++) {
		var u = edges[i][0];
		var v = edges[i][1];
		var t = edges[i][2];
		graph[u].push([v, t]);
		graph[v].push([u, t]);
	}

	// Dijkstra from node 0 to prune paths that cannot return in time.
	var dist = Array(n).fill(Infinity);
	dist[0] = 0;
	var heap = [];
	heapPush(heap, [0, 0]);
	while (heap.length > 0) {
		var item = heapPop(heap);
		var d = item[0];
		var node = item[1];
		if (d !== dist[node]) {
			continue;
		}
		var neighbors = graph[node];
		for (var j = 0; j < neighbors.length; j++) {
			var next = neighbors[j][0];
			var cost = neighbors[j][1];
			var nd = d + cost;
			if (nd < dist[next]) {
				dist[next] = nd;
				heapPush(heap, [nd, next]);
			}
		}
	}

	var best = 0;
	var visits = Array(n).fill(0);

	function dfs(node, timeUsed, quality) {
		if (timeUsed + dist[node] > maxTime) {
			return;
		}
		if (node === 0) {
			if (quality > best) {
				best = quality;
			}
		}
		var neighbors = graph[node];
		for (var i = 0; i < neighbors.length; i++) {
			var next = neighbors[i][0];
			var cost = neighbors[i][1];
			var newTime = timeUsed + cost;
			if (newTime > maxTime) {
				continue;
			}
			var add = 0;
			if (visits[next] === 0) {
				add = values[next];
			}
			visits[next] += 1;
			dfs(next, newTime, quality + add);
			visits[next] -= 1;
		}
	}

	visits[0] = 1;
	dfs(0, 0, values[0]);
	return best;
};

function heapPush(heap, item) {
	heap.push(item);
	var idx = heap.length - 1;
	while (idx > 0) {
		var parent = Math.floor((idx - 1) / 2);
		if (heap[parent][0] <= heap[idx][0]) {
			break;
		}
		var tmp = heap[parent];
		heap[parent] = heap[idx];
		heap[idx] = tmp;
		idx = parent;
	}
}

function heapPop(heap) {
	var top = heap[0];
	var last = heap.pop();
	if (heap.length > 0) {
		heap[0] = last;
		var idx = 0;
		var len = heap.length;
		while (true) {
			var left = idx * 2 + 1;
			var right = idx * 2 + 2;
			var smallest = idx;
			if (left < len && heap[left][0] < heap[smallest][0]) {
				smallest = left;
			}
			if (right < len && heap[right][0] < heap[smallest][0]) {
				smallest = right;
			}
			if (smallest === idx) {
				break;
			}
			var tmp = heap[smallest];
			heap[smallest] = heap[idx];
			heap[idx] = tmp;
			idx = smallest;
		}
	}
	return top;
}
