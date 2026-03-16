// Source: https://leetcode.com/problems/path-with-maximum-probability/   |   Difficulty: Medium
//
// Problem Description:
// You are given an undirected weighted graph of n nodes (0-indexed), represented by an edge list where edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of success of traversing that edge succProb[i].
//
// Given two nodes start and end, find the path with the maximum probability of success to go from start to end and return its success probability.
//
// If there is no path from start to end, return 0. Your answer will be accepted if it differs from the correct answer by at most 1e-5.
//
// Example:
// Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
// Output: 0.25000
// Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.
//
// Constraints:
// 2 <= n <= 10^4
// 	0 <= start, end < n
// 	start != end
// 	0 <= a, b < n
// 	a != b
// 	0 <= succProb.length == edges.length <= 2*10^4
// 	0 <= succProb[i] <= 1
// 	There is at most one edge between every two nodes.
//
// Helpful references (internal KB):
// - Undirected Graphs (graph, matrix, simulation)
//   • When to use: Use when modeling symmetric relationships between entities, analyzing graph properties like connectivity or degrees, or simulating processes on a network where connections are bidirectional.
//   • Idea: An undirected graph consists of a set of vertices and a set of edges, where each edge connects two vertices symmetrically. Basic operations often have a time complexity of O(V+E) or O(V^2) depending on representation.
//   • Invariants: For every edge (u, v) in the graph, the edge (v, u) also exists.; The sum of degrees of all vertices equals twice the number of edges.
//   • Tips: Choose adjacency list for sparse graphs, adjacency matrix for dense graphs.; Degrees of vertices are easily calculated from adjacency representations.
//   • Pitfalls: Forgetting to add both (u,v) and (v,u) when using an adjacency matrix or list.; Not handling disconnected components during full graph traversals.
// - Dijkstra on sparse graphs (heap, queue, dijkstra)
//   • When to use: When you need to find the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights, especially efficient for sparse graphs.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source to all other vertices in a weighted graph with non-negative edge weights. It uses a priority queue to greedily explore vertices, achieving O(E log V) complexity with a binary heap.
//   • Invariants: At the start of each iteration, dist[u] holds the shortest distance found so far from the source to u.; All vertices already extracted from the priority queue have their final shortest distance determined.
//   • Tips: Use a priority queue (min-heap) to efficiently retrieve the unvisited vertex with the smallest distance.; Initialize all distances to infinity and the source distance to zero.
//   • Pitfalls: Does not work correctly with negative edge weights; Bellman-Ford or SPFA is needed.; Forgetting to mark vertices as visited or handle duplicate entries in the priority queue can lead to incorrectness or TLE.
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double maxProbability(int n, int** edges, int edgesSize, int* edgesColSize, double* succProb, int succProbSize, int start_node, int end_node) {
    // Dijkstra's algorithm to find the maximum probability path
    #define MAX_EDGES 20000
    #define MAX_NODES 10000

    typedef struct {
        int node;
        double prob;
    } HeapNode;

    typedef struct {
        HeapNode data[MAX_EDGES + 1];
        int size;
    } MaxHeap;

    void heap_init(MaxHeap* heap) {
        heap->size = 0;
    }

    void heap_push(MaxHeap* heap, int node, double prob) {
        heap->data[++heap->size] = (HeapNode){node, prob};
        int idx = heap->size;
        while (idx > 1 && heap->data[idx].prob > heap->data[idx / 2].prob) {
            HeapNode temp = heap->data[idx];
            heap->data[idx] = heap->data[idx / 2];
            heap->data[idx / 2] = temp;
            idx /= 2;
        }
    }

    HeapNode heap_pop(MaxHeap* heap) {
        HeapNode top = heap->data[1];
        heap->data[1] = heap->data[heap->size--];
        int idx = 1;
        while (1) {
            int largest = idx;
            if (2 * idx <= heap->size && heap->data[2 * idx].prob > heap->data[largest].prob) {
                largest = 2 * idx;
            }
            if (2 * idx + 1 <= heap->size && heap->data[2 * idx + 1].prob > heap->data[largest].prob) {
                largest = 2 * idx + 1;
            }
            if (largest == idx) break;
            HeapNode temp = heap->data[idx];
            heap->data[idx] = heap->data[largest];
            heap->data[largest] = temp;
            idx = largest;
        }
        return top;
    }

    // Build adjacency list
    typedef struct {
        int to;
        double prob;
        struct Edge* next;
    } Edge;

    Edge* graph[MAX_NODES] = {0};

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        double p = succProb[i];

        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = v;
        edge1->prob = p;
        edge1->next = graph[u];
        graph[u] = edge1;

        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = u;
        edge2->prob = p;
        edge2->next = graph[v];
        graph[v] = edge2;
    }
    double dist[MAX_NODES];
    for (int i = 0; i < n; i++) {
        dist[i] = 0.0;
    }
    dist[start_node] = 1.0;
    MaxHeap heap;
    heap_init(&heap);
    heap_push(&heap, start_node, 1.0);
    while (heap.size > 0) {
        HeapNode current = heap_pop(&heap);
        int u = current.node;
        double p = current.prob;
        if (p < dist[u]) continue;
        for (Edge* edge = graph[u]; edge != NULL; edge = edge->next) {
            int v = edge->to;
            double newProb = p * edge->prob;
            if (newProb > dist[v]) {
                dist[v] = newProb;
                heap_push(&heap, v, newProb);
            }
        }
    }
    // Free graph memory
    for (int i = 0; i < n; i++) {
        Edge* edge = graph[i];
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    return dist[end_node];
}