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

int reachableNodes(int** edges, int edgesSize, int* edgesColSize, int maxMoves, int n) {
    #define INF 0x3f3f3f3f
    typedef struct {
        int node;
        int dist;
    } HeapNode;

    typedef struct {
        HeapNode* data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createMinHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (HeapNode*)malloc(capacity * sizeof(HeapNode));
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void swap(HeapNode* a, HeapNode* b) {
        HeapNode temp = *a;
        *a = *b;
        *b = temp;
    }

    void minHeapify(MinHeap* heap, int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < heap->size && heap->data[left].dist < heap->data[smallest].dist)
            smallest = left;
        if (right < heap->size && heap->data[right].dist < heap->data[smallest].dist)
            smallest = right;

        if (smallest != idx) {
            swap(&heap->data[smallest], &heap->data[idx]);
            minHeapify(heap, smallest);
        }
    }
    void insertMinHeap(MinHeap* heap, HeapNode node) {
        if (heap->size == heap->capacity) return; // Heap full
        heap->data[heap->size++] = node;
        int idx = heap->size - 1;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap->data[parent].dist <= heap->data[idx].dist) break;
            swap(&heap->data[parent], &heap->data[idx]);
            idx = parent;
        }
    }
    HeapNode extractMin(MinHeap* heap) {
        HeapNode minNode = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        minHeapify(heap, 0);
        return minNode;
    }
    // Build adjacency list
    int** adj = (int**)malloc(n * sizeof(int*));
    int* adjSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        adj[i] = (int*)malloc(n * sizeof(int));
    }
    int** weight = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        weight[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) {
            weight[i][j] = INF;
        }
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1], cnt = edges[i][2];
        adj[u][adjSize[u]++] = v;
        adj[v][adjSize[v]++] = u;
        weight[u][v] = cnt + 1;
        weight[v][u] = cnt + 1;
    }
    // Dijkstra's algorithm
    int* dist = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        dist[i] = INF;
    }
    dist[0] = 0;
    MinHeap* heap = createMinHeap(n * n);
    insertMinHeap(heap, (HeapNode){0, 0});
    while (heap->size > 0) {
        HeapNode current = extractMin(heap);
        int u = current.node;
        int d = current.dist;
        if (d > dist[u]) continue;
        for (int i = 0; i < adjSize[u]; ++i) {
            int v = adj[u][i];
            int w = weight[u][v];
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                insertMinHeap(heap, (HeapNode){v, dist[v]});
            }
        }
    }

    // Count reachable nodes
    int result = 0;
    for (int i = 0; i < n; ++i) {
        if (dist[i] <= maxMoves) {
            result++; // Original node is reachable
        }
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1], cnt = edges[i][2];
        int usedFromU = 0, usedFromV = 0;
        if (dist[u] <= maxMoves) {
            usedFromU = maxMoves - dist[u];
            if (usedFromU > cnt) usedFromU = cnt;
        }
        if (dist[v] <= maxMoves) {
            usedFromV = maxMoves - dist[v];
            if (usedFromV > cnt) usedFromV = cnt;
        }
        result += (usedFromU + usedFromV > cnt) ? cnt : (usedFromU + usedFromV);
    }
    // Cleanup
    for (int i = 0; i < n; ++i) {
        free(adj[i]);
        free(weight[i]);
    }
    free(adj);
    free(adjSize);
    free(weight);
    free(dist);
    free(heap->data);
    free(heap);
    return result;
}
