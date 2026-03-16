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
// Helpful references (internal KB):
// - Shortest Paths (graph, heap, dijkstra, greedy)
//   • When to use: When finding the shortest path from a single source vertex to all other vertices in a weighted graph. It is specifically applicable when all edge weights are non-negative.
//   • Idea: Dijkstra's algorithm computes the shortest paths from a single source vertex to all other vertices in a weighted graph with non-negative edge weights. It uses a greedy approach with a priority queue, achieving a typical time complexity of O(E log V) or O(E + V log V).
//   • Invariants: For any vertex v extracted from the priority queue, distTo[v] is the shortest path distance from the source.; The distTo array always stores the shortest known distance from the source to each vertex found so far.
//   • Tips: Use a min-priority queue to efficiently extract the vertex with the smallest current distance.; Initialize source distance to 0 and all other distances to infinity.
//   • Pitfalls: Fails if the graph contains any negative edge weights; use Bellman-Ford or SPFA instead.; Inefficient priority queue implementation can degrade performance significantly.
// - Floyd-Warshall Algorithm (graph, matrix, floyd-warshall, dp-2d)
//   • When to use: Use when needing to find the shortest paths between all pairs of vertices in a weighted graph, especially if negative edge weights are present but no negative cycles.
//   • Idea: The Floyd-Warshall algorithm is a dynamic programming approach that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path lengths, achieving an O(N^3) time complexity.
//   • Invariants: After k iterations, d[i][j] stores the shortest path from i to j using only vertices {1, ..., k} as intermediate nodes.; d[i][j] always represents a valid path length or infinity, never an invalid negative value unless a negative cycle is detected.
//   • Tips: Initialize direct edge weights and infinity for non-existent edges.; Set distance from a vertex to itself to zero initially.
//   • Pitfalls: Incorrect loop order (k must be outermost) will yield incorrect results.; Improper handling of 'infinity' values can lead to overflow or incorrect comparisons.
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

long long minimumWeight(int n, int** edges, int edgesSize, int* edgesColSize, int src1, int src2, int dest) {
    #define MAX_NODES 100000
    #define INF 1000000000000000LL

    /* Adjacency list representation */
    typedef struct {
        int to;
        int weight;
        struct AdjNode* next;
    } AdjNode;

    AdjNode* createAdjList(int n, int** edges, int edgesSize) {
        AdjNode** adjList = (AdjNode**)calloc(n, sizeof(AdjNode*));
        for (int i = 0; i < edgesSize; ++i) {
            int from = edges[i][0];
            int to = edges[i][1];
            int weight = edges[i][2];
            AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
            newNode->to = to;
            newNode->weight = weight;
            newNode->next = adjList[from];
            adjList[from] = newNode;
        }
        return adjList;
    }

    /* Dijkstra's algorithm */
    long long* dijkstra(AdjNode** adjList, int n, int start) {
        long long* dist = (long long*)malloc(n * sizeof(long long));
        for (int i = 0; i < n; ++i) dist[i] = INF;
        dist[start] = 0;

        typedef struct {
            int node;
            long long dist;
        } HeapNode;

        HeapNode* heap = (HeapNode*)malloc(n * sizeof(HeapNode));
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
                if (left < heapSize && heap[left].dist < heap[smallest].dist) smallest = left;
                if (right < heapSize && heap[right].dist < heap[smallest].dist) smallest = right;
                if (smallest == idx) break;
                HeapNode temp = heap[smallest];
                heap[smallest] = heap[idx];
                heap[idx] = temp;
                idx = smallest;
            }
            return top;
        }

        push(start, 0);
        while (heapSize > 0) {
            HeapNode current = pop();
            int u = current.node;
            long long d = current.dist;
            if (d > dist[u]) continue;

            for (AdjNode* neighbor = adjList[u]; neighbor != NULL; neighbor = neighbor->next) {
                int v = neighbor->to;
                long long weight = neighbor->weight;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    push(v, dist[v]);
                }
            }
        }

        free(heap);
        return dist;
    }
    /* Create adjacency list for original and reversed graph */
    AdjNode** adjList = createAdjList(n, edges, edgesSize); 
    AdjNode** revAdjList = createAdjList(n, edges, edgesSize);
    for (int i = 0; i < edgesSize; ++i) {
        int from = edges[i][0];
        int to = edges[i][1];
        int weight = edges[i][2];
        AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
        newNode->to = from;
        newNode->weight = weight;
        newNode->next = revAdjList[to];
        revAdjList[to] = newNode;
    }
    /* Run Dijkstra from src1, src2 and dest (on reversed graph) */
    long long* distFromSrc1 = dijkstra(adjList, n, src1);
    long long* distFromSrc2 = dijkstra(adjList, n, src2);
    long long* distToDest = dijkstra(revAdjList, n, dest);
    /* Find minimum weight */
    long long minWeight = INF;
    for (int i = 0; i < n; ++i) {
        if (distFromSrc1[i] != INF && distFromSrc2[i] != INF && distToDest[i] != INF) {
            long long total = distFromSrc1[i] + distFromSrc2[i] + distToDest[i];
            if (total < minWeight) {
                minWeight = total;
            }
        }
    }
    /* Free memory */
    for (int i = 0; i < n; ++i) {
        AdjNode* node = adjList[i];
        while (node) {
            AdjNode* temp = node;
            node = node->next;
            free(temp);
        }
        node = revAdjList[i];
        while (node) {
            AdjNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(adjList);
    free(revAdjList);
    free(distFromSrc1);
    free(distFromSrc2);
    free(distToDest);   
    return (minWeight == INF) ? -1 : minWeight;
}
