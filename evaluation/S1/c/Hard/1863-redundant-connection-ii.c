// Source: https://leetcode.com/problems/redundant-connection-ii/   |   Difficulty: Hard
//
// Problem Description:
// In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.
//
// The given input is a directed graph that started as a rooted tree with n nodes (with distinct values from 1 to n), with one additional directed edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed.
//
// The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [ui, vi] that represents a directed edge connecting nodes ui and vi, where ui is a parent of child vi.
//
// Return an edge that can be removed so that the resulting graph is a rooted tree of n nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.
//
// Example:
// Input: edges = [[1,2],[1,3],[2,3]]
// Output: [2,3]
//
// Constraints:
// n == edges.length
// 	3 <= n <= 1000
// 	edges[i].length == 2
// 	1 <= ui, vi <= n
// 	ui != vi
//
// Helpful references (internal KB):
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to efficiently manage a collection of disjoint sets, supporting operations to merge sets and determine if two elements belong to the same set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that maintains a collection of disjoint sets and supports two primary operations: union (merging two sets) and find (determining the representative of an element's set). With path compression and union by rank/size, operations achieve nearly O(1) amortized time complexity.
//   • Invariants: For any element `v`, `parent[v]` is either `v` itself (if `v` is a root) or an ancestor of `v`.; All elements belonging to the same set share a common root representative.
//   • Tips: Apply path compression during `find_set` to optimize future queries.; Utilize union by rank or size to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size results in poor performance.; Failing to correctly identify the root of a set in `find_set`.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
// - Finding a negative cycle in the graph (graph, array, bellman-ford)
//   • When to use: Use when a graph may contain negative edge weights and you need to find the shortest paths from a single source, or specifically to detect and identify negative cycles.
//   • Idea: The Bellman-Ford algorithm computes single-source shortest paths in a weighted graph, even with negative edge weights, and can detect negative cycles. It has a time complexity of O(VE).
//   • Invariants: After k iterations, dist[v] is the shortest path from the source to v using at most k edges.; If no negative cycle is reachable, dist[v] will be the true shortest path distance after V-1 iterations.
//   • Tips: Perform V-1 iterations for shortest path calculation, then one more for cycle detection.; A negative cycle exists if any distance can still be reduced in the V-th iteration.
//   • Pitfalls: Inefficient for graphs with only non-negative weights compared to Dijkstra's.; Does not directly work for undirected graphs with negative edges.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findRedundantDirectedConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    int parent[edgesSize + 1];
    for (int i = 1; i <= edgesSize; i++) {
        parent[i] = i;
    }

    int candidate1[2] = {-1, -1};
    int candidate2[2] = {-1, -1};

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        if (parent[v] != v) {
            candidate1[0] = parent[v];
            candidate1[1] = v;
            candidate2[0] = u;
            candidate2[1] = v;
            edges[i][1] = 0; // Mark this edge to be skipped
        } else {
            parent[v] = u;
        }
    }

    // Reset union-find structure
    for (int i = 1; i <= edgesSize; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        if (v == 0) continue; // Skip the marked edge

        int pu = u;
        while (parent[pu] != pu) {
            pu = parent[pu];
        }
        int pv = v;
        while (parent[pv] != pv) {
            pv = parent[pv];
        }

        if (pu == pv) {
            if (candidate1[0] == -1) {
                *returnSize = 2;
                int* res = (int*)malloc(2 * sizeof(int));
                res[0] = u;
                res[1] = v;
                return res;
            } else {
                *returnSize = 2;
                int* res = (int*)malloc(2 * sizeof(int));
                res[0] = candidate1[0];
                res[1] = candidate1[1];
                return res;
            }
        }
        parent[pv] = pu;
    }

    *returnSize = 2;
    int* res = (int*)malloc(2 * sizeof(int));
    res[0] = candidate2[0];
    res[1] = candidate2[1];
    return res;     
}
