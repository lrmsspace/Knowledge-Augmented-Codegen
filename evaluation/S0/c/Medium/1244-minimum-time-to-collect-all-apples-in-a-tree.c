// Source: https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given an undirected tree consisting of n vertices numbered from 0 to n-1, which has some apples in their vertices. You spend 1 second to walk over one edge of the tree. Return the minimum time in seconds you have to spend to collect all apples in the tree, starting at vertex 0 and coming back to this vertex.
//
// The edges of the undirected tree are given in the array edges, where edges[i] = [ai, bi] means that exists an edge connecting the vertices ai and bi. Additionally, there is a boolean array hasApple, where hasApple[i] = true means that vertex i has an apple; otherwise, it does not have any apple.
//
// Example:
// Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,true,true,false]
// Output: 8 
// Explanation: The figure above represents the given tree where red vertices have an apple. One optimal path to collect all apples is shown by the green arrows.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai < bi <= n - 1
// 	hasApple.length == n
//

int minTime(int n, int** edges, int edgesSize, int* edgesColSize, bool* hasApple, int hasAppleSize) {
    // Build adjacency list
    int** graph = (int**)calloc(n, sizeof(int*));
    int* graphColSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u] = (int*)realloc(graph[u], (graphColSize[u] + 1) * sizeof(int));
        graph[u][graphColSize[u]++] = v;
        graph[v] = (int*)realloc(graph[v], (graphColSize[v] + 1) * sizeof(int));
        graph[v][graphColSize[v]++] = u;
    }

    // DFS function to calculate time
    int dfs(int node, int parent) {
        int totalTime = 0;
        for (int i = 0; i < graphColSize[node]; i++) {
            int neighbor = graph[node][i];
            if (neighbor != parent) {
                totalTime += dfs(neighbor, node);
            }
        }
        if ((totalTime > 0 || hasApple[node]) && node != 0) {
            totalTime += 2; // Add time to go to this node and back
        }
        return totalTime;
    }

    int result = dfs(0, -1);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphColSize);

    return result;      
}
