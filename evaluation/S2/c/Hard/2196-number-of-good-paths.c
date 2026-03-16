// Source: https://leetcode.com/problems/number-of-good-paths/   |   Difficulty: Hard
//
// Problem Description:
// There is a tree (i.e. a connected, undirected graph with no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges.
//
// You are given a 0-indexed integer array vals of length n where vals[i] denotes the value of the ith node. You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// A good path is a simple path that satisfies the following conditions:
//
//
// 	The starting node and the ending node have the same value.
// 	All nodes between the starting node and the ending node have values less than or equal to the starting node (i.e. the starting node's value should be the maximum value along the path).
//
//
// Return the number of distinct good paths.
//
// Note that a path and its reverse are counted as the same path. For example, 0 -> 1 is considered to be the same as 1 -> 0. A single node is also considered as a valid path.
//
// Example:
// Input: vals = [1,3,2,1,3], edges = [[0,1],[0,2],[2,3],[2,4]]
// Output: 6
// Explanation: There are 5 good paths consisting of a single node.
// There is 1 additional good path: 1 -> 0 -> 2 -> 4.
// (The reverse path 4 -> 2 -> 0 -> 1 is treated as the same as 1 -> 0 -> 2 -> 4.)
// Note that 0 -> 2 -> 3 is not a good path because vals[2] > vals[0].
//
// Constraints:
// n == vals.length
// 	1 <= n <= 3 * 104
// 	0 <= vals[i] <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	edges represents a valid tree.
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
//   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
//   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
//   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
//   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
//   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numberOfGoodPaths(int* vals, int valsSize, int** edges, int edgesSize, int* edgesColSize) {
	(void)edgesColSize;

	int n = valsSize;

	if (n == 0) {
		return 0;
	}

	// To be implemented: The algorithm to solve the problem will go here.

	int* head = (int*)malloc(n * sizeof(int));
	int* to = (int*)malloc(2 * (n - 1) * sizeof(int));
	int* next = (int*)malloc(2 * (n - 1) * sizeof(int));
	int* parent = (int*)malloc(n * sizeof(int));
	int* order = (int*)malloc(n * sizeof(int));
	int* stack = (int*)malloc(n * sizeof(int));
	long long* down = (long long*)malloc(n * sizeof(long long));
	long long* up = (long long*)malloc(n * sizeof(long long));

	int edgePtr = 0;
	int i;

	if (n == 1) {
            long long ans = 1;
            for (i = 0; i < n; ++i) {
                ans += (long long)vals[i] * (vals[i] - 1) / 2;
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

        if (edgesSize == 0) {
            long long ans = n;
            for (i = 0; i < n; ++i) {
                ans += (long long)vals[i] * (vals[i] - 1) / 2;
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

        if (edgesSize == 1) {
            long long ans = 1;
            for (i = 0; i < n; ++i) {
                ans += (long long)vals[i] * (vals[i] - 1) / 2;
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
        
        // Initialize adjacency list
        for (i = 0; i < n; ++i) {
            head[i] = -1;
        }

        // Build adjacency list from edges
        for (i = 0; i < edgesSize; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];
            to[edgePtr] = v;
            next[edgePtr] = head[u];
            head[u] = edgePtr++;
            to[edgePtr] = u;
            next[edgePtr] = head[v];
            head[v] = edgePtr++;
        }

        // Initialize parent array
        for (i = 0; i < n; ++i) {
            parent[i] = -1;
        }

        // DFS to build parent and order arrays
        int stackTop = 0;
        stack[stackTop++] = 0;
        int orderIndex = 0;

        while (stackTop > 0) {
            int current = stack[--stackTop];
            order[orderIndex++] = current;

            for (int e = head[current]; e != -1; e = next[e]) {
                int neighbor = to[e];
                if (parent[current] != neighbor) {
                    parent[neighbor] = current;
                    stack[stackTop++] = neighbor;
                }
            }
        }

        // Initialize down and up arrays
        for (i = 0; i < n; ++i) {
            down[i] = 1;
            up[i] = 1;
        }

        long long result = n;

        // Process nodes in reverse order of DFS traversal
        for (int j = orderIndex - 1; j >= 0; --j) {
            int current_node_index_in_order_array = order[j];
            
            long long count_of_current_node_value_in_subtree_downwards_from_current_node =
                down[current_node_index_in_order_array];

            long long count_of_current_node_value_in_subtree_upwards_from_current_node =
                up[current_node_index_in_order_array];

            result += count_of_current_node_value_in_subtree_downwards_from_current_node *
                      count_of_current_node_value_in_subtree_upwards_from_current_node;

            if (parent[current_node_index_in_order_array] != -1) {
                int parent_index =
                    parent[current_node_index_in_order_array];

                if (vals[parent_index] == vals[current_node_index_in_order_array]) {
                    down[parent_index] += down[current_node_index_in_order_array];
                    up[parent_index] += up[current_node_index_in_order_array];
                } else if (vals[parent_index] > vals[current_node_index_in_order_array]) {
                    up[parent_index]++;
                } else if (vals[parent_index] < vals[current_node_index_in_order_array]) {
                    down[parent_index]++;
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

    return result;
}