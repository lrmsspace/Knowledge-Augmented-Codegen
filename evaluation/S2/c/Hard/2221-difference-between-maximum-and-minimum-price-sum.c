// Source: https://leetcode.com/problems/difference-between-maximum-and-minimum-price-sum/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected and initially unrooted tree with n nodes indexed from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Each node has an associated price. You are given an integer array price, where price[i] is the price of the ith node.
//
// The price sum of a given path is the sum of the prices of all nodes lying on that path.
//
// The tree can be rooted at any node root of your choice. The incurred cost after choosing root is the difference between the maximum and minimum price sum amongst all paths starting at root.
//
// Return the maximum possible cost amongst all possible root choices.
//
// Example:
// Input: n = 6, edges = [[0,1],[1,2],[1,3],[3,4],[3,5]], price = [9,8,7,6,10,5]
// Output: 24
// Explanation: The diagram above denotes the tree after rooting it at node 2. The first part (colored in red) shows the path with the maximum price sum. The second part (colored in blue) shows the path with the minimum price sum.
// - The first path contains nodes [2,1,3,4]: the prices are [7,8,6,10], and the sum of the prices is 31.
// - The second path contains the node [2] with the price [7].
// The difference between the maximum and minimum price sum is 24. It can be proved that 24 is the maximum cost.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	0 <= ai, bi <= n - 1
// 	edges represents a valid tree.
// 	price.length == n
// 	1 <= price[i] <= 105
//
// Helpful references (internal KB):
// - Second Best Minimum Spanning Tree (graph, tree, mst-kruskal, lca, binary-lifting, enumeration)
//   • When to use: When you need to find a spanning tree with the second smallest total edge weight, typically after finding the primary Minimum Spanning Tree.
//   • Idea: This algorithm finds the second best Minimum Spanning Tree by iterating through non-MST edges, adding each to the MST to form a cycle, and then removing the maximum weight edge on that cycle (excluding the added edge). It leverages Kruskal's for the initial MST and LCA with binary lifting for efficient path maximum queries, achieving an overall time complexity of O(E log E + E log V).
//   • Invariants: The initial MST is always a valid spanning tree with minimum total weight.; For any non-MST edge (u, v) added, a unique cycle is formed in the current graph.
//   • Tips: Precompute LCA and maximum edge weights on paths using binary lifting for efficiency.; The initial MST can be found using Kruskal's or Prim's algorithm.
//   • Pitfalls: Incorrectly identifying the maximum weight edge on the cycle when adding a non-MST edge.; Forgetting to exclude the newly added edge itself when finding the maximum edge on the cycle.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maxOutput(int n, int** edges, int edgesSize, int* edgesColSize, int* price, int priceSize) {
	(void)edgesColSize;
	(void)priceSize;

	if (n <= 1) {
		return 0;
	}

	{
		int m = edgesSize * 2;
		int i;
		int edgePtr = 0;

		int* head = (int*)malloc(n * (int)sizeof(int));
		int* to = (int*)malloc(m * (int)sizeof(int));
		int* next = (int*)malloc(m * (int)sizeof(int));
		int* parent = (int*)malloc(n * (int)sizeof(int));
		int* order = (int*)malloc(n * (int)sizeof(int));
		int* stack = (int*)malloc(n * (int)sizeof(int));
		long long* down = (long long*)malloc(n * (int)sizeof(long long));
		long long* up = (long long*)malloc(n * (int)sizeof(long long));

		if (!head || !to || !next || !parent ||
			!order || !stack || !down || !up) {
			free(head);
			free(to);
			free(next);
			free(parent);
			free(order);
			free(stack);
			free(down);
			free(up);
			return 0;
		}

		for (i = 0; i < n; ++i) {
			head[i] = -1;
			parent[i] = -2;
		}

		for (i = 0; i < edgesSize; ++i) {
			int a = edges[i][0];
			int b = edges[i][1];

			to[edgePtr] = b;
			next[edgePtr] = head[a];
			head[a] = edgePtr;
			++edgePtr;

			to[edgePtr] = a;
			next[edgePtr] = head[b];
			head[b] = edgePtr;
			++edgePtr;
		}

		{
			int sp = 0;
			int ord = 0;
			stack[sp++] = 0;
			parent[0] = -1;

			while (sp > 0) {
				int u = stack[--sp];
				int e = head[u];
				order[ord++] = u;

				while (e != -1) {
					int v = to[e];
					if (v != parent[u]) {
						parent[v] = u;
						stack[sp++] = v;
					}
					e = next[e];
				}
			}
		}

		for (i = n - 1; i >= 0; --i) {
			int u = order[i];
			int e = head[u];
			long long best = (long long)price[u];

			while (e != -1) {
				int v = to[e];
				if (v != parent[u]) {
					long long cand = (long long)price[u] + down[v];
					if (cand > best) {
						best = cand;
					}
				}
				e = next[e];
			}
			down[u] = best;
		}

		up[0] = (long long)price[0];

		for (i = 0; i < n; ++i) {
			int u = order[i];
			int e;
			long long top1 = -1;
			long long top2 = -1;
			int top1Child = -1;

			e = head[u];
			while (e != -1) {
				int v = to[e];
				if (v != parent[u]) {
					long long val = down[v];
					if (val > top1) {
						top2 = top1;
						top1 = val;
						top1Child = v;
					} else if (val > top2) {
						top2 = val;
					}
				}
				e = next[e];
			}

			e = head[u];
			while (e != -1) {
				int v = to[e];
				if (v != parent[u]) {
					long long bestFromU = (long long)price[u];
					long long siblingBest = (v == top1Child) ? top2 : top1;

					if (up[u] > bestFromU) {
						bestFromU = up[u];
					}
					if (siblingBest >= 0) {
						long long viaSibling = (long long)price[u] + siblingBest;
						if (viaSibling > bestFromU) {
							bestFromU = viaSibling;
						}
					}

					up[v] = (long long)price[v] + bestFromU;
				}
				e = next[e];
			}
		}

		{
			long long ans = 0;
			for (i = 0; i < n; ++i) {
				long long farthest = down[i] > up[i] ? down[i] : up[i];
				long long cost = farthest - (long long)price[i];
				if (cost > ans) {
					ans = cost;
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
			return ans;
		}
	}
}
    