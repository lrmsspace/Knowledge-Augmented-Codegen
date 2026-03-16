// Source: https://leetcode.com/problems/network-delay-time/   |   Difficulty: Medium
//
// Problem Description:
// You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.
//
// We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.
//
// Example:
// Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
// Output: 2
//
// Constraints:
// 1 <= k <= n <= 100
// 	1 <= times.length <= 6000
// 	times[i].length == 3
// 	1 <= ui, vi <= n
// 	ui != vi
// 	0 <= wi <= 100
// 	All the pairs (ui, vi) are unique. (i.e., no multiple edges.)
//
// Helpful references (internal KB):
// - Dijkstra on sparse graphs (heap, queue, dijkstra)
//   • When to use: When you need to find the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights, especially efficient for sparse graphs.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source to all other vertices in a weighted graph with non-negative edge weights. It uses a priority queue to greedily explore vertices, achieving O(E log V) complexity with a binary heap.
//   • Invariants: At the start of each iteration, dist[u] holds the shortest distance found so far from the source to u.; All vertices already extracted from the priority queue have their final shortest distance determined.
//   • Tips: Use a priority queue (min-heap) to efficiently retrieve the unvisited vertex with the smallest distance.; Initialize all distances to infinity and the source distance to zero.
//   • Pitfalls: Does not work correctly with negative edge weights; Bellman-Ford or SPFA is needed.; Forgetting to mark vertices as visited or handle duplicate entries in the priority queue can lead to incorrectness or TLE.
// - Solving assignment problem using min-cost-flow (graph, dijkstra, bellman-ford)
//   • When to use: Use when finding a one-to-one assignment between two sets of entities, such as workers to tasks, to minimize the total cost. It's suitable for problems modelable as min-cost max-flow in a bipartite graph.
//   • Idea: This technique models the assignment problem as a minimum cost maximum flow problem on a specially constructed bipartite graph. It finds a perfect matching with the lowest total cost, typically with a polynomial time complexity depending on the shortest path algorithm used.
//   • Invariants: Flow conservation holds for all intermediate nodes in the network.; The flow on any edge never exceeds its defined capacity.
//   • Tips: Construct a bipartite graph with a source and sink nodes.; Set capacities to 1 for all assignment-related edges to ensure one-to-one mapping.
//   • Pitfalls: Incorrectly modeling capacities or costs on graph edges can lead to wrong solutions.; Forgetting to ensure a perfect matching (flow value equals N) is found for a complete assignment.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k){
    // Dijkstra's algorithm implementation
    #define MAXN 101
    #define INF 0x3f3f3f3f

    typedef struct {
        int node;
        int dist;
    } HeapNode;

    typedef struct {
        HeapNode data[MAXN * MAXN];
        int size;
    } MinHeap;

    void heapInit(MinHeap* heap) {
        heap->size = 0;
    }

    void heapPush(MinHeap* heap, int node, int dist) {
        HeapNode hn = {node, dist};
        heap->data[heap->size++] = hn;
        int i = heap->size - 1;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap->data[parent].dist <= heap->data[i].dist) break;
            HeapNode temp = heap->data[parent];
            heap->data[parent] = heap->data[i];
            heap->data[i] = temp;
            i = parent;
        }
    }

    HeapNode heapPop(MinHeap* heap) {
        HeapNode root = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        int i = 0;
        while (1) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            if (left < heap->size && heap->data[left].dist < heap->data[smallest].dist) {
                smallest = left;
            }
            if (right < heap->size && heap->data[right].dist < heap->data[smallest].dist) {
                smallest = right;
            }
            if (smallest == i) break;
            HeapNode temp = heap->data[i];
            heap->data[i] = heap->data[smallest];
            heap->data[smallest] = temp;
            i = smallest;
        }
        return root;
    }
    int graph[MAXN][MAXN];
    int dist[MAXN];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
        dist[i] = INF;
    }
    for (int i = 0; i < timesSize; i++) {
        int u = times[i][0];
        int v = times[i][1];
        int w = times[i][2];
        graph[u][v] = w;
    }
    MinHeap heap;
    heapInit(&heap);
    dist[k] = 0;
    heapPush(&heap, k, 0);
    while (heap.size > 0) {
        HeapNode hn = heapPop(&heap);
        int u = hn.node;
        int d = hn.dist;
        if (d > dist[u]) continue;
        for (int v = 1; v <= n; v++) {
            if (graph[u][v] != INF) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    heapPush(&heap, v, dist[v]);
                }
            }
        }
    }
    int maxDist = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) {
            return -1;
        }
        if (dist[i] > maxDist) {
            maxDist = dist[i];
        }
    }
    return maxDist;
}
