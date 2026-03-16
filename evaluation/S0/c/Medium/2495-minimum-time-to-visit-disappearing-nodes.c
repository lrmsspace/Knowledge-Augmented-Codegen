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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minimumTime(int n, int** edges, int edgesSize, int* edgesColSize, int* disappear, int disappearSize, int* returnSize) {
    #define MAX_NODES 50000
    #define MAX_EDGES 100000
    #define INF 1000000000

    typedef struct {
        int to;
        int length;
        struct Edge* next;
    } Edge;

    Edge* graph[MAX_NODES] = {0};
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int length = edges[i][2];

        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = v;
        edge1->length = length;
        edge1->next = graph[u];
        graph[u] = edge1;

        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = u;
        edge2->length = length;
        edge2->next = graph[v];
        graph[v] = edge2;
    }

    int* dist = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[0] = 0;

    typedef struct {
        int node;
        int time;
    } HeapNode;

    HeapNode minHeap[MAX_NODES];
    int heapSize = 0;

    void push(int node, int time) {
        minHeap[heapSize].node = node;
        minHeap[heapSize].time = time;
        int idx = heapSize++;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (minHeap[parent].time <= minHeap[idx].time) break;
            HeapNode temp = minHeap[parent];
            minHeap[parent] = minHeap[idx];
            minHeap[idx] = temp;
            idx = parent;
        }
    }

    HeapNode pop() {
        HeapNode top = minHeap[0];
        minHeap[0] = minHeap[--heapSize];
        int idx = 0;
        while (true) {
            int left = idx * 2 + 1;
            int right = idx * 2 + 2;
            int smallest = idx;
            if (left < heapSize && minHeap[left].time < minHeap[smallest].time) {
                smallest = left;
            }
            if (right < heapSize && minHeap[right].time < minHeap[smallest].time) {
                smallest = right;
            }
            if (smallest == idx) break;
            HeapNode temp = minHeap[smallest];
            minHeap[smallest] = minHeap[idx];
            minHeap[idx] = temp;
            idx = smallest;
        }
        return top;
    }
    push(0, 0);
    while (heapSize > 0) {
        HeapNode current = pop();
        int u = current.node;
        int currentTime = current.time;

        if (currentTime > dist[u]) continue;

        for (Edge* edge = graph[u]; edge != NULL; edge = edge->next) {
            int v = edge->to;
            int travelTime = edge->length;
            int arrivalTime = currentTime + travelTime;

            if (arrivalTime < disappear[v] && arrivalTime < dist[v]) {
                dist[v] = arrivalTime;
                push(v, arrivalTime);
            }
        }
    }
    int* result = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            result[i] = -1;
        } else {
            result[i] = dist[i];
        }
    }
    *returnSize = n;
    return result;
}
