// Source: https://leetcode.com/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi in the tree.
//
// You are also given a 2D integer array queries of length m, where queries[i] = [ai, bi]. For each query, find the minimum number of operations required to make the weight of every edge on the path from ai to bi equal. In one operation, you can choose any edge of the tree and change its weight to any value.
//
// Note that:
//
//
// 	Queries are independent of each other, meaning that the tree returns to its initial state on each new query.
// 	The path from ai to bi is a sequence of distinct nodes starting with node ai and ending with node bi such that every two adjacent nodes in the sequence share an edge in the tree.
//
//
// Return an array answer of length m where answer[i] is the answer to the ith query.
//
// Example:
// Input: n = 7, edges = [[0,1,1],[1,2,1],[2,3,1],[3,4,2],[4,5,2],[5,6,2]], queries = [[0,3],[3,6],[2,6],[0,6]]
// Output: [0,0,1,3]
// Explanation: In the first query, all the edges in the path from 0 to 3 have a weight of 1. Hence, the answer is 0.
// In the second query, all the edges in the path from 3 to 6 have a weight of 2. Hence, the answer is 0.
// In the third query, we change the weight of edge [2,3] to 2. After this operation, all the edges in the path from 2 to 6 have a weight of 2. Hence, the answer is 1.
// In the fourth query, we change the weights of edges [0,1], [1,2] and [2,3] to 2. After these operations, all the edges in the path from 0 to 6 have a weight of 2. Hence, the answer is 3.
// For each queries[i], it can be shown that answer[i] is the minimum number of operations needed to equalize all the edge weights in the path from ai to bi.
//
// Constraints:
// 1 <= n <= 104
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ui, vi < n
// 	1 <= wi <= 26
// 	The input is generated such that edges represents a valid tree.
// 	1 <= queries.length == m <= 2 * 104
// 	queries[i].length == 2
// 	0 <= ai, bi < n
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minOperationsQueries(int n, int** edges, int edgesSize, int* edgesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
  
    if (!returnSize) return NULL;
    *returnSize = queriesSize;
    int *res = (int*)malloc(queriesSize * sizeof(int));
    if (!res) return NULL;

    // Build adjacency list
    typedef struct {
        int to;
        int weight;
    } Edge;

    Edge** graph = (Edge**)malloc(n * sizeof(Edge*));
    int* graphSizes = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        graph[i] = (Edge*)malloc(n * sizeof(Edge));
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        graph[u][graphSizes[u]++] = (Edge){v, w};
        graph[v][graphSizes[v]++] = (Edge){u, w};
    }

    // Process each query using BFS
    for (int q = 0; q < queriesSize; q++) {
        int start = queries[q][0];
        int end = queries[q][1];

        int* dist = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) dist[i] = -1;
        dist[start] = 0;

        int* queue = (int*)malloc(n * sizeof(int));
        int front = 0, back = 0;
        queue[back++] = start;

        while (front < back) {
            int u = queue[front++];
            for (int i = 0; i < graphSizes[u]; i++) {
                Edge edge = graph[u][i];
                int v = edge.to;
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    queue[back++] = v;
                }
            }
        }

        // Backtrack from end to start to count weights
        int* weightCount = (int*)calloc(27, sizeof(int));
        int curr = end;
        while (curr != start) {
            for (int i = 0; i < graphSizes[curr]; i++) {
                Edge edge = graph[curr][i];
                int v = edge.to;
                if (dist[v] == dist[curr] - 1) {
                    weightCount[edge.weight]++;
                    curr = v;
                    break;
                }
            }
        }
        free(dist);
        free(queue);
        // Find max frequency weight
        int maxFreq = 0;
        for (int i = 1; i <= 26; i++) {
            if (weightCount[i] > maxFreq) {
                maxFreq = weightCount[i];
            }
        }
        // Total edges in path = dist[end], operations = total edges - maxFreq
        res[q] = dist[end] - maxFreq;
        free(weightCount);
    }
    // Free graph memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphSizes);
    return res;
}
