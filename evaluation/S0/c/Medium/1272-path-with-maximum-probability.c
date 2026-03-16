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

double maxProbability(int n, int** edges, int edgesSize, int* edgesColSize, double* succProb, int succProbSize, int start_node, int end_node) {
    // Create adjacency list
    typedef struct {
        int node;
        double prob;
    } Edge;

    Edge** graph = (Edge**)calloc(n, sizeof(Edge*));
    int* graphSizes = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        double p = succProb[i];

        graph[u] = (Edge*)realloc(graph[u], (graphSizes[u] + 1) * sizeof(Edge));
        graph[u][graphSizes[u]++] = (Edge){v, p};

        graph[v] = (Edge*)realloc(graph[v], (graphSizes[v] + 1) * sizeof(Edge));
        graph[v][graphSizes[v]++] = (Edge){u, p};
    }

    // Dijkstra's algorithm to find max probability path
    double* maxProb = (double*)calloc(n, sizeof(double));
    maxProb[start_node] = 1.0;

    typedef struct {
        int node;
        double prob;
    } HeapNode;

    HeapNode* heap = (HeapNode*)malloc(n * sizeof(HeapNode));
    int heapSize = 0;

    void heapPush(int node, double prob) {
        heap[heapSize++] = (HeapNode){node, prob};
        int idx = heapSize - 1;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap[parent].prob >= heap[idx].prob) break;
            HeapNode temp = heap[parent];
            heap[parent] = heap[idx];
            heap[idx] = temp;
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
            int largest = idx;
            if (left < heapSize && heap[left].prob > heap[largest].prob) largest = left;
            if (right < heapSize && heap[right].prob > heap[largest].prob) largest = right;
            if (largest == idx) break;
            HeapNode temp = heap[largest];
            heap[largest] = heap[idx];
            heap[idx] = temp;
            idx = largest;
        }
        return top;
    }
    heapPush(start_node, 1.0);
    while (heapSize > 0) {
        HeapNode current = heapPop();
        int u = current.node;
        double prob = current.prob;

        if (u == end_node) {
            // Free allocated memory
            for (int i = 0; i < n; i++) {
                free(graph[i]);
            }
            free(graph);
            free(graphSizes);
            free(maxProb);
            free(heap);
            return prob;
        }

        for (int i = 0; i < graphSizes[u]; i++) {
            Edge edge = graph[u][i];
            int v = edge.node;
            double newProb = prob * edge.prob;
            if (newProb > maxProb[v]) {
                maxProb[v] = newProb;
                heapPush(v, newProb);
            }
        }
    }
    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphSizes);
    free(maxProb);
    free(heap);
    return 0.0;
}
