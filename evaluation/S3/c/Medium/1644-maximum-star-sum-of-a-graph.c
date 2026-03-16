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
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
// - Undirected Graphs (graph, matrix, simulation)
//   • When to use: Use when modeling symmetric relationships between entities, analyzing graph properties like connectivity or degrees, or simulating processes on a network where connections are bidirectional.
//   • Idea: An undirected graph consists of a set of vertices and a set of edges, where each edge connects two vertices symmetrically. Basic operations often have a time complexity of O(V+E) or O(V^2) depending on representation.
//   • Invariants: For every edge (u, v) in the graph, the edge (v, u) also exists.; The sum of degrees of all vertices equals twice the number of edges.
//   • Tips: Choose adjacency list for sparse graphs, adjacency matrix for dense graphs.; Degrees of vertices are easily calculated from adjacency representations.
//   • Pitfalls: Forgetting to add both (u,v) and (v,u) when using an adjacency matrix or list.; Not handling disconnected components during full graph traversals.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
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
        adjList[i] = (int*)malloc(valsSize * sizeof(int)); // Max possible neighbors
    }
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adjList[u][adjListSizes[u]++] = v;
        adjList[v][adjListSizes[v]++] = u;
    }
    
    // Step 2: Calculate the maximum star sum for each node
    int maxSum = INT_MIN;
    
    for (int i = 0; i < valsSize; i++) {
        // Create an array to store neighbor values
        int* neighborValues = (int*)malloc(adjListSizes[i] * sizeof(int));
        for (int j = 0; j < adjListSizes[i]; j++) {
            neighborValues[j] = vals[adjList[i][j]];
        }
        
        // Sort neighbor values in descending order
        qsort(neighborValues, adjListSizes[i], sizeof(int), cmp);
        
        // Calculate star sum for the current node
        int currentSum = vals[i];
        maxSum = fmax(maxSum, currentSum); // Star graph with only the center node
        
        for (int j = 0; j < fmin(k, adjListSizes[i]); j++) {
            currentSum += neighborValues[j];
            maxSum = fmax(maxSum, currentSum);
        }
        
        free(neighborValues);
    }
    
    // Free allocated memory
    for (int i = 0; i < valsSize; i++) {
        free(adjList[i]);
    }
    free(adjList);
    free(adjListSizes);
    
    return maxSum;      
}
