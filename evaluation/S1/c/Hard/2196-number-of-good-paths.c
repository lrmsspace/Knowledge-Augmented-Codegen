// Source: https://leetcode.com/problems/number-of-good-paths/   |   Difficulty: Hard
//
// Problem Description:
// There is a tree (i.e. a connected, undirected graph with no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges.
//
// You are given a 0-indexed integer array vals of length n where vals[i] denotes the value of the ith node. You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// A good path is a simple path that satisfies the following conditions:
//
//
// 	The starting node and the ending node have the same value.
// 	All nodes between the starting node and the ending node have values less than or equal to the starting node (i.e. the starting node's value should be the maximum value along the path).
//
//
// Return the number of distinct good paths.
//
// Note that a path and its reverse are counted as the same path. For example, 0 -> 1 is considered to be the same as 1 -> 0. A single node is also considered as a valid path.
//
// Example:
// Input: vals = [1,3,2,1,3], edges = [[0,1],[0,2],[2,3],[2,4]]
// Output: 6
// Explanation: There are 5 good paths consisting of a single node.
// There is 1 additional good path: 1 -> 0 -> 2 -> 4.
// (The reverse path 4 -> 2 -> 0 -> 1 is treated as the same as 1 -> 0 -> 2 -> 4.)
// Note that 0 -> 2 -> 3 is not a good path because vals[2] > vals[0].
//
// Constraints:
// n == vals.length
// 	1 <= n <= 3 * 104
// 	0 <= vals[i] <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	edges represents a valid tree.
//
// Helpful references (internal KB):
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
//   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
//   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
//   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
// - Minimum spanning tree - Kruskal with Disjoint Set Union (graph, ds, mst-kruskal, union-find)
//   • When to use: Use when you need to find a minimum spanning tree in a graph, especially when the graph is sparse or the number of edges is not excessively large compared to vertices.
//   • Idea: Sorts all graph edges by weight and iteratively adds the cheapest edge that connects two previously disconnected components using a Disjoint Set Union (DSU) data structure. This process builds an MST with O(M log M) or O(M log N) time complexity.
//   • Invariants: After processing k edges, the chosen edges form a forest where each tree is a component of the MST.; Any edge not yet processed has a weight greater than or equal to all processed edges.
//   • Tips: Sort edges by weight in non-decreasing order.; Initialize DSU such that each vertex is in its own set.
//   • Pitfalls: Forgetting to sort edges, leading to an incorrect MST.; Inefficient DSU implementation without path compression or union by rank/size.
// - Finding Bridges Online (graph, ds, union-find, counting)
//   • When to use: Use when edges are added one by one to an initially empty graph and you need to efficiently track the number of bridges or 2-edge-connected components after each addition.
//   • Idea: This algorithm dynamically maintains the number of bridges in an undirected graph as edges are added incrementally. It leverages a Disjoint Set Union (DSU) data structure to achieve an amortized time complexity of O((N+M) log N).
//   • Invariants: Each DSU set represents a 2-edge-connected component or a collection of such components connected by bridges.; The total count of bridges accurately reflects edges whose removal increases connected components.
//   • Tips: Understand the properties of 2-edge-connected components and how they relate to bridges.; Carefully manage DSU operations, including path compression and union by rank/size, for optimal performance.
//   • Pitfalls: Incorrectly updating the bridge count after an edge addition, especially when cycles are formed.; Inefficient DSU operations leading to a higher than expected time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numberOfGoodPaths(int* vals, int valsSize, int** edges, int edgesSize, int* edgesColSize) {
    #define MAX_NODES 30000
    #define MAX_VAL 100000

    typedef struct {
        int parent;
        int rank;
        int count;
    } DSUNode;

    DSUNode dsu[MAX_NODES];

    void dsu_init(int n) {
        for (int i = 0; i < n; i++) {
            dsu[i].parent = i;
            dsu[i].rank = 0;
            dsu[i].count = 1;
        }
    }

    int dsu_find(int v) {
        if (dsu[v].parent != v) {
            dsu[v].parent = dsu_find(dsu[v].parent);
        }
        return dsu[v].parent;
    }

    void dsu_union(int a, int b) {
        a = dsu_find(a);
        b = dsu_find(b);
        if (a != b) {
            if (dsu[a].rank < dsu[b].rank) {
                dsu[a].parent = b;
                dsu[b].count += dsu[a].count;
            } else if (dsu[a].rank > dsu[b].rank) {
                dsu[b].parent = a;
                dsu[a].count += dsu[b].count;
            } else {
                dsu[b].parent = a;
                dsu[a].count += dsu[b].count;
                dsu[a].rank++;
            }
        }
    }

    typedef struct {
        int u;
        int v;
    } Edge;

    Edge edgeList[MAX_NODES - 1];
    for (int i = 0; i < edgesSize; i++) {
        edgeList[i].u = edges[i][0];
        edgeList[i].v = edges[i][1];
    }

    // Group edges by max node value
    typedef struct {
        int index;
        int value;
    } NodeValue;

    NodeValue nodes[MAX_NODES];
    for (int i = 0; i < valsSize; i++) {
        nodes[i].index = i;
        nodes[i].value = vals[i];
    }

    // Sort nodes by value
    int compare(const void* a, const void* b) {
        return ((NodeValue*)a)->value - ((NodeValue*)b)->value;
    }
    qsort(nodes, valsSize, sizeof(NodeValue), compare);
    // Sort edges by max node value
    int edgeMaxVal[MAX_NODES - 1];
    for (int i = 0; i < edgesSize; i++) {
        int u = edgeList[i].u;
        int v = edgeList[i].v;
        edgeMaxVal[i] = vals[u] > vals[v] ? vals[u] : vals[v];
    }
    int compareEdges(const void* a, const void* b) {
        int idxA = *(int*)a;
        int idxB = *(int*)b;
        return edgeMaxVal[idxA] - edgeMaxVal[idxB];
    }
    int edgeIndices[MAX_NODES - 1];
    for (int i = 0; i < edgesSize; i++) {
        edgeIndices[i] = i;
    }
    qsort(edgeIndices, edgesSize, sizeof(int), compareEdges);
    dsu_init(valsSize);
    int edgePtr = 0;
    long long goodPaths = valsSize; // Each node is a good path
    for (int i = 0; i < valsSize;) {
        int currentVal = nodes[i].value;
        // Process all edges with max node value <= currentVal
        while (edgePtr < edgesSize && edgeMaxVal[edgeIndices[edgePtr]] <= currentVal) {
            int u = edgeList[edgeIndices[edgePtr]].u;
            int v = edgeList[edgeIndices[edgePtr]].v;
            dsu_union(u, v);
            edgePtr++;
        }
        // Count good paths for nodes with currentVal
        int start = i;
        while (i < valsSize && nodes[i].value == currentVal) {
            int root = dsu_find(nodes[i].index);
            dsu[root].count++;
            i++;
        }
        for (int j = start; j < i; j++) {
            int root = dsu_find(nodes[j].index);
            if (dsu[root].count > 1) {
                goodPaths += dsu[root].count - 1;
                dsu[root].count = 1; // Reset count after counting
            }
        }
    }
    return (int)goodPaths;
}
