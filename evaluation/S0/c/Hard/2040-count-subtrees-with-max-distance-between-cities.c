// Source: https://leetcode.com/problems/count-subtrees-with-max-distance-between-cities/   |   Difficulty: Hard
//
// Problem Description:
// There are n cities numbered from 1 to n. You are given an array edges of size n-1, where edges[i] = [ui, vi] represents a bidirectional edge between cities ui and vi. There exists a unique path between each pair of cities. In other words, the cities form a tree.
//
// A subtree is a subset of cities where every city is reachable from every other city in the subset, where the path between each pair passes through only the cities from the subset. Two subtrees are different if there is a city in one subtree that is not present in the other.
//
// For each d from 1 to n-1, find the number of subtrees in which the maximum distance between any two cities in the subtree is equal to d.
//
// Return an array of size n-1 where the dth element (1-indexed) is the number of subtrees in which the maximum distance between any two cities is equal to d.
//
// Notice that the distance between the two cities is the number of edges in the path between them.
//
// Example:
// Input: n = 4, edges = [[1,2],[2,3],[2,4]]
// Output: [3,4,0]
// Explanation:
// The subtrees with subsets {1,2}, {2,3} and {2,4} have a max distance of 1.
// The subtrees with subsets {1,2,3}, {1,2,4}, {2,3,4} and {1,2,3,4} have a max distance of 2.
// No subtree has two nodes where the max distance between them is 3.
//
// Constraints:
// 2 <= n <= 15
// 	edges.length == n-1
// 	edges[i].length == 2
// 	1 <= ui, vi <= n
// 	All pairs (ui, vi) are distinct.
//



/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countSubgraphsForEachDiameter(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize){
    int **dist = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        dist[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) {
            dist[i][j] = (i == j) ? 0 : 100;
        }
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0] - 1;
        int v = edges[i][1] - 1;
        dist[u][v] = 1;
        dist[v][u] = 1;
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int maxD = n - 1;
    int *result = (int*)calloc(maxD, sizeof(int));
    for (int mask = 1; mask < (1 << n); ++mask) {
        int diameter = 0;
        int valid = 1;
        for (int i = 0; i < n && valid; ++i) {
            if (!(mask & (1 << i))) continue;
            for (int j = i + 1; j < n && valid; ++j) {
                if (!(mask & (1 << j))) continue;
                if (dist[i][j] == 100) {
                    valid = 0;
                    break;
                }
                if (dist[i][j] > diameter) {
                    diameter = dist[i][j];
                }
            }
        }
        if (valid && diameter > 0) {
            result[diameter - 1]++;
        }
    }

    for (int i = 0; i < n; ++i) {
        free(dist[i]);
    }
    free(dist);

    *returnSize = maxD;
    return result;
}
