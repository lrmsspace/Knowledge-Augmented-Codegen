// Source: https://leetcode.com/problems/minimum-increments-to-equalize-leaf-paths/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n and an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi] indicates an edge from node ui to vi .
//
// Each node i has an associated cost given by cost[i], representing the cost to traverse that node.
//
// The score of a path is defined as the sum of the costs of all nodes along the path.
//
// Your goal is to make the scores of all root-to-leaf paths equal by increasing the cost of any number of nodes by any non-negative amount.
//
// Return the minimum number of nodes whose cost must be increased to make all root-to-leaf path scores equal.
//
// Example:
// Input: n = 3, edges = [[0,1],[0,2]], cost = [2,1,3]
//
// Output: 1
//
// Explanation:
//
//
//
// There are two root-to-leaf paths:
//
//
// 	Path 0 → 1 has a score of 2 + 1 = 3.
// 	Path 0 → 2 has a score of 2 + 3 = 5.
//
//
// To make all root-to-leaf path scores equal to 5, increase the cost of node 1 by 2.
// Only one node is increased, so the output is 1.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi]
// 	0 <= ui, vi < n
// 	cost.length == n
// 	1 <= cost[i] <= 109
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
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

int minIncrease(int n, int** edges, int edgesSize, int* edgesColSize, int* cost, int costSize) {
    // Build adjacency list
    int** adj = (int**)malloc(n * sizeof(int*));
    int* adjSizes = (int*)calloc(n, sizeof(int));
    int* adjCaps = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        adj[i] = (int*)malloc(4 * sizeof(int));
        adjCaps[i] = 4;
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        if (adjSizes[u] == adjCaps[u]) {
            adjCaps[u] *= 2;
            adj[u] = (int*)realloc(adj[u], adjCaps[u] * sizeof(int));
        }
        adj[u][adjSizes[u]++] = v;
        if (adjSizes[v] == adjCaps[v]) {
            adjCaps[v] *= 2;
            adj[v] = (int*)realloc(adj[v], adjCaps[v] * sizeof(int));
        }
        adj[v][adjSizes[v]++] = u;
    }

    // DFS to calculate increments
    int result = 0;
    long long maxPathSum = 0;

    long long* pathSums = (long long*)calloc(n, sizeof(long long));

    void dfs(int node, int parent) {
        if (adjSizes[node] == 1 && parent != -1) { // Leaf node
            pathSums[node] = cost[node];
            if (pathSums[node] > maxPathSum) {
                maxPathSum = pathSums[node];
            }
            return;
        }
        long long totalChildPathSum = 0;
        for (int i = 0; i < adjSizes[node]; i++) {
            int neighbor = adj[node][i];
            if (neighbor != parent) {
                dfs(neighbor, node);
                totalChildPathSum += pathSums[neighbor];
            }
        }
        pathSums[node] = totalChildPathSum + cost[node];
        if (pathSums[node] > maxPathSum) {
            maxPathSum = pathSums[node];
        }
    }

    dfs(0, -1);

    void calculateIncrements(int node, int parent) {
        if (adjSizes[node] == 1 && parent != -1) { // Leaf node
            return;
        }
        long long maxChildPathSum = 0;
        for (int i = 0; i < adjSizes[node]; i++) {
            int neighbor = adj[node][i];
            if (neighbor != parent) {
                if (pathSums[neighbor] > maxChildPathSum) {
                    maxChildPathSum = pathSums[neighbor];
                }
            }
        }
        for (int i = 0; i < adjSizes[node]; i++) {
            int neighbor = adj[node][i];
            if (neighbor != parent) {
                result += maxChildPathSum - pathSums[neighbor];
                calculateIncrements(neighbor, node);
            }
        }
    }

    calculateIncrements(0, -1);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);
    free(adjCaps);
    free(pathSums);

    return result;
}