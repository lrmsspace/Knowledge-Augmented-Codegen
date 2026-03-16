// Source: https://leetcode.com/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi in the tree.
//
// You are also given a 2D integer array queries of length m, where queries[i] = [ai, bi]. For each query, find the minimum number of operations required to make the weight of every edge on the path from ai to bi equal. In one operation, you can choose any edge of the tree and change its weight to any value.
//
// Note that:
//
//
// 	Queries are independent of each other, meaning that the tree returns to its initial state on each new query.
// 	The path from ai to bi is a sequence of distinct nodes starting with node ai and ending with node bi such that every two adjacent nodes in the sequence share an edge in the tree.
//
//
// Return an array answer of length m where answer[i] is the answer to the ith query.
//
// Example:
// Input: n = 7, edges = [[0,1,1],[1,2,1],[2,3,1],[3,4,2],[4,5,2],[5,6,2]], queries = [[0,3],[3,6],[2,6],[0,6]]
// Output: [0,0,1,3]
// Explanation: In the first query, all the edges in the path from 0 to 3 have a weight of 1. Hence, the answer is 0.
// In the second query, all the edges in the path from 3 to 6 have a weight of 2. Hence, the answer is 0.
// In the third query, we change the weight of edge [2,3] to 2. After this operation, all the edges in the path from 2 to 6 have a weight of 2. Hence, the answer is 1.
// In the fourth query, we change the weights of edges [0,1], [1,2] and [2,3] to 2. After these operations, all the edges in the path from 0 to 6 have a weight of 2. Hence, the answer is 3.
// For each queries[i], it can be shown that answer[i] is the minimum number of operations needed to equalize all the edge weights in the path from ai to bi.
//
// Constraints:
// 1 <= n <= 104
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ui, vi < n
// 	1 <= wi <= 26
// 	The input is generated such that edges represents a valid tree.
// 	1 <= queries.length == m <= 2 * 104
// 	queries[i].length == 2
// 	0 <= ai, bi < n
//
// Helpful references (internal KB):
// - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
//   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
//   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
//   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
//   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
//   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
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
int* minOperationsQueries(int n, int** edges, int edgesSize, int* edgesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
  
    /* Build adjacency list */
    int adj[10000][26][2]; // node, weight, neighbor
    int adjSize[10000];
    memset(adjSize, 0, sizeof(adjSize));
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2] - 1;
        adj[u][adjSize[u]][0] = w;
        adj[u][adjSize[u]][1] = v;
        adjSize[u]++;
        adj[v][adjSize[v]][0] = w;
        adj[v][adjSize[v]][1] = u;
        adjSize[v]++;
    }

    /* Preprocess LCA using Binary Lifting */
    int LOG = 0;
    while ((1 << LOG) <= n) LOG++;
    int** up = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        up[i] = (int*)malloc(LOG * sizeof(int));
        for (int j = 0; j < LOG; ++j)
            up[i][j] = -1;
    }
    int depth[10000];
    memset(depth, 0, sizeof(depth));

    void dfs(int u, int parent) {
        up[u][0] = parent;
        for (int j = 1; j < LOG; ++j) {
            if (up[u][j - 1] != -1)
                up[u][j] = up[up[u][j - 1]][j - 1];
        }
        for (int i = 0; i < adjSize[u]; ++i) {
            int v = adj[u][i][1];
            if (v != parent) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
        }
    }
    dfs(0, -1);

    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            int temp = u; u = v; v = temp;
        }
        for (int j = LOG - 1; j >= 0; --j) {
            if (up[u][j] != -1 && depth[up[u][j]] >= depth[v])
                u = up[u][j];
        }
        if (u == v) return u;
        for (int j = LOG - 1; j >= 0; --j) {
            if (up[u][j] != -1 && up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }
    int* result = (int*)malloc(queriesSize * sizeof(int));              
    for (int q = 0; q < queriesSize; ++q) {
        int u = queries[q][0], v = queries[q][1];
        int ancestor = lca(u, v);
        int count[26];
        memset(count, 0, sizeof(count));
        int maxFreq = 0;

        void countPath(int x) {
            while (x != ancestor) {
                int p = up[x][0];
                for (int i = 0; i < adjSize[x]; ++i) {
                    if (adj[x][i][1] == p) {
                        int w = adj[x][i][0];
                        count[w]++;
                        if (count[w] > maxFreq)
                            maxFreq = count[w];
                        break;
                    }
                }
                x = p;
            }
        }
        countPath(u);
        countPath(v);

        int totalEdges = depth[u] + depth[v] - 2 * depth[ancestor];
        result[q] = totalEdges - maxFreq;
    }
    for (int i = 0; i < n; ++i) {
        free(up[i]);
    }
    free(up);
    *returnSize = queriesSize;
    return result;
}