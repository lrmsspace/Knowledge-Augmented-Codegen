// Source: https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted tree with n nodes, numbered from 0 to n - 1. It is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi.​
//
// Additionally, you are given a 2D integer array queries, where queries[j] = [src1j, src2j, destj].
//
// Return an array answer of length equal to queries.length, where answer[j] is the minimum total weight of a subtree such that it is possible to reach destj from both src1j and src2j using edges in this subtree.
//
// A subtree here is any connected subset of nodes and edges of the original tree forming a valid tree.
//
// Example:
// Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], queries = [[2,3,4],[0,2,5]]
//
// Output: [12,11]
//
// Explanation:
//
// The blue edges represent one of the subtrees that yield the optimal answer.
//
//
//
//
// 	
// 	answer[0]: The total weight of the selected subtree that ensures a path from src1 = 2 and src2 = 3 to dest = 4 is 3 + 5 + 4 = 12.
// 	
// 	
// 	answer[1]: The total weight of the selected subtree that ensures a path from src1 = 0 and src2 = 2 to dest = 5 is 2 + 3 + 6 = 11.
//
// Constraints:
// 3 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ui, vi < n
// 	1 <= wi <= 104
// 	1 <= queries.length <= 105
// 	queries[j].length == 3
// 	0 <= src1j, src2j, destj < n
// 	src1j, src2j, and destj are pairwise distinct.
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
//   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
//   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
//   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
//   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
//   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
// - Second Best Minimum Spanning Tree (graph, tree, mst-kruskal, lca, binary-lifting, enumeration)
//   • When to use: When you need to find a spanning tree with the second smallest total edge weight, typically after finding the primary Minimum Spanning Tree.
//   • Idea: This algorithm finds the second best Minimum Spanning Tree by iterating through non-MST edges, adding each to the MST to form a cycle, and then removing the maximum weight edge on that cycle (excluding the added edge). It leverages Kruskal's for the initial MST and LCA with binary lifting for efficient path maximum queries, achieving an overall time complexity of O(E log E + E log V).
//   • Invariants: The initial MST is always a valid spanning tree with minimum total weight.; For any non-MST edge (u, v) added, a unique cycle is formed in the current graph.
//   • Tips: Precompute LCA and maximum edge weights on paths using binary lifting for efficiency.; The initial MST can be found using Kruskal's or Prim's algorithm.
//   • Pitfalls: Incorrectly identifying the maximum weight edge on the cycle when adding a non-MST edge.; Forgetting to exclude the newly added edge itself when finding the maximum edge on the cycle.
// - Heavy-light decomposition (tree, segment-tree, lca, dfs)
//   • When to use: When you need to perform path queries or updates on a tree efficiently, often involving operations like sum, min, max, or XOR on edges/nodes along a path. It transforms tree paths into linear segments for data structure application.
//   • Idea: Heavy-light decomposition partitions a tree into disjoint heavy paths and light edges, allowing tree path operations to be performed efficiently using data structures like segment trees. It typically achieves O(log^2 N) or O(log N) complexity per query/update after O(N log N) or O(N) preprocessing.
//   • Invariants: Each node belongs to exactly one heavy path.; Moving from a node to its parent via a light edge reduces the subtree size by at least half.
//   • Tips: Perform two DFS traversals: one for subtree sizes and parent pointers, another for heavy/light edges and path IDs.; Map tree nodes to a 1D array for segment tree operations based on their position in heavy paths.
//   • Pitfalls: Incorrectly identifying heavy edges (largest subtree size) during the first DFS.; Off-by-one errors when mapping nodes to segment tree indices or handling path boundaries.
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
#include <stdint.h>

typedef struct { int to; int w; int next; } Edge;

