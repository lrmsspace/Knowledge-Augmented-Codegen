// Source: https://leetcode.com/problems/shortest-path-in-a-weighted-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 1 with n nodes numbered from 1 to n. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an undirected edge from node ui to vi with weight wi.
//
// You are also given a 2D integer array queries of length q, where each queries[i] is either:
//
//
// 	[1, u, v, w'] – Update the weight of the edge between nodes u and v to w', where (u, v) is guaranteed to be an edge present in edges.
// 	[2, x] – Compute the shortest path distance from the root node 1 to node x.
//
//
// Return an integer array answer, where answer[i] is the shortest path distance from node 1 to x for the ith query of [2, x].
//
// Example:
// Input: n = 2, edges = [[1,2,7]], queries = [[2,2],[1,1,2,4],[2,2]]
//
// Output: [7,4]
//
// Explanation:
//
//
//
//
// 	Query [2,2]: The shortest path from root node 1 to node 2 is 7.
// 	Query [1,1,2,4]: The weight of edge (1,2) changes from 7 to 4.
// 	Query [2,2]: The shortest path from root node 1 to node 2 is 4.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	1 <= ui, vi <= n
// 	1 <= wi <= 104
// 	The input is generated such that edges represents a valid tree.
// 	1 <= queries.length == q <= 105
// 	queries[i].length == 2 or 4
// 	
// 		queries[i] == [1, u, v, w'] or,
// 		queries[i] == [2, x]
// 		1 <= u, v, x <= n
// 		(u, v) is always an edge from edges.
// 		1 <= w' <= 104
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
//   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
//   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
//   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
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

// DFS to calculate distance from root (node 1) to target node
long long dfs(int node, int parent, int target, int** adj, int* adjSize, int** weights) {
    if (node == target) {
        return 0;
    }
    
    for (int i = 0; i < adjSize[node]; i++) {
        int neighbor = adj[node][i];
        if (neighbor != parent) {
            long long dist = dfs(neighbor, node, target, adj, adjSize, weights);
            if (dist != -1) {
                // Find the edge weight between node and neighbor
                for (int j = 0; j < adjSize[node]; j++) {
                    if (adj[node][j] == neighbor) {
                        return dist + weights[node][j];
                    }
                }
            }
        }
    }
    
    return -1;
}

int* treeQueries(int n, int** edges, int edgesSize, int* edgesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Create adjacency list and weight matrix
    int** adj = (int**)malloc((n + 1) * sizeof(int*));
    int** weights = (int**)malloc((n + 1) * sizeof(int*));
    int* adjSize = (int*)malloc((n + 1) * sizeof(int));
    
    for (int i = 1; i <= n; i++) {
        adj[i] = (int*)malloc(n * sizeof(int));
        weights[i] = (int*)malloc(n * sizeof(int));
        adjSize[i] = 0;
    }
    
    // Store edge information for quick weight lookup
    int** edgeMap = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 1; i <= n; i++) {
        edgeMap[i] = (int*)malloc((n + 1) * sizeof(int));
        for (int j = 1; j <= n; j++) {
            edgeMap[i][j] = 0;
        }
    }
    
    // Build the tree from edges
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        
        adj[u][adjSize[u]] = v;
        weights[u][adjSize[u]] = w;
        adjSize[u]++;
        
        adj[v][adjSize[v]] = u;
        weights[v][adjSize[v]] = w;
        adjSize[v]++;
        
        edgeMap[u][v] = w;
        edgeMap[v][u] = w;
    }
    
    // Process queries
    int* result = (int*)malloc(queriesSize * sizeof(int));
    int resultIdx = 0;
    
    for (int i = 0; i < queriesSize; i++) {
        if (queries[i][0] == 1) {
            // Update edge weight
            int u = queries[i][1];
            int v = queries[i][2];
            int newWeight = queries[i][3];
            
            // Update edgeMap
            edgeMap[u][v] = newWeight;
            edgeMap[v][u] = newWeight;
            
            // Update adjacency list weights
            for (int j = 0; j < adjSize[u]; j++) {
                if (adj[u][j] == v) {
                    weights[u][j] = newWeight;
                }
            }
            for (int j = 0; j < adjSize[v]; j++) {
                if (adj[v][j] == u) {
                    weights[v][j] = newWeight;
                }
            }
        } else {
            // Query shortest path from root (1) to x
            int x = queries[i][1];
            long long dist = 0;
            
            if (x != 1) {
                // BFS/DFS from node 1 to find path to x
                int* parent = (int*)malloc((n + 1) * sizeof(int));
                long long* distance = (long long*)malloc((n + 1) * sizeof(long long));
                
                for (int j = 1; j <= n; j++) {
                    distance[j] = -1;
                    parent[j] = -1;
                }
                
                // BFS to find path
                int* queue = (int*)malloc((n + 1) * sizeof(int));
                int front = 0, rear = 0;
                queue[rear++] = 1;
                distance[1] = 0;
                
                while (front < rear && distance[x] == -1) {
                    int node = queue[front++];
                    
                    for (int j = 0; j < adjSize[node]; j++) {
                        int neighbor = adj[node][j];
                        if (distance[neighbor] == -1) {
                            distance[neighbor] = distance[node] + weights[node][j];
                            parent[neighbor] = node;
                            queue[rear++] = neighbor;
                        }
                    }
                }
                
                dist = distance[x];
                
                free(parent);
                free(distance);
                free(queue);
            }
            
            result[resultIdx++] = (int)dist;
        }
    }
    
    // Free memory
    for (int i = 1; i <= n; i++) {
        free(adj[i]);
        free(weights[i]);
        free(edgeMap[i]);
    }
    free(adj);
    free(weights);
    free(adjSize);
    free(edgeMap);
    
    *returnSize = resultIdx;
    return result;
}
