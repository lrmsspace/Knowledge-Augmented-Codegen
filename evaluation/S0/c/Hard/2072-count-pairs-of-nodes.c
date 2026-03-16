// Source: https://leetcode.com/problems/count-pairs-of-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph defined by an integer n, the number of nodes, and a 2D integer array edges, the edges in the graph, where edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi. You are also given an integer array queries.
//
// Let incident(a, b) be defined as the number of edges that are connected to either node a or b.
//
// The answer to the jth query is the number of pairs of nodes (a, b) that satisfy both of the following conditions:
//
//
// 	a < b
// 	incident(a, b) > queries[j]
//
//
// Return an array answers such that answers.length == queries.length and answers[j] is the answer of the jth query.
//
// Note that there can be multiple edges between the same two nodes.
//
// Example:
// Input: n = 4, edges = [[1,2],[2,4],[1,3],[2,3],[2,1]], queries = [2,3]
// Output: [6,5]
// Explanation: The calculations for incident(a, b) are shown in the table above.
// The answers for each of the queries are as follows:
// - answers[0] = 6. All the pairs have an incident(a, b) value greater than 2.
// - answers[1] = 5. All the pairs except (3, 4) have an incident(a, b) value greater than 3.
//
// Constraints:
// 2 <= n <= 2 * 104
// 	1 <= edges.length <= 105
// 	1 <= ui, vi <= n
// 	ui != vi
// 	1 <= queries.length <= 20
// 	0 <= queries[j] < edges.length
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countPairs(int n, int** edges, int edgesSize, int* edgesColSize, int* queries, int queriesSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = queriesSize;
    int *results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) return NULL;

    int *degree = (int*)calloc(n + 1, sizeof(int));
    if (!degree) { free(results); return NULL; }

    /* count degree of each node */
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        degree[u]++;
        degree[v]++;
    }

    /* sort degrees */
    int *sortedDegree = (int*)malloc(n * sizeof(int));
    if (!sortedDegree) { free(degree); free(results); return NULL; }
    for (int i = 0; i < n; ++i) sortedDegree[i] = degree[i + 1];
    qsort(sortedDegree, n, sizeof(int), cmpInt);

    /* process each query */
    for (int qIdx = 0; qIdx < queriesSize; ++qIdx) {
        int q = queries[qIdx];
        int left = 0, right = n - 1;
        int count = 0;

        while (left < right) {
            if (sortedDegree[left] + sortedDegree[right] > q) {
                count += (right - left);
                right--;
            } else {
                left++;
            }
        }

        results[qIdx] = count;
    }

    free(sortedDegree);
    free(degree);
    return results;     
}
