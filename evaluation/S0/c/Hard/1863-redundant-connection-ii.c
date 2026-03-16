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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findRedundantDirectedConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    if (!edges || edgesSize <= 0 || !returnSize) return NULL;

    int parent[1001] = {0};
    int candA[2] = {0}, candB[2] = {0};

    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        if (parent[v] == 0) {
            parent[v] = u;
        } else {
            candA[0] = parent[v]; candA[1] = v;
            candB[0] = u; candB[1] = v;
            edges[i][1] = 0; // invalidate this edge
        }
    }

    // Union-Find to detect cycle
    int uf[1001];
    for (int i = 1; i <= edgesSize; ++i) uf[i] = i;

    int find(int x) {
        if (uf[x] != x) uf[x] = find(uf[x]);
        return uf[x];
    }

    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        if (v == 0) continue; // skip invalidated edge
        int pu = find(u), pv = find(v);
        if (pu == pv) {
            if (candA[0] == 0) {
                *returnSize = 2;
                int *res = (int*)malloc(2 * sizeof(int));
                res[0] = u; res[1] = v;
                return res;
            } else {
                *returnSize = 2;
                int *res = (int*)malloc(2 * sizeof(int));
                res[0] = candA[0]; res[1] = candA[1];
                return res;
            }
        }
        uf[pv] = pu;
    }

    *returnSize = 2;
    int *res = (int*)malloc(2 * sizeof(int));
    res[0] = candB[0]; res[1] = candB[1];
    return res;     
}
