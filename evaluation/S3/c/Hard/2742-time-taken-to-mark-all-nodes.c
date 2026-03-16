// Source: https://leetcode.com/problems/time-taken-to-mark-all-nodes/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.
//
// Initially, all nodes are unmarked. For each node i:
//
//
// 	If i is odd, the node will get marked at time x if there is at least one node adjacent to it which was marked at time x - 1.
// 	If i is even, the node will get marked at time x if there is at least one node adjacent to it which was marked at time x - 2.
//
//
// Return an array times where times[i] is the time when all nodes get marked in the tree, if you mark node i at time t = 0.
//
// Note that the answer for each times[i] is independent, i.e. when you mark node i all other nodes are unmarked.
//
// Example:
// Input: edges = [[0,1],[0,2]]
//
// Output: [2,4,3]
//
// Explanation:
//
//
//
//
// 	For i = 0:
//
// 	
// 		Node 1 is marked at t = 1, and Node 2 at t = 2.
// 	
// 	
// 	For i = 1:
// 	
// 		Node 0 is marked at t = 2, and Node 2 at t = 4.
// 	
// 	
// 	For i = 2:
// 	
// 		Node 0 is marked at t = 2, and Node 1 at t = 3.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= edges[i][0], edges[i][1] <= n - 1
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
//   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
//   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
//   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
//   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
//   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
// - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
//   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
//   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
//   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
//   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
//   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
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
int* timeTaken(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
	(void)edgesColSize;

	{
		int n = edgesSize + 1;
		int m = edgesSize * 2;
		int* head = (int*)malloc(sizeof(int) * n);
		int* to = (int*)malloc(sizeof(int) * m);
		int* next = (int*)malloc(sizeof(int) * m);
		int idx = 0;
		int i;

		int* parent = (int*)malloc(sizeof(int) * n);
		int* order = (int*)malloc(sizeof(int) * n);
		int* stack = (int*)malloc(sizeof(int) * n);
		int* down = (int*)malloc(sizeof(int) * n);
		int* up = (int*)malloc(sizeof(int) * n);
		int* best1Val = (int*)malloc(sizeof(int) * n);
		int* best2Val = (int*)malloc(sizeof(int) * n);
		int* best1Child = (int*)malloc(sizeof(int) * n);
		int* ans = (int*)malloc(sizeof(int) * n);

		if (!head || !to || !next || !parent || !order || !stack || !down || !up || !best1Val || !best2Val || !best1Child || !ans) {
			free(head);
			free(to);
			free(next);
			free(parent);
			free(order);
			free(stack);
			free(down);
			free(up);
			free(best1Val);
			free(best2Val);
			free(best1Child);
			free(ans);
			*returnSize = 0;
			return NULL;
		}

		for (i = 0; i < n; ++i) {
			head[i] = -1;
		}

		for (i = 0; i < edgesSize; ++i) {
			int u = edges[i][0];
			int v = edges[i][1];

			to[idx] = v;
			next[idx] = head[u];
			head[u] = idx;
			++idx;

			to[idx] = u;
			next[idx] = head[v];
			head[v] = idx;
			++idx;
		}

		for (i = 0; i < n; ++i) {
			parent[i] = -2;
		}

		{
			int top = 0;
			int ord = 0;
			stack[top++] = 0;
			parent[0] = -1;

			while (top > 0) {
				int u = stack[--top];
				int e = head[u];
				order[ord++] = u;

				while (e != -1) {
					int v = to[e];
					if (v != parent[u] && parent[v] == -2) {
						parent[v] = u;
						stack[top++] = v;
					}
					e = next[e];
				}
			}

			for (i = ord - 1; i >= 0; --i) {
				int u = order[i];
				int e = head[u];
				int b1 = 0;
				int b2 = 0;
				int b1c = -1;

				while (e != -1) {
					int v = to[e];
					if (parent[v] == u) {
						int wv = (v & 1) ? 1 : 2;
						int cand = wv + down[v];
						if (cand > b1) {
							b2 = b1;
							b1 = cand;
							b1c = v;
						} else if (cand > b2) {
							b2 = cand;
						}
					}
					e = next[e];
				}

				best1Val[u] = b1;
				best2Val[u] = b2;
				best1Child[u] = b1c;
				down[u] = b1;
			}

			up[0] = 0;
			for (i = 0; i < ord; ++i) {
				int u = order[i];
				int e = head[u];

				while (e != -1) {
					int v = to[e];
					if (parent[v] == u) {
						int useFromU = up[u];
						int wu = (u & 1) ? 1 : 2;
						if (best1Child[u] == v) {
							if (best2Val[u] > useFromU) {
								useFromU = best2Val[u];
							}
						} else {
							if (best1Val[u] > useFromU) {
								useFromU = best1Val[u];
							}
						}
						up[v] = wu + useFromU;
					}
					e = next[e];
				}
			}

			for (i = 0; i < n; ++i) {
				ans[i] = (down[i] > up[i]) ? down[i] : up[i];
			}
		}

		free(head);
		free(to);
		free(next);
		free(parent);
		free(order);
		free(stack);
		free(down);
		free(up);
		free(best1Val);
		free(best2Val);
		free(best1Child);

		*returnSize = n;
		return ans;
	}
}