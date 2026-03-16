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
// - Breadth-first search (graph, array, bfs)
//   • When to use: Use when finding the shortest path or minimum number of edges between nodes in an unweighted graph, or to explore a graph layer by layer. It is also suitable for finding shortest cycles or identifying all components of shortest paths.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring the shortest path in terms of edges is found from a source node to all reachable nodes. It operates in O(V + E) time complexity for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at depth `k` or `k+1` from the source.; The distance recorded for any visited node is its shortest path length from the source.
//   • Tips: Run multiple BFS from different sources to find global properties like shortest cycles.; Maintain a distance array to record the shortest path length from the source to each node.
//   • Pitfalls: Applying BFS directly to weighted graphs will not yield shortest paths.; Failing to mark visited nodes can lead to infinite loops in cyclic graphs or incorrect path lengths.
// - Minimum Spanning Trees (graph, greedy)
//   • When to use: When you need to find a subset of edges in a connected, edge-weighted graph that connects all vertices with the minimum possible total edge weight. Useful for network design problems where minimizing connection costs is crucial.
//   • Idea: A Minimum Spanning Tree (MST) algorithm finds a subset of edges in an edge-weighted graph that connects all vertices with the minimum possible total weight, forming a tree. This is typically solved using greedy approaches with a time complexity often involving sorting edges or using a priority queue.
//   • Invariants: The set of edges selected so far always forms a forest.; Each connected component formed by the chosen edges is a valid subtree of some Minimum Spanning Tree.
//   • Tips: Greedy approaches often work by iteratively adding the cheapest valid edge or expanding from a starting vertex.; The cut property and cycle property are fundamental for proving correctness of MST algorithms.
//   • Pitfalls: Assuming the graph is always connected; disconnected graphs require finding a minimum spanning forest.; Incorrectly applying the greedy choice without ensuring it maintains the MST property (e.g., creating a cycle).
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
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
int* maxTargetNodes(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size, int* edges2ColSize, int k, int* returnSize) {
    int n = edges1Size + 1;
    int m = edges2Size + 1;
    *returnSize = n;
    int* result = (int*)malloc(n * sizeof(int));

    // Build adjacency list for tree1
    int** adj1 = (int**)malloc(n * sizeof(int*));
    int* size1 = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        adj1[i] = (int*)malloc((n - 1) * sizeof(int));
    }
    for (int i = 0; i < edges1Size; i++) {
        int u = edges1[i][0];
        int v = edges1[i][1];
        adj1[u][size1[u]++] = v;
        adj1[v][size1[v]++] = u;
    }

    // Build adjacency list for tree2
    int** adj2 = (int**)malloc(m * sizeof(int*));
    int* size2 = (int*)calloc(m, sizeof(int));
    for (int i = 0; i < m; i++) {
        adj2[i] = (int*)malloc((m - 1) * sizeof(int));
    }
    for (int i = 0; i < edges2Size; i++) {
        int u = edges2[i][0];
        int v = edges2[i][1];
        adj2[u][size2[u]++] = v;
        adj2[v][size2[v]++] = u;
    }

    // Precompute distances in tree2 using BFS
    int** dist2 = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        dist2[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            dist2[i][j] = -1;
        }
        // BFS from node i
        int* queue = (int*)malloc(m * sizeof(int));
        int front = 0, back = 0;
        queue[back++] = i;
        dist2[i][i] = 0;
        while (front < back) {
            int curr = queue[front++];
            for (int j = 0; j < size2[curr]; j++) {
                int neighbor = adj2[curr][j];
                if (dist2[i][neighbor] == -1) {
                    dist2[i][neighbor] = dist2[i][curr] + 1;
                    queue[back++] = neighbor;
                }
            }
        }
        free(queue);
    }
    // For each node in tree1, find max target nodes after connecting to tree2
    for (int i = 0; i < n; i++) {
        // BFS in tree1 from node i
        int* dist1 = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            dist1[j] = -1;
        }
        int* queue = (int*)malloc(n * sizeof(int));
        int front = 0, back = 0;
        queue[back++] = i;
        dist1[i] = 0;
        while (front < back) {
            int curr = queue[front++];
            for (int j = 0; j < size1[curr]; j++) {
                int neighbor = adj1[curr][j];
                if (dist1[neighbor] == -1) {
                    dist1[neighbor] = dist1[curr] + 1;
                    queue[back++] = neighbor;
                }
            }
        }

        // Count target nodes
        int maxTargets = 0;
        for (int j = 0; j < m; j++) {
            int targets = 0;
            for (int u = 0; u < n; u++) {
                if (dist1[u] != -1 && dist1[u] + dist2[j][u % m] <= k) {
                    targets++;
                }
            }
            if (targets > maxTargets) {
                maxTargets = targets;
            }
        }
        result[i] = maxTargets;

        free(dist1);
        free(queue);
    }
    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(adj1[i]);
    }
    free(adj1);
    free(size1);
    for (int i = 0; i < m; i++) {
        free(adj2[i]);
    }
    free(adj2);
    free(size2);
    for (int i = 0; i < m; i++) {
        free(dist2[i]);
    }
    free(dist2);
    return result;
}
