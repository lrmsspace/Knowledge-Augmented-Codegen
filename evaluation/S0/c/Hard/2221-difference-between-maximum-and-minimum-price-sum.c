// Source: https://leetcode.com/problems/difference-between-maximum-and-minimum-price-sum/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected and initially unrooted tree with n nodes indexed from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Each node has an associated price. You are given an integer array price, where price[i] is the price of the ith node.
//
// The price sum of a given path is the sum of the prices of all nodes lying on that path.
//
// The tree can be rooted at any node root of your choice. The incurred cost after choosing root is the difference between the maximum and minimum price sum amongst all paths starting at root.
//
// Return the maximum possible cost amongst all possible root choices.
//
// Example:
// Input: n = 6, edges = [[0,1],[1,2],[1,3],[3,4],[3,5]], price = [9,8,7,6,10,5]
// Output: 24
// Explanation: The diagram above denotes the tree after rooting it at node 2. The first part (colored in red) shows the path with the maximum price sum. The second part (colored in blue) shows the path with the minimum price sum.
// - The first path contains nodes [2,1,3,4]: the prices are [7,8,6,10], and the sum of the prices is 31.
// - The second path contains the node [2] with the price [7].
// The difference between the maximum and minimum price sum is 24. It can be proved that 24 is the maximum cost.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	0 <= ai, bi <= n - 1
// 	edges represents a valid tree.
// 	price.length == n
// 	1 <= price[i] <= 105
//

long long maxOutput(int n, int** edges, int edgesSize, int* edgesColSize, int* price, int priceSize) {
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

    long long maxCost = 0;

    long long dfs(Node* node, Node* parent, int* price, long long* maxPath) {
        long long max1 = 0, max2 = 0;
        for (int i = 0; i < node->neighborCount; i++) {
            Node* neighbor = node->neighbors[i];
            if (neighbor == parent) continue;
            long long pathSum = dfs(neighbor, node, price, maxPath);
            if (pathSum > max1) {
                max2 = max1;
                max1 = pathSum;
            } else if (pathSum > max2) {
                max2 = pathSum;
            }
        }
        long long currentPathSum = price[node->id] + max1;
        if (parent == NULL) {
            *maxPath = currentPathSum;
        } else {
            long long cost = currentPathSum + price[parent->id] + max2 - price[parent->id];
            if (cost > maxCost) {
                maxCost = cost;
            }
        }
        return currentPathSum;
    }

    long long overallMaxPath = 0;
    dfs(&nodes[0], NULL, price, &overallMaxPath);

    for (int i = 0; i < n; i++) {
        free(nodes[i].neighbors);
    }
    free(nodes);

    return maxCost;
}
