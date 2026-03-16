// Source: https://leetcode.com/problems/maximum-star-sum-of-a-graph/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected graph consisting of n nodes numbered from 0 to n - 1. You are given a 0-indexed integer array vals of length n where vals[i] denotes the value of the ith node.
//
// You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// A star graph is a subgraph of the given graph having a center node containing 0 or more neighbors. In other words, it is a subset of edges of the given graph such that there exists a common node for all edges.
//
// The image below shows star graphs with 3 and 4 neighbors respectively, centered at the blue node.
//
// The star sum is the sum of the values of all the nodes present in the star graph.
//
// Given an integer k, return the maximum star sum of a star graph containing at most k edges.
//
// Example:
// Input: vals = [1,2,3,4,10,-10,-20], edges = [[0,1],[1,2],[1,3],[3,4],[3,5],[3,6]], k = 2
// Output: 16
// Explanation: The above diagram represents the input graph.
// The star graph with the maximum star sum is denoted by blue. It is centered at 3 and includes its neighbors 1 and 4.
// It can be shown it is not possible to get a star graph with a sum greater than 16.
//
// Constraints:
// n == vals.length
// 	1 <= n <= 105
// 	-104 <= vals[i] <= 104
// 	0 <= edges.length <= min(n * (n - 1) / 2, 105)
// 	edges[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	0 <= k <= n - 1
//

int maxStarSum(int* vals, int valsSize, int** edges, int edgesSize, int* edgesColSize, int k) {
    // Create an adjacency list to store neighbors for each node
    int** adj = (int**)malloc(valsSize * sizeof(int*));
    int* adjSizes = (int*)calloc(valsSize, sizeof(int));
    for (int i = 0; i < valsSize; i++) {
        adj[i] = (int*)malloc(valsSize * sizeof(int));
    }

    // Populate the adjacency list
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][adjSizes[u]++] = v;
        adj[v][adjSizes[v]++] = u;
    }

    int maxSum = INT_MIN;

    // Calculate the maximum star sum for each node
    for (int i = 0; i < valsSize; i++) {
        int* neighborVals = (int*)malloc(adjSizes[i] * sizeof(int));
        for (int j = 0; j < adjSizes[i]; j++) {
            neighborVals[j] = vals[adj[i][j]];
        }

        // Sort neighbor values in descending order
        qsort(neighborVals, adjSizes[i], sizeof(int), (int (*)(const void*, const void*))[](const int* a, const int* b) {
            return (*b) - (*a);
        });

        int currentSum = vals[i];
        for (int j = 0; j < adjSizes[i] && j < k; j++) {
            if (neighborVals[j] > 0) {
                currentSum += neighborVals[j];
            } else {
                break;
            }
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
        }

        free(neighborVals);
    }

    // Free allocated memory
    for (int i = 0; i < valsSize; i++) {
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);

    return maxSum;      
}
