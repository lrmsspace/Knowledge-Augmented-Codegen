// Source: https://leetcode.com/problems/minimum-edge-reversals-so-every-node-is-reachable/   |   Difficulty: Hard
//
// Problem Description:
// There is a simple directed graph with n nodes labeled from 0 to n - 1. The graph would form a tree if its edges were bi-directional.
//
// You are given an integer n and a 2D integer array edges, where edges[i] = [ui, vi] represents a directed edge going from node ui to node vi.
//
// An edge reversal changes the direction of an edge, i.e., a directed edge going from node ui to node vi becomes a directed edge going from node vi to node ui.
//
// For every node i in the range [0, n - 1], your task is to independently calculate the minimum number of edge reversals required so it is possible to reach any other node starting from node i through a sequence of directed edges.
//
// Return an integer array answer, where answer[i] is the  minimum number of edge reversals required so it is possible to reach any other node starting from node i through a sequence of directed edges.
//
// Example:
// Input: n = 4, edges = [[2,0],[2,1],[1,3]]
// Output: [1,1,0,2]
// Explanation: The image above shows the graph formed by the edges.
// For node 0: after reversing the edge [2,0], it is possible to reach any other node starting from node 0.
// So, answer[0] = 1.
// For node 1: after reversing the edge [2,1], it is possible to reach any other node starting from node 1.
// So, answer[1] = 1.
// For node 2: it is already possible to reach any other node starting from node 2.
// So, answer[2] = 0.
// For node 3: after reversing the edges [1,3] and [2,1], it is possible to reach any other node starting from node 3.
// So, answer[3] = 2.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ui == edges[i][0] < n
// 	0 <= vi == edges[i][1] < n
// 	ui != vi
// 	The input is generated such that if the edges were bi-directional, the graph would be a tree.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minEdgeReversals(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = n;
    int *res = (int*)calloc(n, sizeof(int));
    if (!res) return NULL;

    /* Build adjacency list with edge directions encoded */
    int **adj = (int**)calloc(n, sizeof(int*));
    int *adjSizes = (int*)calloc(n, sizeof(int));
    if (!adj || !adjSizes) {
        free(res); free(adj); free(adjSizes); return NULL;
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adj[u] = (int*)realloc(adj[u], (adjSizes[u] + 1) * sizeof(int));
        adj[u][adjSizes[u]++] = v;      /* original direction */
        adj[v] = (int*)realloc(adj[v], (adjSizes[v] + 1) * sizeof(int));
        adj[v][adjSizes[v]++] = -u;     /* reversed direction */
    }

    /* First DFS to count reversals needed from node 0 */
    int *visited = (int*)calloc(n, sizeof(int));
    if (!visited) {
        free(res); free(adj); free(adjSizes); return NULL;
    }
    visited[0] = 1;
    int stack[n], top = -1;
    stack[++top] = 0;
    while (top >= 0) {
        int node = stack[top--];
        for (int i = 0; i < adjSizes[node]; ++i) {
            int neighbor = adj[node][i];
            int toNode = neighbor < 0 ? -neighbor : neighbor;
            if (!visited[toNode]) {
                visited[toNode] = 1;
                if (neighbor > 0) res[0]++; /* original direction needs reversal */
                stack[++top] = toNode;
            }
        }
    }

    /* Second DFS to compute results for all nodes */
    memset(visited, 0, n * sizeof(int));
    visited[0] = 1;
    stack[++top] = 0;
    while (top >= 0) {
        int node = stack[top--];
        for (int i = 0; i < adjSizes[node]; ++i) {
            int neighbor = adj[node][i];
            int toNode = neighbor < 0 ? -neighbor : neighbor;
            if (!visited[toNode]) {
                visited[toNode] = 1;
                if (neighbor > 0) {
                    res[toNode] = res[node] - 1; /* original direction */
                } else {
                    res[toNode] = res[node] + 1; /* reversed direction */
                }
                stack[++top] = toNode;
            }
        }
    }
    free(visited);
    for (int i = 0; i < n; ++i) free(adj[i]);
    free(adj);
    free(adjSizes);
    return res;
}
