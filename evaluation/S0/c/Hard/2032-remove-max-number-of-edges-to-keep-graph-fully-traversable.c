// Source: https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/   |   Difficulty: Hard
//
// Problem Description:
// Alice and Bob have an undirected graph of n nodes and three types of edges:
//
//
// 	Type 1: Can be traversed by Alice only.
// 	Type 2: Can be traversed by Bob only.
// 	Type 3: Can be traversed by both Alice and Bob.
//
//
// Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.
//
// Return the maximum number of edges you can remove, or return -1 if Alice and Bob cannot fully traverse the graph.
//
// Example:
// Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
// Output: 2
// Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= edges.length <= min(105, 3 * n * (n - 1) / 2)
// 	edges[i].length == 3
// 	1 <= typei <= 3
// 	1 <= ui < vi <= n
// 	All tuples (typei, ui, vi) are distinct.
//

int maxNumEdgesToRemove(int n, int** edges, int edgesSize, int* edgesColSize) {
    int parentA[n+1], parentB[n+1];
    int rankA[n+1], rankB[n+1];
    for (int i = 1; i <= n; ++i) {
        parentA[i] = i; parentB[i] = i;
        rankA[i] = 0; rankB[i] = 0;
    }

    int usedEdges = 0;

    /* Find with path compression */
    int find(int *parent, int u) {
        if (parent[u] != u) {
            parent[u] = find(parent, parent[u]);
        }
        return parent[u];
    }

    /* Union by rank */
    int unionSets(int *parent, int *rank, int u, int v) {
        int pu = find(parent, u);
        int pv = find(parent, v);
        if (pu == pv) return 0; /* already connected */

        if (rank[pu] < rank[pv]) {
            parent[pu] = pv;
        } else if (rank[pu] > rank[pv]) {
            parent[pv] = pu;
        } else {
            parent[pv] = pu;
            rank[pu]++;
        }
        return 1; /* union done */
    }

    /* First process type 3 edges */
    for (int i = 0; i < edgesSize; ++i) {
        if (edges[i][0] == 3) {
            if (unionSets(parentA, rankA, edges[i][1], edges[i][2])) {
                unionSets(parentB, rankB, edges[i][1], edges[i][2]);
                usedEdges++;
            }
        }
    }

    /* Then process type 1 and type 2 edges */
    for (int i = 0; i < edgesSize; ++i) {
        if (edges[i][0] == 1) {
            if (unionSets(parentA, rankA, edges[i][1], edges[i][2])) {
                usedEdges++;
            }
        } else if (edges[i][0] == 2) {
            if (unionSets(parentB, rankB, edges[i][1], edges[i][2])) {
                usedEdges++;
            }
        }
    }

    /* Check if both Alice and Bob can traverse the entire graph */
    for (int i = 2; i <= n; ++i) {
        if (find(parentA, i) != find(parentA, 1) || find(parentB, i) != find(parentB, 1)) {
            return -1;
        }
    }
    return edgesSize - usedEdges;
}