static int lca(int u, int v, int LOG, const int *level, const int *up) {
	if (level[u] < level[v]) { int tmp = u; u = v; v = tmp; }
	int diff = level[u] - level[v];
	for (int k = 0; diff && k < LOG; ++k) {
		if (diff & (1 << k)) {
			u = up[u * LOG + k];
		}
	}
	if (u == v) return u;
	for (int k = LOG - 1; k >= 0; --k) {
		int upu = up[u * LOG + k];
		int upv = up[v * LOG + k];
		if (upu != upv) {
			u = upu;
			v = upv;
		}
	}
	return up[u * LOG + 0];
}

int* minimumWeight(int** edges, int edgesSize, int* edgesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
	int n = edgesSize + 1;
	*returnSize = queriesSize;
	int *answer = (int*)malloc(sizeof(int) * (queriesSize > 0 ? queriesSize : 1));
	if (n <= 0) return answer;

	// Build adjacency list
	int m = edgesSize;
	int totalEdges = m * 2;
	Edge *E = (Edge*)malloc(sizeof(Edge) * (totalEdges > 0 ? totalEdges : 1));
	int *head = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; ++i) head[i] = -1;
	int idx = 0;
	for (int i = 0; i < m; ++i) {
		int u = edges[i][0];
		int v = edges[i][1];
		int w = edges[i][2];
		// u -> v
		E[idx].to = v; E[idx].w = w; E[idx].next = head[u]; head[u] = idx++;
		// v -> u
		E[idx].to = u; E[idx].w = w; E[idx].next = head[v]; head[v] = idx++;
	}

	// Compute LOG for binary lifting
	int LOG = 0;
	while ((1 << LOG) <= n) LOG++;

	// Allocate binary lifting structures
	int *up = (int*)malloc(sizeof(int) * n * LOG);
	int *level = (int*)malloc(sizeof(int) * n);
	long long *depth = (long long*)malloc(sizeof(long long) * n);

	// BFS from root 0 to fill parent (up[][0]), level (edge-depth), and weighted depth
	int root = 0;
	int *parent = (int*)malloc(sizeof(int) * n);
	int *q = (int*)malloc(sizeof(int) * n);
	int qt = 0, qh = 0;
	parent[root] = root;
	level[root] = 0;
	depth[root] = 0;
	up[root * LOG + 0] = root;
	q[qt++] = root;
	while (qh < qt) {
		int u = q[qh++];
		for (int e = head[u]; e != -1; e = E[e].next) {
			int v = E[e].to;
			if (v == parent[u]) continue;
			parent[v] = u;
			level[v] = level[u] + 1;
			depth[v] = depth[u] + (long long)E[e].w;
			up[v * LOG + 0] = u;
			q[qt++] = v;
		}
	}

	// Complete up table
	for (int k = 1; k < LOG; ++k) {
		for (int i = 0; i < n; ++i) {
			int mid = up[i * LOG + (k - 1)];
			up[i * LOG + k] = up[mid * LOG + (k - 1)];
		}
	}

	// Answer queries using Steiner tree property on trees:
	// weight(T(u, v, w)) = (dist(u, v) + dist(u, w) + dist(v, w)) / 2
	for (int j = 0; j < queriesSize; ++j) {
		int src1 = queries[j][0];
		int src2 = queries[j][1];
		int dest = queries[j][2];

		int a = lca(src1, src2, LOG, level, up);
		int b = lca(src1, dest, LOG, level, up);
		int c = lca(src2, dest, LOG, level, up);

		long long d12 = depth[src1] + depth[src2] - 2LL * depth[a];
		long long d1d = depth[src1] + depth[dest] - 2LL * depth[b];
		long long d2d = depth[src2] + depth[dest] - 2LL * depth[c];

		long long steiner = (d12 + d1d + d2d) / 2LL;
		if (steiner < 0) steiner = 0; // safety, though not expected
		answer[j] = (int)steiner;
	}

	// Cleanup
	free(E);
	free(head);
	free(up);
	free(level);
	free(depth);
	free(parent);
	free(q);

	return answer;
}
