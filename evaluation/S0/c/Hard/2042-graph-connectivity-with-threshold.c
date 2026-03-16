// Source: https://leetcode.com/problems/graph-connectivity-with-threshold/   |   Difficulty: Hard
//
// Problem Description:
// We have n cities labeled from 1 to n. Two different cities with labels x and y are directly connected by a bidirectional road if and only if x and y share a common divisor strictly greater than some threshold. More formally, cities with labels x and y have a road between them if there exists an integer z such that all of the following are true:
//
//
// 	x % z == 0,
// 	y % z == 0, and
// 	z > threshold.
//
//
// Given the two integers, n and threshold, and an array of queries, you must determine for each queries[i] = [ai, bi] if cities ai and bi are connected directly or indirectly. (i.e. there is some path between them).
//
// Return an array answer, where answer.length == queries.length and answer[i] is true if for the ith query, there is a path between ai and bi, or answer[i] is false if there is no path.
//
// Example:
// Input: n = 6, threshold = 2, queries = [[1,4],[2,5],[3,6]]
// Output: [false,false,true]
// Explanation: The divisors for each number:
// 1:   1
// 2:   1, 2
// 3:   1, 3
// 4:   1, 2, 4
// 5:   1, 5
// 6:   1, 2, 3, 6
// Using the underlined divisors above the threshold, only cities 3 and 6 share a common divisor, so they are the
// only ones directly connected. The result of each query:
// [1,4]   1 is not connected to 4
// [2,5]   2 is not connected to 5
// [3,6]   3 is connected to 6 through path 3--6
//
// Constraints:
// 2 <= n <= 104
// 	0 <= threshold <= n
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	1 <= ai, bi <= cities
// 	ai != bi
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* areConnected(int n, int threshold, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = queriesSize;
    bool *results = (bool*)malloc(queriesSize * sizeof(bool));
    if (!results) return NULL;

    /* Union-Find (Disjoint Set Union - DSU) structure */
    int *parent = (int*)malloc((n + 1) * sizeof(int));
    int *rank = (int*)calloc((n + 1), sizeof(int));
    if (!parent || !rank) {
        free(results); free(parent); free(rank);
        return NULL;
    }
    for (int i = 1; i <= n; ++i) parent[i] = i;

    /* Find with path compression */
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    /* Union by rank */
    void union_sets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    /* Connect cities based on common divisors greater than threshold */
    for (int div = threshold + 1; div <= n / 2; ++div) {
        for (int multiple = div * 2; multiple <= n; multiple += div) {
            union_sets(div, multiple);
        }
    }

    /* Process queries */
    for (int i = 0; i < queriesSize; ++i) {
        int a = queries[i][0];
        int b = queries[i][1];
        results[i] = (find(a) == find(b));
    }

    free(parent);
    free(rank);
    return results;     
}
