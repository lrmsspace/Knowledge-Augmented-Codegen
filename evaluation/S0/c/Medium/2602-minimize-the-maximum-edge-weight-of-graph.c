// Source: https://leetcode.com/problems/minimize-the-maximum-edge-weight-of-graph/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers, n and threshold, as well as a directed weighted graph of n nodes numbered from 0 to n - 1. The graph is represented by a 2D integer array edges, where edges[i] = [Ai, Bi, Wi] indicates that there is an edge going from node Ai to node Bi with weight Wi.
//
// You have to remove some edges from this graph (possibly none), so that it satisfies the following conditions:
//
//
// 	Node 0 must be reachable from all other nodes.
// 	The maximum edge weight in the resulting graph is minimized.
// 	Each node has at most threshold outgoing edges.
//
//
// Return the minimum possible value of the maximum edge weight after removing the necessary edges. If it is impossible for all conditions to be satisfied, return -1.
//
// Example:
// Input: n = 5, edges = [[1,0,1],[2,0,2],[3,0,1],[4,3,1],[2,1,1]], threshold = 2
//
// Output: 1
//
// Explanation:
//
//
//
// Remove the edge 2 -> 0. The maximum weight among the remaining edges is 1.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= threshold <= n - 1
// 	1 <= edges.length <= min(105, n * (n - 1) / 2).
// 	edges[i].length == 3
// 	0 <= Ai, Bi < n
// 	Ai != Bi
// 	1 <= Wi <= 106
// 	There may be multiple edges between a pair of nodes, but they must have unique weights.
//

int minMaxWeight(int n, int** edges, int edgesSize, int* edgesColSize, int threshold) {
    // Adjacency list representation of the graph
    typedef struct Edge {
        int to;
        int weight;
        struct Edge* next;
    } Edge;

    Edge** graph = (Edge**)calloc(n, sizeof(Edge*));
    for (int i = 0; i < edgesSize; i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        int weight = edges[i][2];

        Edge* edge = (Edge*)malloc(sizeof(Edge));
        edge->to = to;
        edge->weight = weight;
        edge->next = graph[from];
        graph[from] = edge;
    }

    // Function to perform DFS and check reachability
    int* outDegree = (int*)calloc(n, sizeof(int));
    int visited[n];
    memset(visited, 0, sizeof(visited));

    void dfs(int node) {
        visited[node] = 1;
        Edge* edge = graph[node];
        while (edge) {
            if (!visited[edge->to]) {
                dfs(edge->to);
            }
            edge = edge->next;
        }
    }

    dfs(0);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return -1; // Node i is not reachable from node 0
        }
    }

    // Check outgoing edges constraint
    for (int i = 0; i < n; i++) {
        int count = 0;
        Edge* edge = graph[i];
        while (edge) {
            count++;
            edge = edge->next;
        }
        if (count > threshold) {
            return -1; // Node i has more than threshold outgoing edges
        }
    }

    // Find the maximum edge weight
    int maxWeight = 0;
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][2] > maxWeight) {
            maxWeight = edges[i][2];
        }
    }

    // Clean up memory
    for (int i = 0; i < n; i++) {
        Edge* edge = graph[i];
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(graph);
    free(outDegree);

    return maxWeight;
}
