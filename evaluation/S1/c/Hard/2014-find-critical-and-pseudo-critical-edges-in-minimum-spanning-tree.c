// Source: https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/   |   Difficulty: Hard
//
// Problem Description:
// Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional and weighted edge between nodes ai and bi. A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.
//
// Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST). An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge. On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.
//
// Note that you can return the indices of the edges in any order.
//
// Example:
// Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
// Output: [[0,1],[2,3,4,5]]
// Explanation: The figure above describes the graph.
// The following figure shows all the possible MSTs:
//
// Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first list of the output.
// The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical edges. We add them to the second list of the output.
//
// Constraints:
// 2 <= n <= 100
// 	1 <= edges.length <= min(200, n * (n - 1) / 2)
// 	edges[i].length == 3
// 	0 <= ai < bi < n
// 	1 <= weighti <= 1000
// 	All pairs (ai, bi) are distinct.
//
// Helpful references (internal KB):
// - Minimum spanning tree - Kruskal with Disjoint Set Union (graph, ds, mst-kruskal, union-find)
//   • When to use: Use when you need to find a minimum spanning tree in a graph, especially when the graph is sparse or the number of edges is not excessively large compared to vertices.
//   • Idea: Sorts all graph edges by weight and iteratively adds the cheapest edge that connects two previously disconnected components using a Disjoint Set Union (DSU) data structure. This process builds an MST with O(M log M) or O(M log N) time complexity.
//   • Invariants: After processing k edges, the chosen edges form a forest where each tree is a component of the MST.; Any edge not yet processed has a weight greater than or equal to all processed edges.
//   • Tips: Sort edges by weight in non-decreasing order.; Initialize DSU such that each vertex is in its own set.
//   • Pitfalls: Forgetting to sort edges, leading to an incorrect MST.; Inefficient DSU implementation without path compression or union by rank/size.
// - Finding bridges in a graph in O(N+M) (graph, dfs)
//   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
//   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
//   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
//   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
//   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
// - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
//   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
//   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
//   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
//   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
//   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

// Union-Find (Disjoint Set Union) structure
typedef struct {
    int *parent;
    int *rank;
} DSU;

DSU* createDSU(int n) {
    DSU *dsu = (DSU*)malloc(sizeof(DSU));
    dsu->parent = (int*)malloc(n * sizeof(int));
    dsu->rank = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
    }
    return dsu;
}

int find(DSU *dsu, int x) {
    if (dsu->parent[x] != x) {
        dsu->parent[x] = find(dsu, dsu->parent[x]); // path compression
    }
    return dsu->parent[x];
}

int unionSets(DSU *dsu, int x, int y) {
    int px = find(dsu, x);
    int py = find(dsu, y);
    if (px == py) return 0; // already connected
    
    // union by rank
    if (dsu->rank[px] < dsu->rank[py]) {
        dsu->parent[px] = py;
    } else if (dsu->rank[px] > dsu->rank[py]) {
        dsu->parent[py] = px;
    } else {
        dsu->parent[py] = px;
        dsu->rank[px]++;
    }
    return 1;
}

void freeDSU(DSU *dsu) {
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
}

// Edge structure with index
typedef struct {
    int u, v, weight, index;
} Edge;

// Comparator for sorting edges by weight
int compareEdges(const void *a, const void *b) {
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    return ea->weight - eb->weight;
}

// Compute MST weight, optionally excluding or forcing an edge
int computeMST(int n, Edge *sortedEdges, int edgesSize, int excludeIdx, int forceIdx) {
    DSU *dsu = createDSU(n);
    int weight = 0;
    int edgeCount = 0;
    
    // Force the edge if specified
    if (forceIdx != -1) {
        if (unionSets(dsu, sortedEdges[forceIdx].u, sortedEdges[forceIdx].v)) {
            weight += sortedEdges[forceIdx].weight;
            edgeCount++;
        }
    }
    
    // Add edges using Kruskal's algorithm
    for (int i = 0; i < edgesSize && edgeCount < n - 1; i++) {
        if (i == excludeIdx || i == forceIdx) continue;
        
        if (unionSets(dsu, sortedEdges[i].u, sortedEdges[i].v)) {
            weight += sortedEdges[i].weight;
            edgeCount++;
        }
    }
    
    freeDSU(dsu);
    
    // If we couldn't form a spanning tree, return -1
    return (edgeCount == n - 1) ? weight : -1;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findCriticalAndPseudoCriticalEdges(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize, int** returnColumnSizes) {
    // Create sorted edges with original indices
    Edge *sortedEdges = (Edge*)malloc(edgesSize * sizeof(Edge));
    for (int i = 0; i < edgesSize; i++) {
        sortedEdges[i].u = edges[i][0];
        sortedEdges[i].v = edges[i][1];
        sortedEdges[i].weight = edges[i][2];
        sortedEdges[i].index = i;
    }
    qsort(sortedEdges, edgesSize, sizeof(Edge), compareEdges);
    
    // Compute the weight of the original MST
    int originalMSTWeight = computeMST(n, sortedEdges, edgesSize, -1, -1);
    
    // Lists to store critical and pseudo-critical edges
    int *critical = (int*)malloc(edgesSize * sizeof(int));
    int *pseudoCritical = (int*)malloc(edgesSize * sizeof(int));
    int criticalCount = 0;
    int pseudoCriticalCount = 0;
    
    // Check each edge
    for (int i = 0; i < edgesSize; i++) {
        // Check if edge is critical: MST weight increases when edge is excluded
        int weightWithoutEdge = computeMST(n, sortedEdges, edgesSize, i, -1);
        if (weightWithoutEdge > originalMSTWeight || weightWithoutEdge == -1) {
            critical[criticalCount++] = sortedEdges[i].index;
        } else {
            // Check if edge is pseudo-critical: can be part of some MST
            int weightWithEdge = computeMST(n, sortedEdges, edgesSize, -1, i);
            if (weightWithEdge == originalMSTWeight) {
                pseudoCritical[pseudoCriticalCount++] = sortedEdges[i].index;
            }
        }
    }
    
    // Prepare result
    int **result = (int**)malloc(2 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(2 * sizeof(int));
    
    result[0] = (int*)malloc(criticalCount * sizeof(int));
    result[1] = (int*)malloc(pseudoCriticalCount * sizeof(int));
    
    for (int i = 0; i < criticalCount; i++) {
        result[0][i] = critical[i];
    }
    for (int i = 0; i < pseudoCriticalCount; i++) {
        result[1][i] = pseudoCritical[i];
    }
    
    (*returnColumnSizes)[0] = criticalCount;
    (*returnColumnSizes)[1] = pseudoCriticalCount;
    *returnSize = 2;
    
    // Cleanup
    free(sortedEdges);
    free(critical);
    free(pseudoCritical);
    
    return result;
}
