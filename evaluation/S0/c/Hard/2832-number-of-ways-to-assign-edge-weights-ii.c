// Source: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.
//
// Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
//
// The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.
//
// You are given a 2D integer array queries. For each queries[i] = [ui, vi], determine the number of ways to assign weights to edges in the path such that the cost of the path between ui and vi is odd.
//
// Return an array answer, where answer[i] is the number of valid assignments for queries[i].
//
// Since the answer may be large, apply modulo 109 + 7 to each answer[i].
//
// Note: For each query, disregard all edges not in the path between node ui and vi.
//
// Example:
// Input: edges = [[1,2]], queries = [[1,1],[1,2]]
//
// Output: [0,1]
//
// Explanation:
//
//
// 	Query [1,1]: The path from Node 1 to itself consists of no edges, so the cost is 0. Thus, the number of valid assignments is 0.
// 	Query [1,2]: The path from Node 1 to Node 2 consists of one edge (1 → 2). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi]
// 	1 <= queries.length <= 105
// 	queries[i] == [ui, vi]
// 	1 <= ui, vi <= n
// 	edges represents a valid tree.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    const int MOD = 1000000007;

    int n = edgesSize + 1;
    int *adj[n + 1];
    int adjSizes[n + 1];
    memset(adjSizes, 0, sizeof(adjSizes));
    for (int i = 0; i <= n; ++i) {
        adj[i] = (int*)malloc(n * sizeof(int)); /* worst case */
        if (!adj[i]) {
            for (int j = 0; j < i; ++j) free(adj[j]);
            return NULL;
        }
    }

    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][adjSizes[u]++] = v;
        adj[v][adjSizes[v]++] = u;
    }

    int depth[n + 1];
    memset(depth, -1, sizeof(depth));
    depth[1] = 0;
    int stack[n];
    int top = 0;
    stack[top++] = 1;

    while (top > 0) {
        int node = stack[--top];
        for (int i = 0; i < adjSizes[node]; ++i) {
            int neighbor = adj[node][i];
            if (depth[neighbor] == -1) {
                depth[neighbor] = depth[node] + 1;
                stack[top++] = neighbor;
            }
        }
    }

    int *results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) {
        for (int i = 0; i <= n; ++i) free(adj[i]);
        return NULL;
    }

    for (int i = 0; i < queriesSize; ++i) {
        int u = queries[i][0];
        int v = queries[i][1];
        int dist = depth[u] + depth[v];
        results[i] = (dist % 2 == 1) ? 1 : 0;
    }

    for (int i = 0; i <= n; ++i) free(adj[i]);

    *returnSize = queriesSize;
    return results;     
}
