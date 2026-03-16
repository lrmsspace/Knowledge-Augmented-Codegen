// Source: https://leetcode.com/problems/longest-special-path/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1, represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi with length lengthi. You are also given an integer array nums, where nums[i] represents the value at node i.
//
// A special path is defined as a downward path from an ancestor node to a descendant node such that all the values of the nodes in that path are unique.
//
// Note that a path may start and end at the same node.
//
// Return an array result of size 2, where result[0] is the length of the longest special path, and result[1] is the minimum number of nodes in all possible longest special paths.
//
// Example:
// Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], nums = [2,1,2,1,3,1]
//
// Output: [6,2]
//
// Explanation:
//
// In the image below, nodes are colored by their corresponding values in nums
//
//
//
// The longest special paths are 2 -> 5 and 0 -> 1 -> 4, both having a length of 6. The minimum number of nodes across all longest special paths is 2.
//
// Constraints:
// 2 <= n <= 5 * 104
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ui, vi < n
// 	1 <= lengthi <= 103
// 	nums.length == n
// 	0 <= nums[i] <= 5 * 104
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Checking a graph for acyclicity and finding a cycle in O(M) (graph, array, dfs)
//   • When to use: Use when needing to determine if a graph contains any cycles or to identify one such cycle. It is applicable to both directed and undirected graphs.
//   • Idea: This algorithm uses Depth First Search to detect cycles in a graph by tracking visited states of nodes during traversal. It runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently on the DFS recursion stack are marked as 'gray' (or equivalent).; All nodes fully explored and not part of the current path are marked as 'black' (or equivalent).
//   • Tips: For directed graphs, use a three-color scheme (white, gray, black) to distinguish states.; For undirected graphs, a simple visited array and checking against the immediate parent is sufficient.
//   • Pitfalls: Incorrectly handling the parent edge in undirected graphs can lead to false cycle detections.; Failing to distinguish between nodes currently in the recursion stack (gray) and fully processed nodes (black) in directed graphs.
// - Finding articulation points in a graph in O(N+M) (graph, array, dfs)
//   • When to use: Use when identifying critical nodes whose removal would increase the number of connected components in an undirected graph. It's essential for analyzing network robustness and vulnerability.
//   • Idea: This algorithm finds all articulation points (cut vertices) in an undirected graph using a single Depth First Search traversal. It operates in linear time, O(N+M), where N is vertices and M is edges.
//   • Invariants: For any node `u`, `tin[u]` is its discovery time, and `low[u]` is initialized to `tin[u]`.; After visiting all children `v` of `u` (and their subtrees), `low[u]` will hold the minimum `tin` value reachable from `u` or its descendants via tree edges and at most one back-edge.
//   • Tips: Initialize `tin` (discovery time) and `low` (lowest reachable ancestor) arrays for all vertices.; The root of the DFS tree is an articulation point if it has more than one child in the DFS tree.
//   • Pitfalls: Forgetting to initialize `low[u]` with `tin[u]` before processing children.; Incorrectly applying the `tin[u] <= low[v]` condition to the root node of the DFS tree.
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
int* longestSpecialPath(int** edges, int edgesSize, int* edgesColSize, int* nums, int numsSize, int* returnSize) {
#include <stdlib.h>
#include <string.h>

	typedef struct {
		int u;
		int parent;
		int edgeWeightFromParent;
		int edgeIter;
		int phase;
		int depth;
		int value;
		int prevLastDepth;
		int prevWindowStart;
	} Frame;

	int n = numsSize;
	int m = edgesSize * 2;
	int* head = (int*)malloc((size_t)n * sizeof(int));
	int* to = (int*)malloc((size_t)m * sizeof(int));
	int* w = (int*)malloc((size_t)m * sizeof(int));
	int* next = (int*)malloc((size_t)m * sizeof(int));
	int* dist = (int*)malloc((size_t)n * sizeof(int));
	Frame* stack = (Frame*)malloc((size_t)n * sizeof(Frame));
	int* lastDepth = (int*)malloc(50001u * sizeof(int));
	int* result = (int*)malloc(2u * sizeof(int));
	int i;
	int idx = 0;
	int top = 0;
	int pathLen = 0;
	int windowStart = 0;
	long long bestLen = -1;
	int bestNodes = 0;

	(void)edgesColSize;

	if (!head || !to || !w || !next || !dist || !stack || !lastDepth || !result) {
		free(head);
		free(to);
		free(w);
		free(next);
		free(dist);
		free(stack);
		free(lastDepth);
		free(result);
		*returnSize = 0;
		return NULL;
	}

	for (i = 0; i < n; ++i) {
		head[i] = -1;
	}
	for (i = 0; i < 50001; ++i) {
		lastDepth[i] = -1;
	}

	for (i = 0; i < edgesSize; ++i) {
		int u = edges[i][0];
		int v = edges[i][1];
		int len = edges[i][2];

		to[idx] = v;
		w[idx] = len;
		next[idx] = head[u];
		head[u] = idx;
		++idx;

		to[idx] = u;
		w[idx] = len;
		next[idx] = head[v];
		head[v] = idx;
		++idx;
	}

	stack[top].u = 0;
	stack[top].parent = -1;
	stack[top].edgeWeightFromParent = 0;
	stack[top].edgeIter = -1;
	stack[top].phase = 0;
	stack[top].depth = 0;
	stack[top].value = 0;
	stack[top].prevLastDepth = -1;
	stack[top].prevWindowStart = 0;
	++top;

	while (top > 0) {
		Frame* cur = &stack[top - 1];

		if (cur->phase == 0) {
			long long currLen;
			int currNodes;

			cur->phase = 1;
			cur->depth = pathLen;
			if (cur->depth == 0) {
				dist[cur->depth] = 0;
			} else {
				dist[cur->depth] = dist[cur->depth - 1] + cur->edgeWeightFromParent;
			}

			cur->value = nums[cur->u];
			cur->prevLastDepth = lastDepth[cur->value];
			cur->prevWindowStart = windowStart;

			if (cur->prevLastDepth + 1 > windowStart) {
				windowStart = cur->prevLastDepth + 1;
			}
			lastDepth[cur->value] = cur->depth;

			currLen = (long long)dist[cur->depth] - (long long)dist[windowStart];
			currNodes = cur->depth - windowStart + 1;
			if (currLen > bestLen) {
				bestLen = currLen;
				bestNodes = currNodes;
			} else if (currLen == bestLen && currNodes < bestNodes) {
				bestNodes = currNodes;
			}

			++pathLen;
			cur->edgeIter = head[cur->u];
			continue;
		}

		while (cur->edgeIter != -1 && to[cur->edgeIter] == cur->parent) {
			cur->edgeIter = next[cur->edgeIter];
		}

		if (cur->edgeIter == -1) {
			--pathLen;
			lastDepth[cur->value] = cur->prevLastDepth;
			windowStart = cur->prevWindowStart;
			--top;
		} else {
			int e = cur->edgeIter;
			int v = to[e];
			int edgeLen = w[e];

			cur->edgeIter = next[e];

			stack[top].u = v;
			stack[top].parent = cur->u;
			stack[top].edgeWeightFromParent = edgeLen;
			stack[top].edgeIter = -1;
			stack[top].phase = 0;
			stack[top].depth = 0;
			stack[top].value = 0;
			stack[top].prevLastDepth = -1;
			stack[top].prevWindowStart = 0;
			++top;
		}
	}

	result[0] = (int)bestLen;
	result[1] = bestNodes;
	*returnSize = 2;

	free(head);
	free(to);
	free(w);
	free(next);
	free(dist);
	free(stack);
	free(lastDepth);

	return result;
}