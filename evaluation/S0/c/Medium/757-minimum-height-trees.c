// Source: https://leetcode.com/problems/minimum-height-trees/   |   Difficulty: Medium
//
// Problem Description:
// A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.
//
// Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai, bi] indicates that there is an undirected edge between the two nodes ai and bi in the tree, you can choose any node of the tree as the root. When you select a node x as the root, the result tree has height h. Among all possible rooted trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).
//
// Return a list of all MHTs' root labels. You can return the answer in any order.
//
// The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.
//
// Example:
// Input: n = 4, edges = [[1,0],[1,2],[1,3]]
// Output: [1]
// Explanation: As shown, the height of the tree is 1 when the root is the node with label 1 which is the only MHT.
//
// Constraints:
// 1 <= n <= 2 * 104
// 	edges.length == n - 1
// 	0 <= ai, bi < n
// 	ai != bi
// 	All the pairs (ai, bi) are distinct.
// 	The given input is guaranteed to be a tree and there will be no repeated edges.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMinHeightTrees(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    if (n == 1) {
        int* res = (int*)malloc(sizeof(int));
        res[0] = 0;
        *returnSize = 1;
        return res;
    }

    // Build the adjacency list
    int** graph = (int**)malloc(n * sizeof(int*));
    int* degree = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u][degree[u]++] = v;
        graph[v][degree[v]++] = u;
    }

    // Initialize the first layer of leaves
    int* leaves = (int*)malloc(n * sizeof(int));
    int leavesCount = 0;
    for (int i = 0; i < n; i++) {
        if (degree[i] == 1) {
            leaves[leavesCount++] = i;
        }
    }

    // Trim the leaves until reaching the centroids
    int remainingNodes = n;
    while (remainingNodes > 2) {
        remainingNodes -= leavesCount;
        int newLeavesCount = 0;
        for (int i = 0; i < leavesCount; i++) {
            int leaf = leaves[i];
            for (int j = 0; j < degree[leaf]; j++) {
                int neighbor = graph[leaf][j];
                degree[neighbor]--;
                if (degree[neighbor] == 1) {
                    leaves[newLeavesCount++] = neighbor;
                }
            }
            degree[leaf] = 0; // Mark as removed
        }
        leavesCount = newLeavesCount;
    }

    // The remaining nodes are the centroids
    int* result = (int*)malloc(remainingNodes * sizeof(int));
    for (int i = 0; i < remainingNodes; i++) {
        result[i] = leaves[i];
    }
    *returnSize = remainingNodes;

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(degree);
    free(leaves);       
    return result;
}
