// Source: https://leetcode.com/problems/find-if-path-exists-in-graph/   |   Difficulty: Easy
//
// Problem Description:
// There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1 (inclusive). The edges in the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.
//
// You want to determine if there is a valid path that exists from vertex source to vertex destination.
//
// Given edges and the integers n, source, and destination, return true if there is a valid path from source to destination, or false otherwise.
//
// Example:
// Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
// Output: true
// Explanation: There are two paths from vertex 0 to vertex 2:
// - 0 → 1 → 2
// - 0 → 2
//
// Constraints:
// 1 <= n <= 2 * 105
// 	0 <= edges.length <= 2 * 105
// 	edges[i].length == 2
// 	0 <= ui, vi <= n - 1
// 	ui != vi
// 	0 <= source, destination <= n - 1
// 	There are no duplicate edges.
// 	There are no self edges.
//
// Helpful references (internal KB):
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
// - Shortest Paths (graph, queue, bellman-ford)
//   • When to use: Use when finding single-source shortest paths in edge-weighted digraphs that may contain negative edge weights, or to detect negative cycles. It can also be adapted for longest paths in DAGs.
//   • Idea: The Bellman-Ford algorithm solves the single-source shortest paths problem in edge-weighted digraphs, even with negative edge weights, or detects negative cycles. Its worst-case time complexity is O(V*E).
//   • Invariants: For any vertex v, distTo[v] is always an upper bound on the shortest path distance from the source s to v.; If distTo[v] is finite, there exists a path from s to v of length distTo[v].
//   • Tips: Use a queue-based optimization (SPFA) for better average-case performance.; It can detect the presence of negative cycles reachable from the source.
//   • Pitfalls: Shortest paths are undefined if a negative cycle is reachable from the source.; O(V*E) worst-case time complexity can be prohibitive for large, dense graphs.
// - Check whether a graph is bipartite (graph, queue, bfs)
//   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
//   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
//   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
//   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
//   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool validPath(int n, int** edges, int edgesSize, int* edgesColSize, int source, int destination) {
    // Build adjacency list
    int** graph = (int**)malloc(n * sizeof(int*));
    int* graphColSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int)); // Over-allocate, will resize later
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u][graphColSize[u]++] = v;
        graph[v][graphColSize[v]++] = u;
    }

    // BFS initialization
    bool* visited = (bool*)calloc(n, sizeof(bool));
    int* queue = (int*)malloc(n * sizeof(int));
    int front = 0, back = 0;

    // Start BFS from source
    queue[back++] = source;
    visited[source] = true;

    while (front < back) {
        int node = queue[front++];
        if (node == destination) {
            // Free allocated memory
            for (int i = 0; i < n; i++) {
                free(graph[i]);
            }
            free(graph);
            free(graphColSize);
            free(visited);
            free(queue);
            return true;
        }
        for (int i = 0; i < graphColSize[node]; i++) {
            int neighbor = graph[node][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue[back++] = neighbor;
            }
        }
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphColSize);
    free(visited);
    free(queue);

    return false;       
}
