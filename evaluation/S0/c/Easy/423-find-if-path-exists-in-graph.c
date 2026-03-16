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

bool validPath(int n, int** edges, int edgesSize, int* edgesColSize, int source, int destination) {
    if (source == destination) {
        return true;
    }

    // Build adjacency list
    int** graph = (int**)malloc(n * sizeof(int*));
    int* graphSizes = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u][graphSizes[u]++] = v;
        graph[v][graphSizes[v]++] = u;
    }

    // BFS
    bool* visited = (bool*)calloc(n, sizeof(bool));
    int* queue = (int*)malloc(n * sizeof(int));
    int front = 0, back = 0;

    queue[back++] = source;
    visited[source] = true;

    while (front < back) {
        int node = queue[front++];
        for (int i = 0; i < graphSizes[node]; i++) {
            int neighbor = graph[node][i];
            if (!visited[neighbor]) {
                if (neighbor == destination) {
                    // Free allocated memory
                    for (int j = 0; j < n; j++) {
                        free(graph[j]);
                    }
                    free(graph);
                    free(graphSizes);
                    free(visited);
                    free(queue);
                    return true;
                }
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
    free(graphSizes);
    free(visited);
    free(queue);

    return false;       
}
