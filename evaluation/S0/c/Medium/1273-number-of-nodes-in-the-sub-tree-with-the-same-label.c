// Source: https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/   |   Difficulty: Medium
//
// Problem Description:
// You are given a tree (i.e. a connected, undirected graph that has no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges. The root of the tree is the node 0, and each node of the tree has a label which is a lower-case character given in the string labels (i.e. The node with the number i has the label labels[i]).
//
// The edges array is given on the form edges[i] = [ai, bi], which means there is an edge between nodes ai and bi in the tree.
//
// Return an array of size n where ans[i] is the number of nodes in the subtree of the ith node which have the same label as node i.
//
// A subtree of a tree T is the tree consisting of a node in T and all of its descendant nodes.
//
// Example:
// Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], labels = "abaedcd"
// Output: [2,1,1,1,1,1,1]
// Explanation: Node 0 has label 'a' and its sub-tree has node 2 with label 'a' as well, thus the answer is 2. Notice that any node is part of its sub-tree.
// Node 1 has a label 'b'. The sub-tree of node 1 contains nodes 1,4 and 5, as nodes 4 and 5 have different labels than node 1, the answer is just 1 (the node itself).
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	labels.length == n
// 	labels is consisting of only of lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countSubTrees(int n, int** edges, int edgesSize, int* edgesColSize, char* labels, int* returnSize) {
    // Build adjacency list
    int** adj = (int**)malloc(n * sizeof(int*));
    int* adjSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        adj[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][adjSize[u]++] = v;
        adj[v][adjSize[v]++] = u;
    }

    int* result = (int*)calloc(n, sizeof(int));
    int* visited = (int*)calloc(n, sizeof(int));

    // DFS function to count labels
    void dfs(int node, int* count) {
        visited[node] = 1;
        int labelIndex = labels[node] - 'a';
        count[labelIndex]++;
        for (int i = 0; i < adjSize[node]; i++) {
            int neighbor = adj[node][i];
            if (!visited[neighbor]) {
                int* childCount = (int*)calloc(26, sizeof(int));
                dfs(neighbor, childCount);
                for (int j = 0; j < 26; j++) {
                    count[j] += childCount[j];
                }
                free(childCount);
            }
        }
        result[node] = count[labelIndex];
    }

    int* count = (int*)calloc(26, sizeof(int));
    dfs(0, count);
    free(count);

    // Free adjacency list
    for (int i = 0; i < n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(adjSize);
    free(visited);

    *returnSize = n;
    return result;      
}
