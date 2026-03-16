// Source: https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n denoting the number of nodes of a weighted directed graph. The nodes are numbered from 0 to n - 1.
//
// You are also given a 2D integer array edges where edges[i] = [fromi, toi, weighti] denotes that there exists a directed edge from fromi to toi with weight weighti.
//
// Lastly, you are given three distinct integers src1, src2, and dest denoting three distinct nodes of the graph.
//
// Return the minimum weight of a subgraph of the graph such that it is possible to reach dest from both src1 and src2 via a set of edges of this subgraph. In case such a subgraph does not exist, return -1.
//
// A subgraph is a graph whose vertices and edges are subsets of the original graph. The weight of a subgraph is the sum of weights of its constituent edges.
//
// Example:
// Input: n = 6, edges = [[0,2,2],[0,5,6],[1,0,3],[1,4,5],[2,1,1],[2,3,3],[2,3,4],[3,4,2],[4,5,1]], src1 = 0, src2 = 1, dest = 5
// Output: 9
// Explanation:
// The above figure represents the input graph.
// The blue edges represent one of the subgraphs that yield the optimal answer.
// Note that the subgraph [[1,0,3],[0,5,6]] also yields the optimal answer. It is not possible to get a subgraph with less weight satisfying all the constraints.
//
// Constraints:
// 3 <= n <= 105
// 	0 <= edges.length <= 105
// 	edges[i].length == 3
// 	0 <= fromi, toi, src1, src2, dest <= n - 1
// 	fromi != toi
// 	src1, src2, and dest are pairwise distinct.
// 	1 <= weight[i] <= 105
//

long long minimumWeight(int n, int** edges, int edgesSize, int* edgesColSize, int src1, int src2, int dest) {
    /* Dijkstra's algorithm implementation */
    typedef struct AdjNode {
        int to;
        int weight;
        struct AdjNode *next;
    } AdjNode;

    typedef struct {
        AdjNode **heads;
        int size;
    } Graph;

    Graph* createGraph(int n) {
        Graph *graph = (Graph*)malloc(sizeof(Graph));
        graph->heads = (AdjNode**)calloc(n, sizeof(AdjNode*));
        graph->size = n;
        return graph;
    }

    void addEdge(Graph *graph, int from, int to, int weight) {
        AdjNode *node = (AdjNode*)malloc(sizeof(AdjNode));
        node->to = to;
        node->weight = weight;
        node->next = graph->heads[from];
        graph->heads[from] = node;
    }

    void freeGraph(Graph *graph) {
        for (int i = 0; i < graph->size; i++) {
            AdjNode *curr = graph->heads[i];
            while (curr) {
                AdjNode *temp = curr;
                curr = curr->next;
                free(temp);
            }
        }
        free(graph->heads);
        free(graph);
    }

    long long* dijkstra(Graph *graph, int start) {
        long long *dist = (long long*)malloc(graph->size * sizeof(long long));
        for (int i = 0; i < graph->size; i++) dist[i] = 1e15;
        dist[start] = 0;

        typedef struct {
            int node;
            long long dist;
        } HeapNode;

        HeapNode *heap = (HeapNode*)malloc(graph->size * sizeof(HeapNode));
        int heapSize = 0;

        void push(int node, long long d) {
            heap[heapSize].node = node;
            heap[heapSize].dist = d;
            int idx = heapSize++;
            while (idx > 0) {
                int parent = (idx - 1) / 2;
                if (heap[parent].dist <= heap[idx].dist) break;
                HeapNode temp = heap[parent];
                heap[parent] = heap[idx];
                heap[idx] = temp;
                idx = parent;
            }
        }

        HeapNode pop() {
            HeapNode top = heap[0];
            heap[0] = heap[--heapSize];   
            int idx = 0;
            while (1) {
                int left = 2 * idx + 1;
                int right = 2 * idx + 2;
                int smallest = idx;
                if (left < heapSize && heap[left].dist < heap[smallest].dist) {
                    smallest = left;
                }
                if (right < heapSize && heap[right].dist < heap[smallest].dist) {
                    smallest = right;
                }
                if (smallest == idx) break;
                HeapNode temp = heap[idx];
                heap[idx] = heap[smallest];
                heap[smallest] = temp;
                idx = smallest;
            }
            return top;
        }
        push(start, 0);
        while (heapSize > 0) {
            HeapNode curr = pop();
            if (curr.dist > dist[curr.node]) continue;
            AdjNode *adj = graph->heads[curr.node];
            while (adj) {
                if (dist[adj->to] > dist[curr.node] + adj->weight) {
                    dist[adj->to] = dist[curr.node] + adj->weight;
                    push(adj->to, dist[adj->to]);
                }
                adj = adj->next;
            }
        }
        free(heap);
        return dist;
    }
    Graph *graph = createGraph(n);
    Graph *revGraph = createGraph(n);
    for (int i = 0; i < edgesSize; i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        int weight = edges[i][2];
        addEdge(graph, from, to, weight);
        addEdge(revGraph, to, from, weight);
    }
    long long *distFromSrc1 = dijkstra(graph, src1);
    long long *distFromSrc2 = dijkstra(graph, src2);
    long long *distToDest = dijkstra(revGraph, dest);
    long long minWeight = 1e15;
    for (int i = 0; i < n; i++) {
        if (distFromSrc1[i] == 1e15 || distFromSrc2[i] == 1e15 || distToDest[i] == 1e15) continue;
        long long totalDist = distFromSrc1[i] + distFromSrc2[i] + distToDest[i];
        if (totalDist < minWeight) {
            minWeight = totalDist;
        }
    }
    freeGraph(graph);
    freeGraph(revGraph);
    free(distFromSrc1);
    free(distFromSrc2);
    free(distToDest);
    return (minWeight == 1e15) ? -1 : (int)minWeight;  
}
