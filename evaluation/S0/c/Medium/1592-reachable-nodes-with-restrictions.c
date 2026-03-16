// Source: https://leetcode.com/problems/reachable-nodes-with-restrictions/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
//
// You are given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree. You are also given an integer array restricted which represents restricted nodes.
//
// Return the maximum number of nodes you can reach from node 0 without visiting a restricted node.
//
// Note that node 0 will not be a restricted node.
//
// Example:
// Input: n = 7, edges = [[0,1],[1,2],[3,1],[4,0],[0,5],[5,6]], restricted = [4,5]
// Output: 4
// Explanation: The diagram above shows the tree.
// We have that [0,1,2,3] are the only nodes that can be reached from node 0 without visiting a restricted node.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	edges represents a valid tree.
// 	1 <= restricted.length < n
// 	1 <= restricted[i] < n
// 	All the values of restricted are unique.
//

int reachableNodes(int n, int** edges, int edgesSize, int* edgesColSize, int* restricted, int restrictedSize) {
    // Create adjacency list
    int** graph = (int**)malloc(n * sizeof(int*));
    int* graphColSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int)); // Max possible size
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u][graphColSize[u]++] = v;
        graph[v][graphColSize[v]++] = u;
    }

    // Mark restricted nodes
    int* isRestricted = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < restrictedSize; i++) {
        isRestricted[restricted[i]] = 1;
    }

    // DFS to count reachable nodes
    int* visited = (int*)calloc(n, sizeof(int));
    int stack[n];
    int top = -1;
    stack[++top] = 0;
    visited[0] = 1;
    int reachableCount = 0;

    while (top >= 0) {
        int node = stack[top--];
        reachableCount++;

        for (int i = 0; i < graphColSize[node]; i++) {
            int neighbor = graph[node][i];
            if (!visited[neighbor] && !isRestricted[neighbor]) {
                visited[neighbor] = 1;
                stack[++top] = neighbor;
            }
        }
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphColSize);
    free(isRestricted);
    free(visited);

    return reachableCount;      
}
