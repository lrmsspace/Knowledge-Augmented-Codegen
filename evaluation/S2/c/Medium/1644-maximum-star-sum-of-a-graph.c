// Source: https://leetcode.com/problems/maximum-star-sum-of-a-graph/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected graph consisting of n nodes numbered from 0 to n - 1. You are given a 0-indexed integer array vals of length n where vals[i] denotes the value of the ith node.
//
// You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// A star graph is a subgraph of the given graph having a center node containing 0 or more neighbors. In other words, it is a subset of edges of the given graph such that there exists a common node for all edges.
//
// The image below shows star graphs with 3 and 4 neighbors respectively, centered at the blue node.
//
// The star sum is the sum of the values of all the nodes present in the star graph.
//
// Given an integer k, return the maximum star sum of a star graph containing at most k edges.
//
// Example:
// Input: vals = [1,2,3,4,10,-10,-20], edges = [[0,1],[1,2],[1,3],[3,4],[3,5],[3,6]], k = 2
// Output: 16
// Explanation: The above diagram represents the input graph.
// The star graph with the maximum star sum is denoted by blue. It is centered at 3 and includes its neighbors 1 and 4.
// It can be shown it is not possible to get a star graph with a sum greater than 16.
//
// Constraints:
// n == vals.length
// 	1 <= n <= 105
// 	-104 <= vals[i] <= 104
// 	0 <= edges.length <= min(n * (n - 1) / 2, 105)
// 	edges[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	0 <= k <= n - 1
//
// Helpful references (internal KB):
// - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
//   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
//   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
//   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
//   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
//   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting items, each with a weight and value, to maximize total value within a limited capacity, where each item can be chosen multiple times. It is suitable for problems exhibiting optimal substructure and overlapping subproblems.
//   • Idea: The Knapsack Problem involves selecting items to maximize total value within a fixed capacity. The complete knapsack variant, where items can be taken multiple times, is typically solved using dynamic programming in O(nW) time and O(W) space.
//   • Invariants: For 2D DP `f[i][j]`, it represents the maximum value obtainable using only the first `i` items with a total weight not exceeding `j`.; For 1D DP `dp[j]`, after processing item `i`, it stores the maximum value obtainable with a total weight not exceeding `j`, considering all items up to `i`.
//   • Tips: For the complete knapsack, iterate capacity `j` forwards (from `w_i` to `W`) when using 1D DP to allow multiple selections of the current item.; The 1D DP array `dp[j]` stores the maximum value achievable for exactly capacity `j`.
//   • Pitfalls: Confusing 0-1 knapsack with complete knapsack, especially in the 1D DP iteration direction for capacity.; Incorrectly initializing the DP array, leading to incorrect base cases or propagation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxStarSum(int* vals, int valsSize, int** edges, int edgesSize, int* edgesColSize, int k) {
    // Step 1: Build the adjacency list for the graph
    int** adjList = (int**)malloc(valsSize * sizeof(int*));
    int* adjListSizes = (int*)calloc(valsSize, sizeof(int));
    for (int i = 0; i < valsSize; i++) {
        adjList[i] = (int*)malloc(valsSize * sizeof(int)); // Allocate maximum possible size
    }
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adjList[u][adjListSizes[u]++] = v;
        adjList[v][adjListSizes[v]++] = u;
    }
    
    // Step 2: Calculate the star sum for each node
    int maxStarSum = INT_MIN;
    
    for (int i = 0; i < valsSize; i++) {
        // Get the values of the neighbors
        int* neighborVals = (int*)malloc(adjListSizes[i] * sizeof(int));
        for (int j = 0; j < adjListSizes[i]; j++) {
            neighborVals[j] = vals[adjList[i][j]];
        }
        
        // Sort the neighbor values in descending order
        qsort(neighborVals, adjListSizes[i], sizeof(int), cmp);
        
        // Calculate the star sum with at most k neighbors
        int currentStarSum = vals[i]; // Start with the center node value
        for (int j = 0; j < adjListSizes[i] && j < k; j++) {
            if (neighborVals[j] > 0) { // Only add positive values
                currentStarSum += neighborVals[j];
            } else {
                break; // No need to add negative values
            }
        }
        
        if (currentStarSum > maxStarSum) {
            maxStarSum = currentStarSum;
        }
        
        free(neighborVals);
    }
    
    // Free allocated memory
    for (int i = 0; i < valsSize; i++) {
        free(adjList[i]);
    }
    free(adjList);
    free(adjListSizes);
    
    return maxStarSum;      
}
