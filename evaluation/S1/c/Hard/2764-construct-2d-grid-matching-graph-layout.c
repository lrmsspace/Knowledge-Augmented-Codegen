// Source: https://leetcode.com/problems/construct-2d-grid-matching-graph-layout/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array edges representing an undirected graph having n nodes, where edges[i] = [ui, vi] denotes an edge between nodes ui and vi.
//
// Construct a 2D grid that satisfies these conditions:
//
//
// 	The grid contains all nodes from 0 to n - 1 in its cells, with each node appearing exactly once.
// 	Two nodes should be in adjacent grid cells (horizontally or vertically) if and only if there is an edge between them in edges.
//
//
// It is guaranteed that edges can form a 2D grid that satisfies the conditions.
//
// Return a 2D integer array satisfying the conditions above. If there are multiple solutions, return any of them.
//
// Example:
// Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]]
//
// Output: [[3,1],[2,0]]
//
// Explanation:
//
// Constraints:
// 2 <= n <= 5 * 104
// 	1 <= edges.length <= 105
// 	edges[i] = [ui, vi]
// 	0 <= ui < vi < n
// 	All the edges are distinct.
// 	The input is generated such that edges can form a 2D grid that satisfies the conditions.
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
// - Depth First Search (graph, dfs, topo)
//   • When to use: Use DFS to explore all reachable vertices from a starting point, find paths, detect cycles, or perform topological sorting on directed acyclic graphs.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically runs in O(V + E) time for graphs represented with adjacency lists, where V is the number of vertices and E is the number of edges.
//   • Invariants: Every node is visited at most once.; The `visited` set accurately reflects nodes currently in the recursion stack or fully explored.
//   • Tips: Always use a visited set to avoid infinite loops in cyclic graphs.; For topological sort, add nodes to a list after visiting all their neighbors.
//   • Pitfalls: Risk of stack overflow for very deep graphs or trees.; Failing to mark nodes as visited before recursive calls can lead to re-processing.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** constructGridLayout(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize, int** returnColumnSizes) {
    int rows = 0, cols = 0;
    for (int i = 1; i * i <= n; ++i) {
        if (i * (n / i) == n) {
            rows = i;
            cols = n / i;
        }
    }

    int** grid = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) {
        grid[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = -1;
        }
    }

    // Build adjacency list
    int** adj = (int**)malloc(n * sizeof(int*));
    int* adjSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        adj[i] = (int*)malloc(n * sizeof(int)); // worst case
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][adjSize[u]++] = v;
        adj[v][adjSize[v]++] = u;
    }

    // BFS to fill the grid
    int* queue = (int*)malloc(n * sizeof(int));
    int front = 0, back = 0;
    int* visited = (int*)calloc(n, sizeof(int));
    queue[back++] = 0;
    visited[0] = 1;

    int r = 0, c = 0;
    while (front < back) {
        int node = queue[front++];
        grid[r][c] = node;
        c++;
        if (c == cols) {
            c = 0;
            r++;
        }
        for (int i = 0; i < adjSize[node]; ++i) {
            int neighbor = adj[node][i];
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                queue[back++] = neighbor;
            }
        }
    }

    // Free adjacency list
    for (int i = 0; i < n; ++i) {
        free(adj[i]);
    }
    free(adj);
    free(adjSize);
    free(queue);    
    free(visited);
    *returnSize = rows;
    *returnColumnSizes = (int*)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; ++i) {
        (*returnColumnSizes)[i] = cols;
    }   
    return grid;    
}
