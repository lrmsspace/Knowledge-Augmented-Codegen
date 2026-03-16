// Source: https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/   |   Difficulty: Medium
//
// Problem Description:
// There exist two undirected trees with n and m nodes, with distinct labels in ranges [0, n - 1] and [0, m - 1], respectively.
//
// You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree. You are also given an integer k.
//
// Node u is target to node v if the number of edges on the path from u to v is less than or equal to k. Note that a node is always target to itself.
//
// Return an array of n integers answer, where answer[i] is the maximum possible number of nodes target to node i of the first tree if you have to connect one node from the first tree to another node in the second tree.
//
// Note that queries are independent from each other. That is, for every query you will remove the added edge before proceeding to the next query.
//
// Example:
// Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], k = 2
//
// Output: [9,7,9,8,8]
//
// Explanation:
//
//
// 	For i = 0, connect node 0 from the first tree to node 0 from the second tree.
// 	For i = 1, connect node 1 from the first tree to node 0 from the second tree.
// 	For i = 2, connect node 2 from the first tree to node 4 from the second tree.
// 	For i = 3, connect node 3 from the first tree to node 4 from the second tree.
// 	For i = 4, connect node 4 from the first tree to node 4 from the second tree.
//
// Constraints:
// 2 <= n, m <= 1000
// 	edges1.length == n - 1
// 	edges2.length == m - 1
// 	edges1[i].length == edges2[i].length == 2
// 	edges1[i] = [ai, bi]
// 	0 <= ai, bi < n
// 	edges2[i] = [ui, vi]
// 	0 <= ui, vi < m
// 	The input is generated such that edges1 and edges2 represent valid trees.
// 	0 <= k <= 1000
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdlib.h>
#include <string.h>

static void buildAdj(int n, int** edges, int edgesSize, int** adjOut, int** degOut) {
	int* deg = (int*)calloc((size_t)n, sizeof(int));
	int* ptr;
	int* adj;
	int i;

	for (i = 0; i < edgesSize; ++i) {
		int u = edges[i][0];
		int v = edges[i][1];
		deg[u]++;
		deg[v]++;
	}

	ptr = (int*)calloc((size_t)n, sizeof(int));
	adj = (int*)malloc((size_t)(2 * edgesSize) * sizeof(int));

	for (i = 1; i < n; ++i) {
		ptr[i] = ptr[i - 1] + deg[i - 1];
	}

	for (i = 0; i < edgesSize; ++i) {
		int u = edges[i][0];
		int v = edges[i][1];
		adj[ptr[u]++] = v;
		adj[ptr[v]++] = u;
	}

	for (i = n - 1; i > 0; --i) {
		ptr[i] = ptr[i - 1];
	}
	ptr[0] = 0;

	*adjOut = adj;
	*degOut = deg;
	free(ptr);
}

static int countWithinK(int n, int* adj, int* deg, int src, int k, int* dist, int* q) {
	int head = 0;
	int tail = 0;
	int count = 0;
	int* start = (int*)calloc((size_t)n, sizeof(int));
	int i;

	for (i = 1; i < n; ++i) {
		start[i] = start[i - 1] + deg[i - 1];
	}

	for (i = 0; i < n; ++i) {
		dist[i] = -1;
	}

	dist[src] = 0;
	q[tail++] = src;

	while (head < tail) {
		int u = q[head++];
		int du = dist[u];
		int begin;
		int end;

		if (du > k) {
			continue;
		}
		count++;
		if (du == k) {
			continue;
		}

		begin = start[u];
		end = begin + deg[u];
		for (i = begin; i < end; ++i) {
			int v = adj[i];
			if (dist[v] == -1) {
				dist[v] = du + 1;
				q[tail++] = v;
			}
		}
	}

	free(start);
	return count;
}

int* maxTargetNodes(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size, int* edges2ColSize, int k, int* returnSize) {
	int n = edges1Size + 1;
	int m = edges2Size + 1;
	int* adj1;
	int* adj2;
	int* deg1;
	int* deg2;
	int* ans;
	int* dist;
	int* q;
	int best2 = 0;
	int i;

	(void)edges1ColSize;
	(void)edges2ColSize;

	buildAdj(n, edges1, edges1Size, &adj1, &deg1);
	buildAdj(m, edges2, edges2Size, &adj2, &deg2);

	ans = (int*)malloc((size_t)n * sizeof(int));
	dist = (int*)malloc((size_t)((n > m) ? n : m) * sizeof(int));
	q = (int*)malloc((size_t)((n > m) ? n : m) * sizeof(int));

	if (k > 0) {
		for (i = 0; i < m; ++i) {
			int cnt = countWithinK(m, adj2, deg2, i, k - 1, dist, q);
			if (cnt > best2) {
				best2 = cnt;
			}
		}
	}

	for (i = 0; i < n; ++i) {
		int cnt1 = countWithinK(n, adj1, deg1, i, k, dist, q);
		ans[i] = cnt1 + best2;
	}

	free(adj1);
	free(adj2);
	free(deg1);
	free(deg2);
	free(dist);
	free(q);

	*returnSize = n;
	return ans;
}