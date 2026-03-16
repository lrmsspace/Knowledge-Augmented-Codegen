// Source: https://leetcode.com/problems/number-of-good-paths/   |   Difficulty: Hard
//
// Problem Description:
// There is a tree (i.e. a connected, undirected graph with no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges.
//
// You are given a 0-indexed integer array vals of length n where vals[i] denotes the value of the ith node. You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// A good path is a simple path that satisfies the following conditions:
//
//
// 	The starting node and the ending node have the same value.
// 	All nodes between the starting node and the ending node have values less than or equal to the starting node (i.e. the starting node's value should be the maximum value along the path).
//
//
// Return the number of distinct good paths.
//
// Note that a path and its reverse are counted as the same path. For example, 0 -> 1 is considered to be the same as 1 -> 0. A single node is also considered as a valid path.
//
// Example:
// Input: vals = [1,3,2,1,3], edges = [[0,1],[0,2],[2,3],[2,4]]
// Output: 6
// Explanation: There are 5 good paths consisting of a single node.
// There is 1 additional good path: 1 -> 0 -> 2 -> 4.
// (The reverse path 4 -> 2 -> 0 -> 1 is treated as the same as 1 -> 0 -> 2 -> 4.)
// Note that 0 -> 2 -> 3 is not a good path because vals[2] > vals[0].
//
// Constraints:
// n == vals.length
// 	1 <= n <= 3 * 104
// 	0 <= vals[i] <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	edges represents a valid tree.
//

int numberOfGoodPaths(int* vals, int valsSize, int** edges, int edgesSize, int* edgesColSize) {
    int i;
    int **graph = (int**)calloc(valsSize, sizeof(int*));
    int *graphColSize = (int*)calloc(valsSize, sizeof(int));
    for (i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u] = (int*)realloc(graph[u], (graphColSize[u] + 1) * sizeof(int));
        graph[u][graphColSize[u]++] = v;
        graph[v] = (int*)realloc(graph[v], (graphColSize[v] + 1) * sizeof(int));
        graph[v][graphColSize[v]++] = u;
    }

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

    // Group nodes by their values
    #define MAX_VAL 100000
    int** valueGroups = (int**)calloc(MAX_VAL + 1, sizeof(int*));
    int* groupSizes = (int*)calloc(MAX_VAL + 1, sizeof(int));
    for (i = 0; i < valsSize; i++) {
        int val = vals[i];
        valueGroups[val] = (int*)realloc(valueGroups[val], (groupSizes[val] + 1) * sizeof(int));
        valueGroups[val][groupSizes[val]++] = i;
    }
    UnionFind* uf = ufCreate(valsSize);
    int goodPaths = 0;

    for (int val = 0; val <= MAX_VAL; val++) {
        if (groupSizes[val] == 0) continue;

        // Union nodes with neighbors of less than or equal value
        for (i = 0; i < groupSizes[val]; i++) {
            int node = valueGroups[val][i];
            for (int j = 0; j < graphColSize[node]; j++) {
                int neighbor = graph[node][j];
                if (vals[neighbor] <= val) {
                    ufUnion(uf, node, neighbor);
                }
            }
        }

        // Count good paths in the current value group
        int* componentCount = (int*)calloc(valsSize, sizeof(int));
        for (i = 0; i < groupSizes[val]; i++) {
            int node = valueGroups[val][i];
            int root = ufFind(uf, node);
            componentCount[root]++;
        }
        for (i = 0; i < valsSize; i++) {
            if (componentCount[i] > 0) {
                goodPaths += (componentCount[i] * (componentCount[i] + 1)) / 2;
            }
        }
        free(componentCount);
    }
    // Cleanup
    for (i = 0; i < valsSize; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphColSize);
    for (int val = 0; val <= MAX_VAL; val++) {
        free(valueGroups[val]);
    }
    free(valueGroups);
    free(groupSizes);
    free(uf);
    return goodPaths;
}
