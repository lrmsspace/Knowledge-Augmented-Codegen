// Source: https://leetcode.com/problems/find-edges-in-shortest-paths/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted graph of n nodes numbered from 0 to n - 1. The graph consists of m edges represented by a 2D array edges, where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight wi.
//
// Consider all the shortest paths from node 0 to node n - 1 in the graph. You need to find a boolean array answer where answer[i] is true if the edge edges[i] is part of at least one shortest path. Otherwise, answer[i] is false.
//
// Return the array answer.
//
// Note that the graph may not be connected.
//
// Example:
// Input: n = 6, edges = [[0,1,4],[0,2,1],[1,3,2],[1,4,3],[1,5,1],[2,3,1],[3,5,3],[4,5,2]]
//
// Output: [true,true,true,false,true,true,true,false]
//
// Explanation:
//
// The following are all the shortest paths between nodes 0 and 5:
//
//
// 	The path 0 -> 1 -> 5: The sum of weights is 4 + 1 = 5.
// 	The path 0 -> 2 -> 3 -> 5: The sum of weights is 1 + 1 + 3 = 5.
// 	The path 0 -> 2 -> 3 -> 1 -> 5: The sum of weights is 1 + 1 + 2 + 1 = 5.
//
// Constraints:
// 2 <= n <= 5 * 104
// 	m == edges.length
// 	1 <= m <= min(5 * 104, n * (n - 1) / 2)
// 	0 <= ai, bi < n
// 	ai != bi
// 	1 <= wi <= 105
// 	There are no repeated edges.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* findAnswer(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = edgesSize;
    bool* answer = (bool*)calloc(edgesSize, sizeof(bool));
    if (!answer) return NULL;

    typedef struct {
        int to;
        long long weight;
        int index;
    } Edge;

    typedef struct {
        int node;
        long long dist;
    } Item;

    // Build adjacency list
    Edge** graph = (Edge**)malloc(n * sizeof(Edge*));
    int* graphSizes = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        graph[i] = NULL;
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        long long w = edges[i][2];

        graph[u] = (Edge*)realloc(graph[u], (graphSizes[u] + 1) * sizeof(Edge));
        graph[u][graphSizes[u]++] = (Edge){v, w, i};

        graph[v] = (Edge*)realloc(graph[v], (graphSizes[v] + 1) * sizeof(Edge));
        graph[v][graphSizes[v]++] = (Edge){u, w, i};
    }

    // Dijkstra's algorithm
    long long* dist = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        dist[i] = 1e18;
    }
    dist[0] = 0;

    Item* pq = (Item*)malloc(n * n * sizeof(Item));
    int pqSize = 0;
    pq[pqSize++] = (Item){0, 0};

    while (pqSize > 0) {
        // Extract min
        int minIndex = 0;
        for (int i = 1; i < pqSize; i++) {
            if (pq[i].dist < pq[minIndex].dist) {
                minIndex = i;
            }
        }
        Item current = pq[minIndex];
        pq[minIndex] = pq[--pqSize];

        if (current.dist > dist[current.node]) continue;

        for (int i = 0; i < graphSizes[current.node]; i++) {
            Edge edge = graph[current.node][i];
            long long newDist = current.dist + edge.weight;
            if (newDist < dist[edge.to]) {
                dist[edge.to] = newDist;
                pq[pqSize++] = (Item){edge.to, newDist};
            }
        }
    }
    free(pq);
    free(dist);
    // Check edges
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        long long w = edges[i][2];

        // Check if edge (u, v) is in any shortest path
        if (dist[u] + w == dist[v] || dist[v] + w == dist[u]) {
            answer[i] = true;
        }
    }
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphSizes);
    return answer;
}
