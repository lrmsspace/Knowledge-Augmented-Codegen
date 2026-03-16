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
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
// - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
//   • When to use: Use when you need to find the Lowest Common Ancestor for multiple pairs of nodes in a tree, and all queries are known beforehand. It's an efficient offline approach for batch processing LCA queries.
//   • Idea: Tarjan's offline LCA algorithm uses a Depth-First Search (DFS) traversal combined with a Union-Find data structure to answer all LCA queries efficiently. It processes N nodes and Q queries in O(N + Q * alpha(N)) time, where alpha is the inverse Ackermann function.
//   • Invariants: After visiting a node 'u' and all its children, 'u' is marked as visited.; For any node 'v' whose subtree has been fully processed, 'find_set(v)' returns the representative of 'v''s component.
//   • Tips: Mark nodes as visited during DFS to track processed subtrees.; Use Union-Find's union operation to merge child subtrees with their parent after processing.
//   • Pitfalls: Forgetting to mark nodes as visited, leading to incorrect LCA identification.; Incorrectly updating the 'ancestor' array or 'find_set' logic in Union-Find.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

 #include <stdlib.h>

long long maxOutput(int n, int** edges, int edgesSize, int* edgesColSize, int* price, int priceSize) {
	(void)edgesColSize;
	(void)priceSize;

	if (n <= 1) {
		return 0;
	}

	{
		int m = edgesSize * 2;
		int* head = (int*)malloc((size_t)n * sizeof(int));
		int* to = (int*)malloc((size_t)m * sizeof(int));
		int* next = (int*)malloc((size_t)m * sizeof(int));
		int idx = 0;

		int* parent = (int*)malloc((size_t)n * sizeof(int));
		int* order = (int*)malloc((size_t)n * sizeof(int));
		int* stack = (int*)malloc((size_t)n * sizeof(int));

		long long* down = (long long*)malloc((size_t)n * sizeof(long long));
		long long* up = (long long*)malloc((size_t)n * sizeof(long long));

		long long answer = 0;
		int top = 0;
		int ordSize = 0;
		int i;

		if (!head || !to || !next || !parent || !order || !stack || !down || !up) {
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
		}

		for (i = 0; i < edgesSize; ++i) {
			int a = edges[i][0];
			int b = edges[i][1];

			to[idx] = b;
			next[idx] = head[a];
			head[a] = idx++;

			to[idx] = a;
			next[idx] = head[b];
			head[b] = idx++;
		}

		for (i = 0; i < n; ++i) {
			parent[i] = -2;
		}

		parent[0] = -1;
		stack[top++] = 0;

		while (top > 0) {
			int u = stack[--top];
			int e;
			order[ordSize++] = u;

			for (e = head[u]; e != -1; e = next[e]) {
				int v = to[e];
				if (parent[v] != -2) {
					continue;
				}
				parent[v] = u;
				stack[top++] = v;
			}
		}

		for (i = n - 1; i >= 0; --i) {
			int u = order[i];
			int e;
			long long bestChild = 0;

			for (e = head[u]; e != -1; e = next[e]) {
				int v = to[e];
				if (parent[v] == u && down[v] > bestChild) {
					bestChild = down[v];
				}
			}
			down[u] = (long long)price[u] + bestChild;
		}

		up[0] = 0;

		for (i = 0; i < n; ++i) {
			int u = order[i];
			int e;
			long long top1 = 0;
			long long top2 = 0;

			for (e = head[u]; e != -1; e = next[e]) {
				int v = to[e];
				long long contrib = (v == parent[u]) ? up[u] : down[v];

				if (contrib >= top1) {
					top2 = top1;
					top1 = contrib;
				} else if (contrib > top2) {
					top2 = contrib;
				}
			}

			if (top1 > answer) {
				answer = top1;
			}

			for (e = head[u]; e != -1; e = next[e]) {
				int v = to[e];
				if (parent[v] == u) {
					long long contrib = down[v];
					long long bestExcludingV = (contrib == top1) ? top2 : top1;
					up[v] = (long long)price[u] + bestExcludingV;
				}
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

		return answer;
	}
}
