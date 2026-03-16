// Source: https://leetcode.com/problems/is-graph-bipartite/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected graph with n nodes, where each node is numbered between 0 and n - 1. You are given a 2D array graph, where graph[u] is an array of nodes that node u is adjacent to. More formally, for each v in graph[u], there is an undirected edge between node u and node v. The graph has the following properties:
//
//
// 	There are no self-edges (graph[u] does not contain u).
// 	There are no parallel edges (graph[u] does not contain duplicate values).
// 	If v is in graph[u], then u is in graph[v] (the graph is undirected).
// 	The graph may not be connected, meaning there may be two nodes u and v such that there is no path between them.
//
//
// A graph is bipartite if the nodes can be partitioned into two independent sets A and B such that every edge in the graph connects a node in set A and a node in set B.
//
// Return true if and only if it is bipartite.
//
// Example:
// Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
// Output: false
// Explanation: There is no way to partition the nodes into two independent sets such that every edge connects a node in one and a node in the other.
//
// Constraints:
// graph.length == n
// 	1 <= n <= 100
// 	0 <= graph[u].length < n
// 	0 <= graph[u][i] <= n - 1
// 	graph[u] does not contain u.
// 	All the values of graph[u] are unique.
// 	If graph[u] contains v, then graph[v] contains u.
//
// Helpful references (internal KB):
// - Check whether a graph is bipartite (graph, queue, bfs)
//   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
//   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
//   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
//   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
//   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    if (graphSize == 0) return true; // An empty graph is bipartite

    int* color = (int*)malloc(graphSize * sizeof(int));
    for (int i = 0; i < graphSize; i++) {
        color[i] = -1; // Initialize all vertices as uncolored
    }

    for (int i = 0; i < graphSize; i++) {
        if (color[i] == -1) { // If the vertex is uncolored
            color[i] = 0; // Start coloring with color 0
            int queue[graphSize]; // Queue for BFS
            int front = 0, rear = 0;
            queue[rear++] = i;

            while (front < rear) {
                int u = queue[front++]; // Dequeue a vertex

                for (int j = 0; j < graphColSize[u]; j++) {
                    int v = graph[u][j]; // Get adjacent vertex

                    if (color[v] == -1) { // If the adjacent vertex is uncolored
                        color[v] = 1 - color[u]; // Color with opposite color
                        queue[rear++] = v; // Enqueue the adjacent vertex
                    } else if (color[v] == color[u]) { // If the adjacent vertex is colored with the same color
                        free(color);
                        return false; // The graph is not bipartite
                    }
                }
            }
        }
    }

    free(color);
    return true; // The graph is bipartite      
}
