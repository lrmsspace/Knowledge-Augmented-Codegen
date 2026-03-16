// Source: https://leetcode.com/problems/minimum-increments-to-equalize-leaf-paths/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n and an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi] indicates an edge from node ui to vi .
//
// Each node i has an associated cost given by cost[i], representing the cost to traverse that node.
//
// The score of a path is defined as the sum of the costs of all nodes along the path.
//
// Your goal is to make the scores of all root-to-leaf paths equal by increasing the cost of any number of nodes by any non-negative amount.
//
// Return the minimum number of nodes whose cost must be increased to make all root-to-leaf path scores equal.
//
// Example:
// Input: n = 3, edges = [[0,1],[0,2]], cost = [2,1,3]
//
// Output: 1
//
// Explanation:
//
//
//
// There are two root-to-leaf paths:
//
//
// 	Path 0 → 1 has a score of 2 + 1 = 3.
// 	Path 0 → 2 has a score of 2 + 3 = 5.
//
//
// To make all root-to-leaf path scores equal to 5, increase the cost of node 1 by 2.
// Only one node is increased, so the output is 1.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi]
// 	0 <= ui, vi < n
// 	cost.length == n
// 	1 <= cost[i] <= 109
// 	The input is generated such that edges represents a valid tree.
//

int minIncrease(int n, int** edges, int edgesSize, int* edgesColSize, int* cost, int costSize) {
    // Build adjacency list
    int** adj = (int**)calloc(n, sizeof(int*));
    int* adjSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u] = (int*)realloc(adj[u], (adjSize[u] + 1) * sizeof(int));
        adj[u][adjSize[u]++] = v;
        adj[v] = (int*)realloc(adj[v], (adjSize[v] + 1) * sizeof(int));
        adj[v][adjSize[v]++] = u;
    }

    int result = 0;

    // DFS function to calculate increments
    int dfs(int node, int parent, int* maxPathCost) {
        if (adjSize[node] == 1 && parent != -1) { // Leaf node
            *maxPathCost = cost[node];
            return 0;
        }

        int totalIncrements = 0;
        int maxChildPathCost = 0;

        for (int i = 0; i < adjSize[node]; i++) {
            int neighbor = adj[node][i];
            if (neighbor == parent) continue;

            int childPathCost = 0;
            totalIncrements += dfs(neighbor, node, &childPathCost);
            if (childPathCost > maxChildPathCost) {
                maxChildPathCost = childPathCost;
            }
        }

        for (int i = 0; i < adjSize[node]; i++) {
            int neighbor = adj[node][i];
            if (neighbor == parent) continue;

            int childPathCost = 0;
            dfs(neighbor, node, &childPathCost);
            if (childPathCost < maxChildPathCost) {
                totalIncrements += 1; // Increment needed
            }
        }

        *maxPathCost = maxChildPathCost + cost[node];
        return totalIncrements;
    }

    int maxPathCost = 0;
    result = dfs(0, -1, &maxPathCost);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(adjSize);

    return result;      
}
