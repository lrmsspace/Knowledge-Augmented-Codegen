// Source: https://leetcode.com/problems/maximize-sum-of-weights-after-edge-removals/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi in the tree.
//
// Your task is to remove zero or more edges such that:
//
//
// 	Each node has an edge with at most k other nodes, where k is given.
// 	The sum of the weights of the remaining edges is maximized.
//
//
// Return the maximum possible sum of weights for the remaining edges after making the necessary removals.
//
// Example:
// Input: edges = [[0,1,4],[0,2,2],[2,3,12],[2,4,6]], k = 2
//
// Output: 22
//
// Explanation:
//
//
//
//
// 	Node 2 has edges with 3 other nodes. We remove the edge [0, 2, 2], ensuring that no node has edges with more than k = 2 nodes.
// 	The sum of weights is 22, and we can't achieve a greater sum. Thus, the answer is 22.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= k <= n - 1
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= edges[i][0] <= n - 1
// 	0 <= edges[i][1] <= n - 1
// 	1 <= edges[i][2] <= 106
// 	The input is generated such that edges form a valid tree.
//

long long maximizeSumOfWeights(int** edges, int edgesSize, int* edgesColSize, int k) {
    int n = edgesSize + 1;
    int *degree = (int*)calloc(n, sizeof(int));
    if (!degree) return 0;
    for (int i = 0; i < edgesSize; ++i) {
        degree[edges[i][0]]++;
        degree[edges[i][1]]++;
    }

    /* build adjacency list */
    int **adj = (int**)malloc(n * sizeof(int*));
    int *adjSizes = (int*)calloc(n, sizeof(int));
    if (!adj || !adjSizes) {
        free(degree); free(adj); free(adjSizes); return 0;
    }
    for (int i = 0; i < n; ++i) {
        adj[i] = (int*)malloc(degree[i] * sizeof(int) * 2); /* each entry: [neighbor, weight] */
        if (!adj[i]) {
            for (int j = 0; j < i; ++j) free(adj[j]);
            free(degree); free(adj); free(adjSizes); return 0;
        }
        degree[i] = 0; /* reuse degree array as current size */
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        adj[u][degree[u] * 2] = v; adj[u][degree[u] * 2 + 1] = w; degree[u]++;
        adj[v][degree[v] * 2] = u; adj[v][degree[v] * 2 + 1] = w; degree[v]++;
    }

    /* calculate result */
    long long result = 0;
    for (int i = 0; i < n; ++i) {
        if (degree[i] <= k) {
            for (int j = 0; j < degree[i]; ++j) {
                result += adj[i][j * 2 + 1];
            }
        } else {
            /* collect weights */
            int *weights = (int*)malloc(degree[i] * sizeof(int));
            if (!weights) {
                for (int j = 0; j < n; ++j) free(adj[j]);
                free(degree); free(adj); free(adjSizes); return 0;
            }
            for (int j = 0; j < degree[i]; ++j) {
                weights[j] = adj[i][j * 2 + 1];
            }
            /* sort weights in descending order */
            qsort(weights, degree[i], sizeof(int), (int (*)(const void*, const void*))[](const int* a, const int* b) {
                return (*b) - (*a);
            });
            for (int j = 0; j < k; ++j) {
                result += weights[j];
            }
            free(weights);
        }
    }
    result /= 2; /* each edge counted twice */
    for (int i = 0; i < n; ++i) free(adj[i]);
    free(degree);
    free(adj);
    free(adjSizes);
    return result;
}
