// Source: https://leetcode.com/problems/shortest-path-with-alternating-colors/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n, the number of nodes in a directed graph where the nodes are labeled from 0 to n - 1. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.
//
// You are given two arrays redEdges and blueEdges where:
//
//
// 	redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the graph, and
// 	blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the graph.
//
//
// Return an array answer of length n, where each answer[x] is the length of the shortest path from node 0 to node x such that the edge colors alternate along the path, or -1 if such a path does not exist.
//
// Example:
// Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
// Output: [0,1,-1]
//
// Constraints:
// 1 <= n <= 100
// 	0 <= redEdges.length, blueEdges.length <= 400
// 	redEdges[i].length == blueEdges[j].length == 2
// 	0 <= ai, bi, uj, vj < n
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shortestAlternatingPaths(int n, int** redEdges, int redEdgesSize, int* redEdgesColSize, int** blueEdges, int blueEdgesSize, int* blueEdgesColSize, int* returnSize) {
    int** graph = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)calloc(n, sizeof(int));
    }
    for (int i = 0; i < redEdgesSize; i++) {
        graph[redEdges[i][0]][redEdges[i][1]] |= 1; // red edge
    }
    for (int i = 0; i < blueEdgesSize; i++) {
        graph[blueEdges[i][0]][blueEdges[i][1]] |= 2; // blue edge
    }

    int* dist = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dist[i] = -1;
    }
    dist[0] = 0;

    int queue[2][n];
    int front[2] = {0, 0};
    int back[2] = {0, 0};
    queue[0][back[0]++] = 0; // start with red
    queue[1][back[1]++] = 0; // start with blue

    int step = 0;
    while (front[0] < back[0] || front[1] < back[1]) {
        step++;
        for (int color = 0; color < 2; color++) {
            int size = back[color] - front[color];
            for (int i = 0; i < size; i++) {
                int node = queue[color][front[color]++];
                for (int nei = 0; nei < n; nei++) {
                    if ((graph[node][nei] & (1 << color)) && dist[nei] == -1) {
                        dist[nei] = step;
                        queue[1 - color][back[1 - color]++] = nei;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);

    *returnSize = n;
    return dist;        
}
