// Source: https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/   |   Difficulty: Hard
//
// Problem Description:
// Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional and weighted edge between nodes ai and bi. A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.
//
// Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST). An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge. On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.
//
// Note that you can return the indices of the edges in any order.
//
// Example:
// Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
// Output: [[0,1],[2,3,4,5]]
// Explanation: The figure above describes the graph.
// The following figure shows all the possible MSTs:
//
// Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first list of the output.
// The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical edges. We add them to the second list of the output.
//
// Constraints:
// 2 <= n <= 100
// 	1 <= edges.length <= min(200, n * (n - 1) / 2)
// 	edges[i].length == 3
// 	0 <= ai < bi < n
// 	1 <= weighti <= 1000
// 	All pairs (ai, bi) are distinct.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findCriticalAndPseudoCriticalEdges(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize, int** returnColumnSizes) {
  
    // Implementation of finding critical and pseudo-critical edges in MST using Kruskal's algorithm
    
    // Define Union-Find structure
    typedef struct {
        int parent;
        int rank;
    } UnionFind;

    UnionFind* ufCreate(int size) {
        UnionFind* uf = (UnionFind*)malloc(size * sizeof(UnionFind));
        for (int i = 0; i < size; i++) {
            uf[i].parent = i;
            uf[i].rank = 0;
        }
        return uf;
    }

    int ufFind(UnionFind* uf, int x) {
        if (uf[x].parent != x) {
            uf[x].parent = ufFind(uf, uf[x].parent);
        }
        return uf[x].parent;
    }

    void ufUnion(UnionFind* uf, int x, int y) {
        int rootX = ufFind(uf, x);
        int rootY = ufFind(uf, y);
        if (rootX != rootY) {
            if (uf[rootX].rank < uf[rootY].rank) {
                uf[rootX].parent = rootY;
            } else if (uf[rootX].rank > uf[rootY].rank) {
                uf[rootY].parent = rootX;
            } else {
                uf[rootY].parent = rootX;
                uf[rootX].rank++;
            }
        }
    }

    // Sort edges by weight
    typedef struct {
        int u;
        int v;
        int weight;
        int index;
    } Edge;

    Edge* edgeList = (Edge*)malloc(edgesSize * sizeof(Edge));
    for (int i = 0; i < edgesSize; i++) {
        edgeList[i].u = edges[i][0];
        edgeList[i].v = edges[i][1];
        edgeList[i].weight = edges[i][2];
        edgeList[i].index = i;
    }

    int compareEdges(const void* a, const void* b) {
        return ((Edge*)a)->weight - ((Edge*)b)->weight;
    }

    qsort(edgeList, edgesSize, sizeof(Edge), compareEdges);

    // Function to calculate MST weight with optional inclusion/exclusion of an edge
    int calculateMST(int n, Edge* edges, int edgesSize, int excludeIndex, int includeIndex) {
        UnionFind* uf = ufCreate(n);
        int totalWeight = 0;
        int edgesUsed = 0;

        // Include the specified edge first
        if (includeIndex != -1) {
            ufUnion(uf, edges[includeIndex].u, edges[includeIndex].v);
            totalWeight += edges[includeIndex].weight;
            edgesUsed++;
        }

        for (int i = 0; i < edgesSize; i++) {
            if (i == excludeIndex) continue;
            int u = edges[i].u;
            int v = edges[i].v;
            if (ufFind(uf, u) != ufFind(uf, v)) {
                ufUnion(uf, u, v);
                totalWeight += edges[i].weight;
                edgesUsed++;
            }
        }

        free(uf);
        return (edgesUsed == n - 1) ? totalWeight : 0x7FFFFFFF; // Return max int if MST not possible
    }
    int originalMSTWeight = calculateMST(n, edgeList, edgesSize, -1, -1);
    int** result = (int**)malloc(2 * sizeof(int*));
    result[0] = (int*)malloc(edgesSize * sizeof(int)); // Critical edges
    result[1] = (int*)malloc(edgesSize * sizeof(int)); // Pseudo-critical edges
    int criticalCount = 0;
    int pseudoCriticalCount = 0;
    for (int i = 0; i < edgesSize; i++) {
        // Check if edge is critical
        int weightWithoutEdge = calculateMST(n, edgeList, edgesSize, i, -1);
        if (weightWithoutEdge > originalMSTWeight) {
            result[0][criticalCount++] = edgeList[i].index;
        } else {
            // Check if edge is pseudo-critical
            int weightWithEdge = calculateMST(n, edgeList, edgesSize, -1, i);
            if (weightWithEdge == originalMSTWeight) {
                result[1][pseudoCriticalCount++] = edgeList[i].index;
            }
        }
    }
    free(edgeList);
    *returnSize = 2;
    *returnColumnSizes = (int*)malloc(2 * sizeof(int));
    (*returnColumnSizes)[0] = criticalCount;
    (*returnColumnSizes)[1] = pseudoCriticalCount;
    return result;
}
