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
// Notes:
//
//
// 	You can go through any vertex any number of times, including 1 and n.
// 	You can assume that when the journey starts, all signals have just turned green.
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
// Helpful references (internal KB):
// - Dijkstra Algorithm (graph, array, dijkstra, greedy)
//   • When to use: Use this algorithm to find the shortest paths from a single source to all other vertices in a graph. It is applicable when all edge weights are non-negative.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source vertex to all other vertices in a weighted graph with non-negative edge weights. It iteratively selects the unvisited vertex with the smallest known distance, relaxing its outgoing edges, achieving O(V^2 + E) or O(E log V) complexity.
//   • Invariants: For any marked vertex v, d[v] holds the true shortest path distance from s to v.; For any unmarked vertex v, d[v] holds the shortest path distance from s to v using only marked intermediate vertices.
//   • Tips: Use a priority queue for sparse graphs to optimize performance to O(E log V).; Initialize distances to infinity for all vertices except the source, which is zero.
//   • Pitfalls: Dijkstra's algorithm does not work correctly with negative edge weights; use Bellman-Ford or SPFA instead.; Failing to use an efficient data structure (like a priority queue) for vertex selection can lead to O(V^2) performance on sparse graphs.
// - Finding faces of a planar graph (graph, array, dfs, enumeration)
//   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
//   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
//   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
//   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
//   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int secondMinimum(int n, int** edges, int edgesSize, int* edgesColSize, int time, int change) {
    /* Build adjacency list */
    int *adjSizes = (int*)calloc(n + 1, sizeof(int));
    for (int i = 0; i < edgesSize; i++) {
        adjSizes[edges[i][0]]++;
        adjSizes[edges[i][1]]++;
    }
    int **adj = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 1; i <= n; i++) {
        adj[i] = (int*)malloc(adjSizes[i] * sizeof(int));
        adjSizes[i] = 0; // reuse for indexing
    }
    for (int i = 0; i < edgesSize; i++) {
        adj[edges[i][0]][adjSizes[edges[i][0]]++] = edges[i][1];
        adj[edges[i][1]][adjSizes[edges[i][1]]++] = edges[i][0];
    }

    /* Dijkstra-like approach to find first and second minimum times */
    #define INF 0x3f3f3f3f
    int (*dist)[2] = malloc((n + 1) * sizeof(int[2]));
    for (int i = 1; i <= n; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }
    dist[1][0] = 0;

    typedef struct {
        int node;
        int time;
    } State;
    State *pq = (State*)malloc((n * 2) * sizeof(State));
    int pqSize = 0;

    // Min-heap functions
    #define PARENT(i) (((i) - 1) / 2)
    #define LEFT(i) (2 * (i) + 1)
    #define RIGHT(i) (2 * (i) + 2)

    void swap(State *a, State *b) {
        State temp = *a;
        *a = *b;
        *b = temp;
    }

    void push(State s) {
        pq[pqSize] = s;
        int i = pqSize++;
        while (i > 0 && pq[PARENT(i)].time > pq[i].time) {
            swap(&pq[PARENT(i)], &pq[i]);
            i = PARENT(i);
        }
    }

    State pop() {
        State root = pq[0];
        pq[0] = pq[--pqSize];
        int i = 0;
        while (1) {
            int left = LEFT(i);
            int right = RIGHT(i);
            int smallest = i;
            if (left < pqSize && pq[left].time < pq[smallest].time) smallest = left;
            if (right < pqSize && pq[right].time < pq[smallest].time) smallest = right;
            if (smallest == i) break;
            swap(&pq[i], &pq[smallest]);
            i = smallest;
        }
        return root;
    }
    push((State){1, 0});
    while (pqSize > 0) {
        State curr = pop();
        int u = curr.node;
        int currTime = curr.time;

        for (int i = 0; i < adjSizes[u]; i++) {
            int v = adj[u][i];
            int waitTime = 0;
            if ((currTime / change) % 2 == 1) {
                waitTime = change - (currTime % change);
            }
            int newTime = currTime + waitTime + time;

            if (newTime < dist[v][0]) {
                dist[v][1] = dist[v][0];
                dist[v][0] = newTime;
                push((State){v, newTime});
            } else if (newTime > dist[v][0] && newTime < dist[v][1]) {
                dist[v][1] = newTime;
                push((State){v, newTime});
            }
        }
    }
    int result = dist[n][1];    
    free(adjSizes);
    for (int i = 1; i <= n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(dist);
    free(pq);
    return result;
    
}
