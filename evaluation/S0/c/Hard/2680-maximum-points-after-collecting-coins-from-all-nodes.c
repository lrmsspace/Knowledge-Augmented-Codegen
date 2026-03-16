// Source: https://leetcode.com/problems/maximum-points-after-collecting-coins-from-all-nodes/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree rooted at node 0 with n nodes labeled from 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree. You are also given a 0-indexed array coins of size n where coins[i] indicates the number of coins in the vertex i, and an integer k.
//
// Starting from the root, you have to collect all the coins such that the coins at a node can only be collected if the coins of its ancestors have been already collected.
//
// Coins at nodei can be collected in one of the following ways:
//
//
// 	Collect all the coins, but you will get coins[i] - k points. If coins[i] - k is negative then you will lose abs(coins[i] - k) points.
// 	Collect all the coins, but you will get floor(coins[i] / 2) points. If this way is used, then for all the nodej present in the subtree of nodei, coins[j] will get reduced to floor(coins[j] / 2).
//
//
// Return the maximum points you can get after collecting the coins from all the tree nodes.
//
// Example:
// Input: edges = [[0,1],[1,2],[2,3]], coins = [10,10,3,3], k = 5
// Output: 11                        
// Explanation: 
// Collect all the coins from node 0 using the first way. Total points = 10 - 5 = 5.
// Collect all the coins from node 1 using the first way. Total points = 5 + (10 - 5) = 10.
// Collect all the coins from node 2 using the second way so coins left at node 3 will be floor(3 / 2) = 1. Total points = 10 + floor(3 / 2) = 11.
// Collect all the coins from node 3 using the second way. Total points = 11 + floor(1 / 2) = 11.
// It can be shown that the maximum points we can get after collecting coins from all the nodes is 11.
//
// Constraints:
// n == coins.length
// 	2 <= n <= 105
// 	0 <= coins[i] <= 104
// 	edges.length == n - 1
// 	0 <= edges[i][0], edges[i][1] < n
// 	0 <= k <= 104
//

int maximumPoints(int** edges, int edgesSize, int* edgesColSize, int* coins, int coinsSize, int k) {
    int n = coinsSize;
    typedef struct Node {
        int id;
        struct Node** neighbors;
        int neighborCount;
    } Node;

    Node* nodes = (Node*)malloc(n * sizeof(Node));
    for (int i = 0; i < n; i++) {
        nodes[i].id = i;
        nodes[i].neighbors = (Node**)malloc(n * sizeof(Node*));
        nodes[i].neighborCount = 0;
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        nodes[u].neighbors[nodes[u].neighborCount++] = &nodes[v];
        nodes[v].neighbors[nodes[v].neighborCount++] = &nodes[u];
    }

    long long dfs(Node* node, Node* parent, int* coins, int k) {
        long long totalPoints = 0;
        for (int i = 0; i < node->neighborCount; i++) {
            Node* neighbor = node->neighbors[i];
            if (neighbor == parent) continue;
            totalPoints += dfs(neighbor, node, coins, k);
        }
        long long collectAll = coins[node->id] - k;
        long long collectHalf = coins[node->id] / 2;
        if (collectAll > collectHalf) {
            totalPoints += collectAll;
        } else {
            totalPoints += collectHalf;
            coins[node->id] /= 2;
        }
        return totalPoints;
    }

    long long result = dfs(&nodes[0], NULL, coins, k);

    for (int i = 0; i < n; i++) {
        free(nodes[i].neighbors);
    }
    free(nodes);

    return (int)result;
}
