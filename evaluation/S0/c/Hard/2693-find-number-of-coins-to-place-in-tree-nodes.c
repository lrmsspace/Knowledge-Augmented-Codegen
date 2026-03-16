// Source: https://leetcode.com/problems/find-number-of-coins-to-place-in-tree-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// You are also given a 0-indexed integer array cost of length n, where cost[i] is the cost assigned to the ith node.
//
// You need to place some coins on every node of the tree. The number of coins to be placed at node i can be calculated as:
//
//
// 	If size of the subtree of node i is less than 3, place 1 coin.
// 	Otherwise, place an amount of coins equal to the maximum product of cost values assigned to 3 distinct nodes in the subtree of node i. If this product is negative, place 0 coins.
//
//
// Return an array coin of size n such that coin[i] is the number of coins placed at node i.
//
// Example:
// Input: edges = [[0,1],[0,2],[0,3],[0,4],[0,5]], cost = [1,2,3,4,5,6]
// Output: [120,1,1,1,1,1]
// Explanation: For node 0 place 6 * 5 * 4 = 120 coins. All other nodes are leaves with subtree of size 1, place 1 coin on each of them.
//
// Constraints:
// 2 <= n <= 2 * 104
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	cost.length == n
// 	1 <= |cost[i]| <= 104
// 	The input is generated such that edges represents a valid tree.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* placedCoins(int** edges, int edgesSize, int* edgesColSize, int* cost, int costSize, int* returnSize) {
    if (!returnSize || costSize <= 0) return NULL;
    *returnSize = costSize;
    long long *result = (long long*)malloc(costSize * sizeof(long long));
    if (!result) return NULL;

    /* Build adjacency list */
    int **adj = (int**)malloc(costSize * sizeof(int*));
    int *adjSizes = (int*)calloc(costSize, sizeof(int));
    for (int i = 0; i < costSize; ++i) adj[i] = NULL;
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adj[u] = (int*)realloc(adj[u], (adjSizes[u] + 1) * sizeof(int));
        adj[u][adjSizes[u]++] = v;
        adj[v] = (int*)realloc(adj[v], (adjSizes[v] + 1) * sizeof(int));
        adj[v][adjSizes[v]++] = u;
    }

    /* DFS to compute subtree sizes and coin placements */
    int *subtreeSizes = (int*)calloc(costSize, sizeof(int));
    int *visited = (int*)calloc(costSize, sizeof(int));

    long long dfs(int node) {
        visited[node] = 1;
        subtreeSizes[node] = 1;
        long long max1 = LLONG_MIN, max2 = LLONG_MIN, max3 = LLONG_MIN;

        for (int i = 0; i < adjSizes[node]; ++i) {
            int neighbor = adj[node][i];
            if (!visited[neighbor]) {
                long long childMax = dfs(neighbor);
                subtreeSizes[node] += subtreeSizes[neighbor];

                if (childMax > max1) {
                    max3 = max2;
                    max2 = max1;
                    max1 = childMax;
                } else if (childMax > max2) {
                    max3 = max2;
                    max2 = childMax;
                } else if (childMax > max3) {
                    max3 = childMax;
                }
            }
        }

        if (subtreeSizes[node] < 3) {
            result[node] = 1;
        } else {
            long long product = max1 * max2 * max3;
            result[node] = product > 0 ? product : 0;
        }

        return cost[node] > 0 ? cost[node] : 0;
    }
    dfs(0);
    /* Free memory */
    for (int i = 0; i < costSize; ++i) free(adj[i]);
    free(adj);
    free(adjSizes);
    free(subtreeSizes);
    free(visited);
    return result;
}
