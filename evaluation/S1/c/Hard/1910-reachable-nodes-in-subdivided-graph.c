// Source: https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph (the "original graph") with n nodes labeled from 0 to n - 1. You decide to subdivide each edge in the graph into a chain of nodes, with the number of new nodes varying between each edge.
//
// The graph is given as a 2D array of edges where edges[i] = [ui, vi, cnti] indicates that there is an edge between nodes ui and vi in the original graph, and cnti is the total number of new nodes that you will subdivide the edge into. Note that cnti == 0 means you will not subdivide the edge.
//
// To subdivide the edge [ui, vi], replace it with (cnti + 1) new edges and cnti new nodes. The new nodes are x1, x2, ..., xcnti, and the new edges are [ui, x1], [x1, x2], [x2, x3], ..., [xcnti-1, xcnti], [xcnti, vi].
//
// In this new graph, you want to know how many nodes are reachable from the node 0, where a node is reachable if the distance is maxMoves or less.
//
// Given the original graph and maxMoves, return the number of nodes that are reachable from node 0 in the new graph.
//
// Example:
// Input: edges = [[0,1,10],[0,2,1],[1,2,2]], maxMoves = 6, n = 3
// Output: 13
// Explanation: The edge subdivisions are shown in the image above.
// The nodes that are reachable are highlighted in yellow.
//
// Constraints:
// 0 <= edges.length <= min(n * (n - 1) / 2, 104)
// 	edges[i].length == 3
// 	0 <= ui < vi < n
// 	There are no multiple edges in the graph.
// 	0 <= cnti <= 104
// 	0 <= maxMoves <= 109
// 	1 <= n <= 3000
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

int reachableNodes(int** edges, int edgesSize, int* edgesColSize, int maxMoves, int n) {
    /* Build adjacency list */
    typedef struct {
        int to;
        int weight;
    } Edge;
    typedef struct {
        Edge* edges;
        int size;
        int capacity;
    } AdjList;

    AdjList* graph = (AdjList*)calloc(n, sizeof(AdjList));
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int cnt = edges[i][2];
        if (graph[u].size == graph[u].capacity) {
            graph[u].capacity = graph[u].capacity ? graph[u].capacity * 2 : 4;
            graph[u].edges = (Edge*)realloc(graph[u].edges, graph[u].capacity * sizeof(Edge));
        }
        graph[u].edges[graph[u].size++] = (Edge){v, cnt + 1};
        if (graph[v].size == graph[v].capacity) {
            graph[v].capacity = graph[v].capacity ? graph[v].capacity * 2 : 4;
            graph[v].edges = (Edge*)realloc(graph[v].edges, graph[v].capacity * sizeof(Edge));
        }
        graph[v].edges[graph[v].size++] = (Edge){u, cnt + 1};
    }

    /* Dijkstra's algorithm */
    int* dist = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) dist[i] = -1;
    dist[0] = 0;

    typedef struct {
        int node;
        int dist;
    } HeapNode;

    typedef struct {
        HeapNode* data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(16 * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = 16;

    void heapPush(MinHeap* h, int node, int distance) {
        if (h->size == h->capacity) {
            h->capacity *= 2;
            h->data = (HeapNode*)realloc(h->data, h->capacity * sizeof(HeapNode));
        }
        h->data[h->size] = (HeapNode){node, distance};
        int idx = h->size++;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (h->data[parent].dist <= h->data[idx].dist) break;
            HeapNode temp = h->data[parent];
            h->data[parent] = h->data[idx];
            h->data[idx] = temp;
            idx = parent;
        }
    }
    HeapNode heapPop(MinHeap* h) {
        HeapNode result = h->data[0];
        h->data[0] = h->data[--h->size];
        int idx = 0;
        while (idx * 2 + 1 < h->size) {
            int left = idx * 2 + 1;
            int right = idx * 2 + 2;
            int smallest = left;
            if (right < h->size && h->data[right].dist < h->data[left].dist) {
                smallest = right;
            }
            if (h->data[idx].dist <= h->data[smallest].dist) break;
            HeapNode temp = h->data[idx];
            h->data[idx] = h->data[smallest];
            h->data[smallest] = temp;
            idx = smallest;
        }
        return result;
    }
    heapPush(heap, 0, 0);
    while (heap->size > 0) {
        HeapNode current = heapPop(heap);
        int u = current.node;
        int d = current.dist;
        if (d > dist[u]) continue;
        for (int i = 0; i < graph[u].size; i++) {
            Edge e = graph[u].edges[i];
            int v = e.to;
            int weight = e.weight;
            int newDist = d + weight;
            if (newDist <= maxMoves && (dist[v] == -1 || newDist < dist[v])) {
                dist[v] = newDist;
                heapPush(heap, v, newDist);
            }
        }
    }
    free(heap->data);
    free(heap);
    free(graph);
    /* Count reachable nodes */
    int reachable = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] != -1) reachable++;
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int cnt = edges[i][2];
        int usedFromU = 0, usedFromV = 0;
        if (dist[u] != -1) {
            usedFromU = (maxMoves - dist[u]) > cnt ? cnt : (maxMoves - dist[u]);
        }
        if (dist[v] != -1) {
            usedFromV = (maxMoves - dist[v]) > cnt ? cnt : (maxMoves - dist[v]);
        }
        reachable += (usedFromU + usedFromV) > cnt ? cnt : (usedFromU + usedFromV);
    }
    free(dist);
    return reachable;
}
