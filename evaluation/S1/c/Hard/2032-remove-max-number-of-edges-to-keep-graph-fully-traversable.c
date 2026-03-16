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
// Helpful references (internal KB):
// - Finding Bridges Online (graph, ds, union-find, counting)
//   • When to use: Use when edges are added one by one to an initially empty graph and you need to efficiently track the number of bridges or 2-edge-connected components after each addition.
//   • Idea: This algorithm dynamically maintains the number of bridges in an undirected graph as edges are added incrementally. It leverages a Disjoint Set Union (DSU) data structure to achieve an amortized time complexity of O((N+M) log N).
//   • Invariants: Each DSU set represents a 2-edge-connected component or a collection of such components connected by bridges.; The total count of bridges accurately reflects edges whose removal increases connected components.
//   • Tips: Understand the properties of 2-edge-connected components and how they relate to bridges.; Carefully manage DSU operations, including path compression and union by rank/size, for optimal performance.
//   • Pitfalls: Incorrectly updating the bridge count after an edge addition, especially when cycles are formed.; Inefficient DSU operations leading to a higher than expected time complexity.
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
// - Minimum Spanning Trees (graph, greedy)
//   • When to use: When you need to find a subset of edges in a connected, edge-weighted graph that connects all vertices with the minimum possible total edge weight. Useful for network design problems where minimizing connection costs is crucial.
//   • Idea: A Minimum Spanning Tree (MST) algorithm finds a subset of edges in an edge-weighted graph that connects all vertices with the minimum possible total weight, forming a tree. This is typically solved using greedy approaches with a time complexity often involving sorting edges or using a priority queue.
//   • Invariants: The set of edges selected so far always forms a forest.; Each connected component formed by the chosen edges is a valid subtree of some Minimum Spanning Tree.
//   • Tips: Greedy approaches often work by iteratively adding the cheapest valid edge or expanding from a starting vertex.; The cut property and cycle property are fundamental for proving correctness of MST algorithms.
//   • Pitfalls: Assuming the graph is always connected; disconnected graphs require finding a minimum spanning forest.; Incorrectly applying the greedy choice without ensuring it maintains the MST property (e.g., creating a cycle).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxNumEdgesToRemove(int n, int** edges, int edgesSize, int* edgesColSize) {
    // Disjoint Set Union (Union-Find) structure
    typedef struct DSU {
        int *parent;
        int *rank;
        int count; // number of connected components
    } DSU;

    DSU* createDSU(int size) {
        DSU* dsu = (DSU*)malloc(sizeof(DSU));
        dsu->parent = (int*)malloc(size * sizeof(int));
        dsu->rank = (int*)calloc(size, sizeof(int));
        dsu->count = size;
        for (int i = 0; i < size; i++) {
            dsu->parent[i] = i;
        }
        return dsu;
    }

    int find(DSU* dsu, int x) {
        if (dsu->parent[x] != x) {
            dsu->parent[x] = find(dsu, dsu->parent[x]);
        }
        return dsu->parent[x];
    }

    int unionSets(DSU* dsu, int x, int y) {
        int rootX = find(dsu, x);
        int rootY = find(dsu, y);
        if (rootX != rootY) {
            if (dsu->rank[rootX] > dsu->rank[rootY]) {
                dsu->parent[rootY] = rootX;
            } else if (dsu->rank[rootX] < dsu->rank[rootY]) {
                dsu->parent[rootX] = rootY;
            } else {
                dsu->parent[rootY] = rootX;
                dsu->rank[rootX]++;
            }
            dsu->count--;
            return 1; // union successful
        }
        return 0; // already connected
    }

    void freeDSU(DSU* dsu) {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu);
    }

    // Create DSUs for Alice and Bob
    DSU* aliceDSU = createDSU(n);
    DSU* bobDSU = createDSU(n);

    int edgesUsed = 0;

    // First, add all type 3 edges
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][0] == 3) {
            int u = edges[i][1] - 1;
            int v = edges[i][2] - 1;
            if (unionSets(aliceDSU, u, v) | unionSets(bobDSU, u, v)) {
                edgesUsed++;
            }
        }
    }
    // Then, add type 1 edges for Alice
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][0] == 1) {
            int u = edges[i][1] - 1;
            int v = edges[i][2] - 1;
            if (unionSets(aliceDSU, u, v)) {
                edgesUsed++;
            }
        }
    }
    // Finally, add type 2 edges for Bob
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][0] == 2) {
            int u = edges[i][1] - 1;
            int v = edges[i][2] - 1;
            if (unionSets(bobDSU, u, v)) {
                edgesUsed++;
            }
        }
    }
    // Check if both Alice and Bob can traverse the entire graph
    if (aliceDSU->count != 1 || bobDSU->count != 1) {
        freeDSU(aliceDSU);
        freeDSU(bobDSU);
        return -1;
    }   
    freeDSU(aliceDSU);
    freeDSU(bobDSU);
    return edgesSize - edgesUsed;
}
