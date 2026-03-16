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
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double frogPosition(int n, int** edges, int edgesSize, int* edgesColSize, int t, int target) {
    // Create an adjacency list for the tree
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
    
    // BFS to find the probability of being on the target vertex after t seconds
    double probability[n + 1];
    for (int i = 0; i <= n; i++) {
        probability[i] = 0.0;
    }
    
    probability[1] = 1.0; // Start at vertex 1
    
    for (int time = 0; time < t; time++) {
        double nextProbability[n + 1];
        for (int i = 0; i <= n; i++) {
            nextProbability[i] = 0.0;
        }
        
        for (int vertex = 1; vertex <= n; vertex++) {
            if (probability[vertex] > 0) {
                int unvisitedCount = degree[vertex];
                if (unvisitedCount == 0) {
                    nextProbability[vertex] += probability[vertex]; // Stay on the same vertex
                } else {
                    double jumpProbability = probability[vertex] / unvisitedCount;
                    for (int j = 0; j < degree[vertex]; j++) {
                        int nextVertex = adj[vertex][j];
                        nextProbability[nextVertex] += jumpProbability;
                    }
                }
            }
        }
        
        // Update probabilities for the next iteration
        for (int i = 0; i <= n; i++) {
            probability[i] = nextProbability[i];
        }
    }
    
    return probability[target];     
}
