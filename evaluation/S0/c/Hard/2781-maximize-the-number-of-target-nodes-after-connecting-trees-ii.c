// Source: https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/   |   Difficulty: Hard
//
// Problem Description:
// There exist two undirected trees with n and m nodes, labeled from [0, n - 1] and [0, m - 1], respectively.
//
// You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.
//
// Node u is target to node v if the number of edges on the path from u to v is even. Note that a node is always target to itself.
//
// Return an array of n integers answer, where answer[i] is the maximum possible number of nodes that are target to node i of the first tree if you had to connect one node from the first tree to another node in the second tree.
//
// Note that queries are independent from each other. That is, for every query you will remove the added edge before proceeding to the next query.
//
// Example:
// Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]
//
// Output: [8,7,7,8,8]
//
// Explanation:
//
//
// 	For i = 0, connect node 0 from the first tree to node 0 from the second tree.
// 	For i = 1, connect node 1 from the first tree to node 4 from the second tree.
// 	For i = 2, connect node 2 from the first tree to node 7 from the second tree.
// 	For i = 3, connect node 3 from the first tree to node 0 from the second tree.
// 	For i = 4, connect node 4 from the first tree to node 4 from the second tree.
//
// Constraints:
// 2 <= n, m <= 105
// 	edges1.length == n - 1
// 	edges2.length == m - 1
// 	edges1[i].length == edges2[i].length == 2
// 	edges1[i] = [ai, bi]
// 	0 <= ai, bi < n
// 	edges2[i] = [ui, vi]
// 	0 <= ui, vi < m
// 	The input is generated such that edges1 and edges2 represent valid trees.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxTargetNodes(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size, int* edges2ColSize, int* returnSize) {
    // Helper function to perform DFS and calculate even/odd level counts
    void dfs(int node, int parent, int level, int (*adj)[2], int *evenCount, int *oddCount, int *visited) {
        visited[node] = 1;
        if (level % 2 == 0) {
            (*evenCount)++;
        } else {
            (*oddCount)++;
        }
        for (int i = 0; i < edges2Size + 1; i++) {
            if (adj[i][0] == node && adj[i][1] != parent && !visited[adj[i][1]]) {
                dfs(adj[i][1], node, level + 1, adj, evenCount, oddCount, visited);
            } else if (adj[i][1] == node && adj[i][0] != parent && !visited[adj[i][0]]) {
                dfs(adj[i][0], node, level + 1, adj, evenCount, oddCount, visited);
            }
        }
    }

    // Build adjacency list for the second tree
    int (*adj2)[2] = malloc((edges2Size + 1) * sizeof(int[2]));
    for (int i = 0; i < edges2Size; i++) {
        adj2[i][0] = edges2[i][0];
        adj2[i][1] = edges2[i][1];
    }

    // Calculate even and odd level counts for the second tree
    int evenCount = 0, oddCount = 0;
    int *visited = calloc(edges2Size + 1, sizeof(int));
    dfs(0, -1, 0, adj2, &evenCount, &oddCount, visited);
    free(visited);
    free(adj2);

    // Prepare the result array
    int n = edges1Size + 1;
    int *result = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        // Determine the level of node i in the first tree
        int level = 0;
        int current = i;
        int parent = -1;
        int found = 0;
        while (!found) {
            found = 1;
            for (int j = 0; j < edges1Size; j++) {
                if (edges1[j][0] == current && edges1[j][1] != parent) {
                    parent = current;
                    current = edges1[j][1];
                    level++;
                    found = 0;
                    break;
                } else if (edges1[j][1] == current && edges1[j][0] != parent) {
                    parent = current;
                    current = edges1[j][0];
                    level++;
                    found = 0;
                    break;
                }
            }
        }
        // Calculate the maximum target nodes for node i
        if (level % 2 == 0) {
            result[i] = evenCount + 1; // +1 for the node itself
        } else {
            result[i] = oddCount + 1; // +1 for the node itself
        }
    }
    *returnSize = n;
    return result;
}
