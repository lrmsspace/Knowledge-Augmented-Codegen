// Source: https://leetcode.com/problems/number-of-ways-to-reconstruct-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array pairs, where pairs[i] = [xi, yi], and:
//
//
// 	There are no duplicates.
// 	xi < yi
//
//
// Let ways be the number of rooted trees that satisfy the following conditions:
//
//
// 	The tree consists of nodes whose values appeared in pairs.
// 	A pair [xi, yi] exists in pairs if and only if xi is an ancestor of yi or yi is an ancestor of xi.
// 	Note: the tree does not have to be a binary tree.
//
//
// Two ways are considered to be different if there is at least one node that has different parents in both ways.
//
// Return:
//
//
// 	0 if ways == 0
// 	1 if ways == 1
// 	2 if ways > 1
//
//
// A rooted tree is a tree that has a single root node, and all edges are oriented to be outgoing from the root.
//
// An ancestor of a node is any node on the path from the root to that node (excluding the node itself). The root has no ancestors.
//
// Example:
// Input: pairs = [[1,2],[2,3]]
// Output: 1
// Explanation: There is exactly one valid rooted tree, which is shown in the above figure.
//
// Constraints:
// 1 <= pairs.length <= 105
// 	1 <= xi < yi <= 500
// 	The elements in pairs are unique.
//

int checkWays(int** pairs, int pairsSize, int* pairsColSize) {
    int maxNode = 0;
    for (int i = 0; i < pairsSize; ++i) {
        if (pairs[i][0] > maxNode) maxNode = pairs[i][0];
        if (pairs[i][1] > maxNode) maxNode = pairs[i][1];
    }

    int adj[maxNode + 1][maxNode + 1];
    memset(adj, 0, sizeof(adj));
    int degree[maxNode + 1];
    memset(degree, 0, sizeof(degree));

    for (int i = 0; i < pairsSize; ++i) {
        int u = pairs[i][0], v = pairs[i][1];
        adj[u][v] = 1;
        adj[v][u] = 1;
        degree[u]++;
        degree[v]++;
    }

    int root = -1;
    for (int i = 1; i <= maxNode; ++i) {
        if (degree[i] == maxNode - 1) {
            root = i;
            break;
        }
    }
    if (root == -1) return 0;

    int result = 1;
    for (int i = 1; i <= maxNode; ++i) {
        if (i == root) continue;

        int parent = -1;
        int parentDegree = maxNode + 1;
        for (int j = 1; j <= maxNode; ++j) {
            if (adj[i][j]) {
                if (degree[j] < parentDegree && degree[j] >= degree[i]) {
                    parentDegree = degree[j];
                    parent = j;
                }
            }
        }
        if (parent == -1) return 0;

        for (int j = 1; j <= maxNode; ++j) {
            if (adj[i][j] && j != parent) {
                if (!adj[parent][j]) return 0;
            }
        }
        if (parentDegree == degree[i]) result = 2;
    }

    return result;      
}
