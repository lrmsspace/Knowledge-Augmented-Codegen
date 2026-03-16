// Source: https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/   |   Difficulty: Hard
//
// Problem Description:
// An undirected graph of n nodes is defined by edgeList, where edgeList[i] = [ui, vi, disi] denotes an edge between nodes ui and vi with distance disi. Note that there may be multiple edges between two nodes.
//
// Given an array queries, where queries[j] = [pj, qj, limitj], your task is to determine for each queries[j] whether there is a path between pj and qj such that each edge on the path has a distance strictly less than limitj .
//
// Return a boolean array answer, where answer.length == queries.length and the jth value of answer is true if there is a path for queries[j] is true, and false otherwise.
//
// Example:
// Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
// Output: [false,true]
// Explanation: The above figure shows the given graph. Note that there are two overlapping edges between 0 and 1 with distances 2 and 16.
// For the first query, between 0 and 1 there is no path where each distance is less than 2, thus we return false for this query.
// For the second query, there is a path (0 -> 1 -> 2) of two edges with distances less than 5, thus we return true for this query.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= edgeList.length, queries.length <= 105
// 	edgeList[i].length == 3
// 	queries[j].length == 3
// 	0 <= ui, vi, pj, qj <= n - 1
// 	ui != vi
// 	pj != qj
// 	1 <= disi, limitj <= 109
// 	There may be multiple edges between two nodes.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* distanceLimitedPathsExist(int n, int** edgeList, int edgeListSize, int* edgeListColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = queriesSize;
    if (queriesSize == 0) return NULL;

    // Union-Find (Disjoint Set Union) structure
    int *parent = (int*)malloc(n * sizeof(int));
    int *rank = (int*)calloc(n, sizeof(int));
    if (!parent || !rank) {
        free(parent); free(rank);
        return NULL;
    }
    for (int i = 0; i < n; ++i) parent[i] = i;

    // Find with path compression
    int find(int u) {
        if (parent[u] != u) parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

    // Sort edges by distance
    qsort(edgeList, edgeListSize, sizeof(int*), [](const void *a, const void *b) {
        return (*(int**)a)[2] - (*(int**)b)[2];
    });

    // Prepare queries with original indices
    typedef struct {
        int p;
        int q;
        int limit;
        int index;
    } Query;

    Query *queryArr = (Query*)malloc(queriesSize * sizeof(Query));
    if (!queryArr) {
        free(parent); free(rank);
        return NULL;
    }
    for (int i = 0; i < queriesSize; ++i) {
        queryArr[i].p = queries[i][0];
        queryArr[i].q = queries[i][1];
        queryArr[i].limit = queries[i][2];
        queryArr[i].index = i;
    }

    // Sort queries by limit
    qsort(queryArr, queriesSize, sizeof(Query), [](const void *a, const void *b) {
        return ((Query*)a)->limit - ((Query*)b)->limit;
    });     
    bool *result = (bool*)malloc(queriesSize * sizeof(bool));
    if (!result) {
        free(parent); free(rank); free(queryArr);
        return NULL;
    }
    int edgeIndex = 0;
    for (int i = 0; i < queriesSize; ++i) {
        while (edgeIndex < edgeListSize && edgeList[edgeIndex][2] < queryArr[i].limit) {
            unionSets(edgeList[edgeIndex][0], edgeList[edgeIndex][1]);
            edgeIndex++;
        }
        result[queryArr[i].index] = (find(queryArr[i].p) == find(queryArr[i].q));
    }
    free(parent);
    free(rank);
    free(queryArr);
    return result;
}
