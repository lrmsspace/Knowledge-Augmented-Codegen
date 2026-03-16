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
// - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
//   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
//   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
//   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
//   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
//   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
// - Finding Bridges Online (ds, tree, union-find, lca, rerooting)
//   • When to use: Use this algorithm to dynamically maintain bridges and 2-edge-connected components in a graph as edges are added. It efficiently processes edge additions by updating forest structures and compressing cycles.
//   • Idea: This algorithm dynamically maintains bridges and 2-edge-connected components using two DSU structures and a parent array for tree structure. Edge additions involve re-rooting smaller trees and compressing cycles via LCA, achieving amortized O(log N) per edge operation.
//   • Invariants: The par[] array always defines a forest structure where each tree corresponds to a connected component of 2-edge-connected components.; Each 2-edge-connected component is represented by a single canonical element in its dedicated DSU structure.
//   • Tips: Employ two DSU structures: one for connected components and another for 2-edge-connected components.; Optimize re-rooting operations by always re-rooting the smaller of the two trees being joined.
//   • Pitfalls: Failing to consistently update both DSU structures and the parent array after operations.; Incorrectly handling parent pointers during re-rooting, leading to broken tree structures.
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
    // Step 1: Build the adjacency list for the tree
    int n = numsSize;
    int** adj = (int**)malloc(n * sizeof(int*));
    int* adjSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        adj[i] = (int*)malloc(n * sizeof(int)); // Max possible size
    }
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int length = edges[i][2];
        adj[u][adjSize[u]++] = v;
        adj[v][adjSize[v]++] = u;
    }
    
    // Step 2: DFS to find longest special path
    int maxLength = 0;
    int minNodes = n; // Start with max possible nodes
    int* visited = (int*)calloc(n, sizeof(int));
    
    void dfs(int node, int currentLength, int currentNodes) {
        visited[node] = 1;
        
        if (currentLength > maxLength) {
            maxLength = currentLength;
            minNodes = currentNodes;
        } else if (currentLength == maxLength) {
            if (currentNodes < minNodes) {
                minNodes = currentNodes;
            }
        }
        
        for (int i = 0; i < adjSize[node]; i++) {
            int nextNode = adj[node][i];
            if (!visited[nextNode]) {
                dfs(nextNode, currentLength + 1, currentNodes + 1);
            }
        }
        
        visited[node] = 0; // Backtrack
    }
    
    dfs(0, 0, 1); // Start DFS from root node
    
    // Step 3: Prepare the result
    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = maxLength;
    result[1] = minNodes;
    
    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(adjSize);
    free(visited);
    
    *returnSize = 2;
    return result;      
}
