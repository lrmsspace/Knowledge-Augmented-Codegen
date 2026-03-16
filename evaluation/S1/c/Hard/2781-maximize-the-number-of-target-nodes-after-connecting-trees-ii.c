// Source: https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/   |   Difficulty: Hard
//
// Problem Description:
// There exist two undirected trees with n and m nodes, labeled from [0, n - 1] and [0, m - 1], respectively.
//
// You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.
//
// Node u is target to node v if the number of edges on the path from u to v is even. Note that a node is always target to itself.
//
// Return an array of n integers answer, where answer[i] is the maximum possible number of nodes that are target to node i of the first tree if you had to connect one node from the first tree to another node in the second tree.
//
// Note that queries are independent from each other. That is, for every query you will remove the added edge before proceeding to the next query.
//
// Example:
// Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]
//
// Output: [8,7,7,8,8]
//
// Explanation:
//
//
// 	For i = 0, connect node 0 from the first tree to node 0 from the second tree.
// 	For i = 1, connect node 1 from the first tree to node 4 from the second tree.
// 	For i = 2, connect node 2 from the first tree to node 7 from the second tree.
// 	For i = 3, connect node 3 from the first tree to node 0 from the second tree.
// 	For i = 4, connect node 4 from the first tree to node 4 from the second tree.
//
// Constraints:
// 2 <= n, m <= 105
// 	edges1.length == n - 1
// 	edges2.length == m - 1
// 	edges1[i].length == edges2[i].length == 2
// 	edges1[i] = [ai, bi]
// 	0 <= ai, bi < n
// 	edges2[i] = [ui, vi]
// 	0 <= ui, vi < m
// 	The input is generated such that edges1 and edges2 represent valid trees.
//
// Helpful references (internal KB):
// - Check whether a graph is bipartite (graph, queue, bfs)
//   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
//   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
//   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
//   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
//   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, lca)
//   • When to use: Use this technique for efficiently answering multiple Range Minimum Queries on a static array, especially when an asymptotically optimal O(1) query time solution is required.
//   • Idea: This algorithm solves the static Range Minimum Query problem by first constructing a Cartesian tree from the input array, then reducing RMQ queries to Lowest Common Ancestor queries on this tree. It achieves an optimal O(N) preprocessing time and O(1) query time.
//   • Invariants: For any node `u` in the Cartesian tree, `value(u)` is the minimum among all values in the original array segment represented by `u`'s subtree.; The in-order traversal of the Cartesian tree nodes' original array indices yields the original array `A`'s indices in increasing order.
//   • Tips: Construct the Cartesian tree efficiently in O(N) time, typically using a stack-based approach.; The value of the LCA of two nodes in the Cartesian tree corresponds to the minimum in the original array range between their indices.
//   • Pitfalls: Incorrectly building the Cartesian tree, especially when handling duplicate values or edge cases like empty arrays.; The Farach-Colton and Bender LCA algorithm is complex to implement and often requires significant effort.
// - Minimum Spanning Trees (graph, greedy)
//   • When to use: When you need to find a subset of edges in a connected, edge-weighted graph that connects all vertices with the minimum possible total edge weight. Useful for network design problems where minimizing connection costs is crucial.
//   • Idea: A Minimum Spanning Tree (MST) algorithm finds a subset of edges in an edge-weighted graph that connects all vertices with the minimum possible total weight, forming a tree. This is typically solved using greedy approaches with a time complexity often involving sorting edges or using a priority queue.
//   • Invariants: The set of edges selected so far always forms a forest.; Each connected component formed by the chosen edges is a valid subtree of some Minimum Spanning Tree.
//   • Tips: Greedy approaches often work by iteratively adding the cheapest valid edge or expanding from a starting vertex.; The cut property and cycle property are fundamental for proving correctness of MST algorithms.
//   • Pitfalls: Assuming the graph is always connected; disconnected graphs require finding a minimum spanning forest.; Incorrectly applying the greedy choice without ensuring it maintains the MST property (e.g., creating a cycle).
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
int* maxTargetNodes(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size, int* edges2ColSize, int* returnSize) {
    int n = edges1Size + 1;
    int m = edges2Size + 1;

    // Build adjacency lists for both trees
    int **adj1 = (int**)malloc(n * sizeof(int*));
    int *adj1Sizes = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) adj1[i] = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < edges1Size; i++) {
        int u = edges1[i][0], v = edges1[i][1];
        adj1[u][adj1Sizes[u]++] = v;
        adj1[v][adj1Sizes[v]++] = u;
    }

    int **adj2 = (int**)malloc(m * sizeof(int*));
    int *adj2Sizes = (int*)calloc(m, sizeof(int));
    for (int i = 0; i < m; i++) adj2[i] = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < edges2Size; i++) {
        int u = edges2[i][0], v = edges2[i][1];
        adj2[u][adj2Sizes[u]++] = v;
        adj2[v][adj2Sizes[v]++] = u;
    }

    // BFS to find bipartite sets and their sizes
    int *color1 = (int*)calloc(n, sizeof(int));
    int count1[2] = {0, 0};
    int queue[n], front, back;

    front = back = 0;
    queue[back++] = 0;
    color1[0] = 1;
    count1[1]++;
    while (front < back) {
        int u = queue[front++];
        for (int i = 0; i < adj1Sizes[u]; i++) {
            int v = adj1[u][i];
            if (color1[v] == 0) {
                color1[v] = 3 - color1[u];
                count1[color1[v]]++;
                queue[back++] = v;
            }
        }
    }

    int *color2 = (int*)calloc(m, sizeof(int));
    int count2[2] = {0, 0};

    front = back = 0;
    queue[back++] = 0;
    color2[0] = 1;
    count2[1]++;
    while (front < back) {
        int u = queue[front++];
        for (int i = 0; i < adj2Sizes[u]; i++) {
            int v = adj2[u][i];
            if (color2[v] == 0) {
                color2[v] = 3 - color2[u];
                count2[color2[v]]++;
                queue[back++] = v;
            }
        }
    }
    // Calculate result for each node in the first tree
    int *result = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (color1[i] == 1) {
            result[i] = count1[1] + count2[1];
        } else {
            result[i] = count1[0] + count2[0];
        }
    }
    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(adj1[i]);
    }
    free(adj1);
    free(adj1Sizes);
    for (int i = 0; i < m; i++) {
        free(adj2[i]);
    }
    free(adj2);
    free(adj2Sizes);
    free(color1);
    free(color2);
    *returnSize = n;
    return result;
}
