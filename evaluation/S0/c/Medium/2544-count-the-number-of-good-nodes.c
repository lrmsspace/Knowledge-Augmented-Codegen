// Source: https://leetcode.com/problems/count-the-number-of-good-nodes/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// A node is good if all the subtrees rooted at its children have the same size.
//
// Return the number of good nodes in the given tree.
//
// A subtree of treeName is a tree consisting of a node in treeName and all of its descendants.
//
// Example:
// Input: edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
//
// Output: 7
//
// Explanation:
//
// All of the nodes of the given tree are good.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	The input is generated such that edges represents a valid tree.
//

int countGoodNodes(int** edges, int edgesSize, int* edgesColSize) {
    int n = edgesSize + 1;
    int* adj[n];
    int adjSize[n];
    for (int i = 0; i < n; i++) {
        adjSize[i] = 0;
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u] = realloc(adj[u], sizeof(int) * (adjSize[u] + 1));
        adj[u][adjSize[u]++] = v;
        adj[v] = realloc(adj[v], sizeof(int) * (adjSize[v] + 1));
        adj[v][adjSize[v]++] = u;
    }

    int goodNodeCount = 0;

    int dfs(int node, int parent) {
        int subtreeSizes[adjSize[node]];
        int count = 0;
        for (int i = 0; i < adjSize[node]; i++) {
            int neighbor = adj[node][i];
            if (neighbor != parent) {
                subtreeSizes[count++] = dfs(neighbor, node);
            }
        }
        if (count == 0) {
            goodNodeCount++;
            return 1;
        }
        int firstSize = subtreeSizes[0];
        for (int i = 1; i < count; i++) {
            if (subtreeSizes[i] != firstSize) {
                return firstSize + 1;
            }
        }
        goodNodeCount++;
        return firstSize * count + 1;
    }

    dfs(0, -1);
    return goodNodeCount;       
}
