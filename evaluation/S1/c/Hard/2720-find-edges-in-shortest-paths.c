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
// Helpful references (internal KB):
// - Shortest Paths (array, graph, dp-1d)
//   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
//   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
//   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
//   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
//   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
// - Dijkstra on sparse graphs (heap, queue, dijkstra)
//   • When to use: When you need to find the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights, especially efficient for sparse graphs.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source to all other vertices in a weighted graph with non-negative edge weights. It uses a priority queue to greedily explore vertices, achieving O(E log V) complexity with a binary heap.
//   • Invariants: At the start of each iteration, dist[u] holds the shortest distance found so far from the source to u.; All vertices already extracted from the priority queue have their final shortest distance determined.
//   • Tips: Use a priority queue (min-heap) to efficiently retrieve the unvisited vertex with the smallest distance.; Initialize all distances to infinity and the source distance to zero.
//   • Pitfalls: Does not work correctly with negative edge weights; Bellman-Ford or SPFA is needed.; Forgetting to mark vertices as visited or handle duplicate entries in the priority queue can lead to incorrectness or TLE.
// - Edge connectivity / Vertex connectivity (graph, enumeration)
//   • When to use: Used to quantify a graph's resilience by finding the minimum number of edges or vertices whose removal disconnects it, or separates a specific pair of nodes.
//   • Idea: Edge connectivity is the minimum edges to disconnect a graph, while vertex connectivity is for vertices. Both are often computed using max-flow min-cut theorems, typically in polynomial time.
//   • Invariants: The flow through any edge in the network does not exceed its capacity.; For any intermediate vertex (not source or sink), the total incoming flow equals the total outgoing flow.
//   • Tips: Edge connectivity between two specific vertices can be found using a max-flow min-cut algorithm.; To find global edge connectivity, iterate over all pairs of vertices or use specialized algorithms.
//   • Pitfalls: Confusing edge connectivity (edges) with vertex connectivity (vertices) requirements.; Incorrectly applying max-flow for global connectivity without considering all relevant source-sink pairs.
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
bool* findAnswer(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    // Build adjacency list
    typedef struct AdjNode {
        int to;
        int weight;
        int edgeIndex;
        struct AdjNode* next;
    } AdjNode;

    AdjNode** graph = (AdjNode**)calloc(n, sizeof(AdjNode*));
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        AdjNode* nodeU = (AdjNode*)malloc(sizeof(AdjNode));
        nodeU->to = v; nodeU->weight = w; nodeU->edgeIndex = i; nodeU->next = graph[u];
        graph[u] = nodeU;

        AdjNode* nodeV = (AdjNode*)malloc(sizeof(AdjNode));
        nodeV->to = u; nodeV->weight = w; nodeV->edgeIndex = i; nodeV->next = graph[v];
        graph[v] = nodeV;
    }

    // Dijkstra's algorithm
    long long* dist = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) dist[i] = 1LL << 60;
    dist[0] = 0;

    typedef struct HeapNode {
        int vertex;
        long long distance;
    } HeapNode;

    HeapNode* heap = (HeapNode*)malloc(n * sizeof(HeapNode));
    int heapSize = 0;

    #define SWAP(a, b) { HeapNode temp = a; a = b; b = temp; }
    void heapPush(int vertex, long long distance) {
        heap[heapSize].vertex = vertex;
        heap[heapSize].distance = distance;
        int idx = heapSize++;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap[parent].distance <= heap[idx].distance) break;
            SWAP(heap[parent], heap[idx]);
            idx = parent;
        }
    }

    HeapNode heapPop() {
        HeapNode top = heap[0];
        heap[0] = heap[--heapSize];
        int idx = 0;
        while (1) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int smallest = idx;
            if (left < heapSize && heap[left].distance < heap[smallest].distance) {
                smallest = left;
            }
            if (right < heapSize && heap[right].distance < heap[smallest].distance) {
                smallest = right;
            }
            if (smallest == idx) break;
            SWAP(heap[idx], heap[smallest]);
            idx = smallest;
        }
        return top;
    }
    heapPush(0, 0);
    while (heapSize) {
        HeapNode node = heapPop();
        int u = node.vertex;
        long long d = node.distance;
        if (d > dist[u]) continue;
        AdjNode* neighbor = graph[u];
        while (neighbor) {
            int v = neighbor->to;
            long long w = neighbor->weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                heapPush(v, dist[v]);
            }
            neighbor = neighbor->next;
        }
    }
    // Determine which edges are in any shortest path
    bool* answer = (bool*)malloc(edgesSize * sizeof(bool));
    for (int i = 0; i < edgesSize; i++) {
        answer[i] = false;
    }
    for (int u = 0; u < n; u++) {
        AdjNode* neighbor = graph[u];
        while (neighbor) {
            int v = neighbor->to;
            long long w = neighbor->weight;
            int edgeIdx = neighbor->edgeIndex;
            if (dist[u] + w == dist[v] || dist[v] + w == dist[u]) {
                answer[edgeIdx] = true;
            }
            neighbor = neighbor->next;
        }
    }
    *returnSize = edgesSize;
    // Free memory
    for (int i = 0; i < n; i++) {
        AdjNode* curr = graph[i];
        while (curr) {
            AdjNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph);
    free(dist);
    free(heap);
    return answer;
}
