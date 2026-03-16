// Source: https://leetcode.com/problems/frog-position-after-t-seconds/   |   Difficulty: Hard
//
// Problem Description:
// Given an undirected tree consisting of n vertices numbered from 1 to n. A frog starts jumping from vertex 1. In one second, the frog jumps from its current vertex to another unvisited vertex if they are directly connected. The frog can not jump back to a visited vertex. In case the frog can jump to several vertices, it jumps randomly to one of them with the same probability. Otherwise, when the frog can not jump to any unvisited vertex, it jumps forever on the same vertex.
//
// The edges of the undirected tree are given in the array edges, where edges[i] = [ai, bi] means that exists an edge connecting the vertices ai and bi.
//
// Return the probability that after t seconds the frog is on the vertex target. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: n = 7, edges = [[1,2],[1,3],[1,7],[2,4],[2,6],[3,5]], t = 2, target = 4
// Output: 0.16666666666666666 
// Explanation: The figure above shows the given graph. The frog starts at vertex 1, jumping with 1/3 probability to the vertex 2 after second 1 and then jumping with 1/2 probability to vertex 4 after second 2. Thus the probability for the frog is on the vertex 4 after 2 seconds is 1/3 * 1/2 = 1/6 = 0.16666666666666666.
//
// Constraints:
// 1 <= n <= 100
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	1 <= t <= 50
// 	1 <= target <= n
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double frogPosition(int n, int** edges, int edgesSize, int* edgesColSize, int t, int target) {
    // Step 1: Build the adjacency list for the tree
    int adj[n + 1][n]; // Adjacency list (using a fixed-size array for simplicity)
    int degree[n + 1]; // Degree of each vertex
    for (int i = 0; i <= n; i++) {
        degree[i] = 0;
    }
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][degree[u]++] = v;
        adj[v][degree[v]++] = u;
    }

    // Step 2: Perform DFS to find the probability of being at target after t seconds
    double probability = 0.0;
    int visited[n + 1];
    for (int i = 0; i <= n; i++) {
        visited[i] = 0;
    }
    
    void dfs(int vertex, int time, double prob) {
        visited[vertex] = 1;

        if (time == t) {
            if (vertex == target) {
                probability += prob;
            }
            visited[vertex] = 0;
            return;
        }

        int unvisitedCount = degree[vertex];
        for (int i = 0; i < degree[vertex]; i++) {
            if (visited[adj[vertex][i]] == 0) {
                unvisitedCount--;
            }
        }

        if (unvisitedCount == 0) {
            if (vertex == target) {
                probability += prob;
            }
            visited[vertex] = 0;
            return;
        }

        for (int i = 0; i < degree[vertex]; i++) {
            if (visited[adj[vertex][i]] == 0) {
                dfs(adj[vertex][i], time + 1, prob / unvisitedCount);
            }
        }

        visited[vertex] = 0;
    }

    dfs(1, 0, 1.0); // Start DFS from vertex 1 with initial probability of 1

    return probability;     
}
