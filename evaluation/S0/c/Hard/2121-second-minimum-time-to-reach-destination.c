// Source: https://leetcode.com/problems/second-minimum-time-to-reach-destination/   |   Difficulty: Hard
//
// Problem Description:
// A city is represented as a bi-directional connected graph with n vertices where each vertex is labeled from 1 to n (inclusive). The edges in the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself. The time taken to traverse any edge is time minutes.
//
// Each vertex has a traffic signal which changes its color from green to red and vice versa every change minutes. All signals change at the same time. You can enter a vertex at any time, but can leave a vertex only when the signal is green. You cannot wait at a vertex if the signal is green.
//
// The second minimum value is defined as the smallest value strictly larger than the minimum value.
//
//
// 	For example the second minimum value of [2, 3, 4] is 3, and the second minimum value of [2, 2, 4] is 4.
//
//
// Given n, edges, time, and change, return the second minimum time it will take to go from vertex 1 to vertex n.
//
// Example:
// Input: n = 5, edges = [[1,2],[1,3],[1,4],[3,4],[4,5]], time = 3, change = 5
// Output: 13
// Explanation:
// The figure on the left shows the given graph.
// The blue path in the figure on the right is the minimum time path.
// The time taken is:
// - Start at 1, time elapsed=0
// - 1 -> 4: 3 minutes, time elapsed=3
// - 4 -> 5: 3 minutes, time elapsed=6
// Hence the minimum time needed is 6 minutes.
//
// The red path shows the path to get the second minimum time.
// - Start at 1, time elapsed=0
// - 1 -> 3: 3 minutes, time elapsed=3
// - 3 -> 4: 3 minutes, time elapsed=6
// - Wait at 4 for 4 minutes, time elapsed=10
// - 4 -> 5: 3 minutes, time elapsed=13
// Hence the second minimum time is 13 minutes.
//
// Constraints:
// 2 <= n <= 104
// 	n - 1 <= edges.length <= min(2 * 104, n * (n - 1) / 2)
// 	edges[i].length == 2
// 	1 <= ui, vi <= n
// 	ui != vi
// 	There are no duplicate edges.
// 	Each vertex can be reached directly or indirectly from every other vertex.
// 	1 <= time, change <= 103
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int secondMinimum(int n, int** edges, int edgesSize, int* edgesColSize, int time, int change) {
    // Build adjacency list
    int** graph = (int**)malloc((n + 1) * sizeof(int*));
    int* graphSizes = (int*)calloc(n + 1, sizeof(int));
    for (int i = 0; i <= n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u][graphSizes[u]++] = v;
        graph[v][graphSizes[v]++] = u;
    }

    // BFS to find the second minimum time
    int dist[2][n + 1];
    for (int i = 0; i <= n; i++) {
        dist[0][i] = dist[1][i] = __INT_MAX__;
    }
    dist[0][1] = 0;

    typedef struct {
        int node;
        int time;
    } State;

    State* queue = (State*)malloc(2 * n * sizeof(State));
    int front = 0, back = 0;
    queue[back++] = (State){1, 0};

    while (front < back) {
        State curr = queue[front++];
        for (int i = 0; i < graphSizes[curr.node]; i++) {
            int neighbor = graph[curr.node][i];
            int waitTime = (curr.time / change) % 2 == 1 ? change - (curr.time % change) : 0;
            int arrivalTime = curr.time + waitTime + time;

            if (arrivalTime < dist[0][neighbor]) {
                dist[1][neighbor] = dist[0][neighbor];
                dist[0][neighbor] = arrivalTime;
                queue[back++] = (State){neighbor, arrivalTime};
            } else if (arrivalTime > dist[0][neighbor] && arrivalTime < dist[1][neighbor]) {
                dist[1][neighbor] = arrivalTime;
                queue[back++] = (State){neighbor, arrivalTime};
            }
        }
    }

    int result = dist[1][n];

    // Free memory
    for (int i = 0; i <= n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphSizes);
    free(queue);
    return result;
}
