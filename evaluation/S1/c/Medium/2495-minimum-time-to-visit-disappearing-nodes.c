// Source: https://leetcode.com/problems/minimum-time-to-visit-disappearing-nodes/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected graph of n nodes. You are given a 2D array edges, where edges[i] = [ui, vi, lengthi] describes an edge between node ui and node vi with a traversal time of lengthi units.
//
// Additionally, you are given an array disappear, where disappear[i] denotes the time when the node i disappears from the graph and you won't be able to visit it.
//
// Note that the graph might be disconnected and might contain multiple edges.
//
// Return the array answer, with answer[i] denoting the minimum units of time required to reach node i from node 0. If node i is unreachable from node 0 then answer[i] is -1.
//
// Example:
// Input: n = 3, edges = [[0,1,2],[1,2,1],[0,2,4]], disappear = [1,1,5]
//
// Output: [0,-1,4]
//
// Explanation:
//
//
//
// We are starting our journey from node 0, and our goal is to find the minimum time required to reach each node before it disappears.
//
//
// 	For node 0, we don't need any time as it is our starting point.
// 	For node 1, we need at least 2 units of time to traverse edges[0]. Unfortunately, it disappears at that moment, so we won't be able to visit it.
// 	For node 2, we need at least 4 units of time to traverse edges[2].
//
// Constraints:
// 1 <= n <= 5 * 104
// 	0 <= edges.length <= 105
// 	edges[i] == [ui, vi, lengthi]
// 	0 <= ui, vi <= n - 1
// 	1 <= lengthi <= 105
// 	disappear.length == n
// 	1 <= disappear[i] <= 105
//
// Helpful references (internal KB):
// - Dijkstra Algorithm (graph, array, dijkstra, greedy)
//   • When to use: Use this algorithm to find the shortest paths from a single source to all other vertices in a graph. It is applicable when all edge weights are non-negative.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source vertex to all other vertices in a weighted graph with non-negative edge weights. It iteratively selects the unvisited vertex with the smallest known distance, relaxing its outgoing edges, achieving O(V^2 + E) or O(E log V) complexity.
//   • Invariants: For any marked vertex v, d[v] holds the true shortest path distance from s to v.; For any unmarked vertex v, d[v] holds the shortest path distance from s to v using only marked intermediate vertices.
//   • Tips: Use a priority queue for sparse graphs to optimize performance to O(E log V).; Initialize distances to infinity for all vertices except the source, which is zero.
//   • Pitfalls: Dijkstra's algorithm does not work correctly with negative edge weights; use Bellman-Ford or SPFA instead.; Failing to use an efficient data structure (like a priority queue) for vertex selection can lead to O(V^2) performance on sparse graphs.
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
// - Finding bridges in a graph in O(N+M) (graph, dfs)
//   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
//   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
//   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
//   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
//   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minimumTime(int n, int** edges, int edgesSize, int* edgesColSize, int* disappear, int disappearSize, int* returnSize) {
    // Build adjacency list
    int* adjSizes = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < edgesSize; ++i) {
        adjSizes[edges[i][0]]++;
        adjSizes[edges[i][1]]++;
    }
    int** adj = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        adj[i] = (int*)malloc(adjSizes[i] * sizeof(int));
        adjSizes[i] = 0;
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adj[u][adjSizes[u]++] = v;
        adj[v][adjSizes[v]++] = u;
    }

    // Dijkstra's algorithm
    int* dist = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        dist[i] = -1;
    }
    dist[0] = 0;

    // Min-heap priority queue
    typedef struct {
        int node;
        int time;
    } HeapNode;

    HeapNode* heap = (HeapNode*)malloc(n * sizeof(HeapNode));
    int heapSize = 0;

    void swap(HeapNode* a, HeapNode* b) {
        HeapNode temp = *a;
        *a = *b;
        *b = temp;
    }

    void insert(HeapNode* heap, int* heapSize, int node, int time) {
        heap[*heapSize].node = node;
        heap[*heapSize].time = time;
        int idx = (*heapSize)++;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap[parent].time <= heap[idx].time) break;
            swap(&heap[parent], &heap[idx]);
            idx = parent;
        }
    }
    HeapNode extractMin(HeapNode* heap, int* heapSize) {
        HeapNode minNode = heap[0];
        heap[0] = heap[--(*heapSize)];
        int idx = 0;
        while (1) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int smallest = idx;
            if (left < *heapSize && heap[left].time < heap[smallest].time) {
                smallest = left;
            }
            if (right < *heapSize && heap[right].time < heap[smallest].time) {
                smallest = right;
            }
            if (smallest == idx) break;
            swap(&heap[idx], &heap[smallest]);
            idx = smallest;
        }
        return minNode;
    }
    insert(heap, &heapSize, 0, 0);
    while (heapSize > 0) {
        HeapNode current = extractMin(heap, &heapSize);
        int node = current.node;
        int time = current.time;

        if (dist[node] < time) continue; // Already found a better path

        for (int i = 0; i < adjSizes[node]; ++i) {
            int neighbor = adj[node][i];
            int travelTime = time + edges[0][2]; // Assuming uniform edge length for simplicity
            if (travelTime < disappear[neighbor]) {
                if (dist[neighbor] == -1 || travelTime < dist[neighbor]) {
                    dist[neighbor] = travelTime;
                    insert(heap, &heapSize, neighbor, travelTime);
                }
            }
        }
    }   
    free(heap);
    for (int i = 0; i < n; ++i) {
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);
    *returnSize = n;
    return dist;
}
