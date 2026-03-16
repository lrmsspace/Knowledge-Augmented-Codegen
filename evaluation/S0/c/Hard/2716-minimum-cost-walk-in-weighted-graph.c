// Source: https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected weighted graph with n vertices labeled from 0 to n - 1.
//
// You are given the integer n and an array edges, where edges[i] = [ui, vi, wi] indicates that there is an edge between vertices ui and vi with a weight of wi.
//
// A walk on a graph is a sequence of vertices and edges. The walk starts and ends with a vertex, and each edge connects the vertex that comes before it and the vertex that comes after it. It's important to note that a walk may visit the same edge or vertex more than once.
//
// The cost of a walk starting at node u and ending at node v is defined as the bitwise AND of the weights of the edges traversed during the walk. In other words, if the sequence of edge weights encountered during the walk is w0, w1, w2, ..., wk, then the cost is calculated as w0 & w1 & w2 & ... & wk, where & denotes the bitwise AND operator.
//
// You are also given a 2D array query, where query[i] = [si, ti]. For each query, you need to find the minimum cost of the walk starting at vertex si and ending at vertex ti. If there exists no such walk, the answer is -1.
//
// Return the array answer, where answer[i] denotes the minimum cost of a walk for query i.
//
// Example:
// Input: n = 5, edges = [[0,1,7],[1,3,7],[1,2,1]], query = [[0,3],[3,4]]
//
// Output: [1,-1]
//
// Explanation:
//
// To achieve the cost of 1 in the first query, we need to move on the following edges: 0->1 (weight 7), 1->2 (weight 1), 2->1 (weight 1), 1->3 (weight 7).
//
// In the second query, there is no walk between nodes 3 and 4, so the answer is -1.
//
// Constraints:
// 2 <= n <= 105
// 	0 <= edges.length <= 105
// 	edges[i].length == 3
// 	0 <= ui, vi <= n - 1
// 	ui != vi
// 	0 <= wi <= 105
// 	1 <= query.length <= 105
// 	query[i].length == 2
// 	0 <= si, ti <= n - 1
// 	si != ti
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minimumCost(int n, int** edges, int edgesSize, int* edgesColSize, int** query, int querySize, int* queryColSize, int* returnSize) {
   
    if (!returnSize) return NULL;
    *returnSize = querySize;
    int *res = (int*)malloc(querySize * sizeof(int));
    if (!res) return NULL;

    typedef struct {
        int parent;
        int rank;
    } DSU;

    DSU* dsuArray = (DSU*)malloc(n * sizeof(DSU));
    for (int i = 0; i < n; i++) {
        dsuArray[i].parent = i;
        dsuArray[i].rank = 0;
    }

    int find(DSU* dsuArray, int x) {
        if (dsuArray[x].parent != x) {
            dsuArray[x].parent = find(dsuArray, dsuArray[x].parent);
        }
        return dsuArray[x].parent;
    }

    void unionSets(DSU* dsuArray, int x, int y) {
        int rootX = find(dsuArray, x);
        int rootY = find(dsuArray, y);
        if (rootX != rootY) {
            if (dsuArray[rootX].rank < dsuArray[rootY].rank) {
                dsuArray[rootX].parent = rootY;
            } else if (dsuArray[rootX].rank > dsuArray[rootY].rank) {
                dsuArray[rootY].parent = rootX;
            } else {
                dsuArray[rootY].parent = rootX;
                dsuArray[rootX].rank++;
            }
        }
    }

    for (int q = 0; q < querySize; q++) {
        res[q] = -1;
        for (int bit = 0; bit <= 20; bit++) {
            for (int i = 0; i < n; i++) {
                dsuArray[i].parent = i;
                dsuArray[i].rank = 0;
            }
            for (int i = 0; i < edgesSize; i++) {
                if ((edges[i][2] & ((1 << (bit + 1)) - 1)) == 0) {
                    unionSets(dsuArray, edges[i][0], edges[i][1]);
                }
            }
            if (find(dsuArray, query[q][0]) == find(dsuArray, query[q][1])) {
                res[q] = 0;
                for (int b = 0; b <= bit; b++) {                        
                    int canConnect = 0;
                    for (int i = 0; i < edgesSize; i++) {
                        if ((edges[i][2] & (1 << b)) && (edges[i][2] & ((1 << (bit + 1)) - 1)) == edges[i][2]) {
                            unionSets(dsuArray, edges[i][0], edges[i][1]);
                        }
                    }
                    if (find(dsuArray, query[q][0]) == find(dsuArray, query[q][1])) {
                        res[q] |= (1 << b);
                    } else {
                        for (int i = 0; i < n; i++) {
                            dsuArray[i].parent = i;
                            dsuArray[i].rank = 0;
                        }
                        for (int i = 0; i < edgesSize; i++) {
                            if ((edges[i][2] & ((1 << (bit + 1)) - 1)) == edges[i][2]) {
                                unionSets(dsuArray, edges[i][0], edges[i][1]);
                            }
                        }
                    }
                }
                break;
            }
        }
    }
    free(dsuArray);
    return res;
}
