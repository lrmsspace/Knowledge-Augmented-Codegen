// Source: https://leetcode.com/problems/sum-of-distances-in-tree/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
//
// You are given the integer n and the array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Return an array answer of length n where answer[i] is the sum of the distances between the ith node in the tree and all other nodes.
//
// Example:
// Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
// Output: [8,12,6,10,10,10]
// Explanation: The tree is shown above.
// We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
// equals 1 + 1 + 2 + 2 + 2 = 8.
// Hence, answer[0] = 8, and so on.
//
// Constraints:
// 1 <= n <= 3 * 104
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	The given input represents a valid tree.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumOfDistancesInTree(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = n;
    if (n <= 0) return NULL;

    /* Build adjacency list */
    int *adjSizes = (int*)calloc(n, sizeof(int));
    if (!adjSizes) return NULL;
    for (int i = 0; i < edgesSize; ++i) {
        adjSizes[edges[i][0]]++;
        adjSizes[edges[i][1]]++;
    }
    int **adj = (int**)malloc(n * sizeof(int*));
    if (!adj) { free(adjSizes); return NULL; }
    for (int i = 0; i < n; ++i) {
        adj[i] = (int*)malloc(adjSizes[i] * sizeof(int));
        if (!adj[i]) {
            for (int j = 0; j < i; ++j) free(adj[j]);
            free(adj); free(adjSizes); return NULL;
        }
        adjSizes[i] = 0; /* reuse to track current size */
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adj[u][adjSizes[u]++] = v;
        adj[v][adjSizes[v]++] = u;
    }

    int *res = (int*)calloc(n, sizeof(int));
    int *subtreeSize = (int*)calloc(n, sizeof(int));
    if (!res || !subtreeSize) {
        for (int i = 0; i < n; ++i) free(adj[i]);
        free(adj); free(adjSizes); free(res); free(subtreeSize);
        return NULL;
    }

    /* Post-order DFS to compute subtree sizes and initial distances */
    void dfs1(int node, int parent) {
        subtreeSize[node] = 1;
        for (int i = 0; i < adjSizes[node]; ++i) {
            int neighbor = adj[node][i];
            if (neighbor == parent) continue;
            dfs1(neighbor, node);
            subtreeSize[node] += subtreeSize[neighbor];
            res[0] += subtreeSize[neighbor];
        }
    }

    /* Pre-order DFS to compute distances for all nodes */
    void dfs2(int node, int parent) {
        for (int i = 0; i < adjSizes[node]; ++i) {
            int neighbor = adj[node][i];
            if (neighbor == parent) continue;
            res[neighbor] = res[node] - subtreeSize[neighbor] + (n - subtreeSize[neighbor]);
            dfs2(neighbor, node);
        }
    }
    dfs1(0, -1);
    dfs2(0, -1);                                                    
    /* Cleanup */
    for (int i = 0; i < n; ++i) free(adj[i]);
    free(adj); free(adjSizes); free(subtreeSize);
    return res;
}
