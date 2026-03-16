// Source: https://leetcode.com/problems/minimize-the-total-price-of-the-trips/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected and unrooted tree with n nodes indexed from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Each node has an associated price. You are given an integer array price, where price[i] is the price of the ith node.
//
// The price sum of a given path is the sum of the prices of all nodes lying on that path.
//
// Additionally, you are given a 2D integer array trips, where trips[i] = [starti, endi] indicates that you start the ith trip from the node starti and travel to the node endi by any path you like.
//
// Before performing your first trip, you can choose some non-adjacent nodes and halve the prices.
//
// Return the minimum total price sum to perform all the given trips.
//
// Example:
// Input: n = 4, edges = [[0,1],[1,2],[1,3]], price = [2,2,10,6], trips = [[0,3],[2,1],[2,3]]
// Output: 23
// Explanation: The diagram above denotes the tree after rooting it at node 2. The first part shows the initial tree and the second part shows the tree after choosing nodes 0, 2, and 3, and making their price half.
// For the 1st trip, we choose path [0,1,3]. The price sum of that path is 1 + 2 + 3 = 6.
// For the 2nd trip, we choose path [2,1]. The price sum of that path is 2 + 5 = 7.
// For the 3rd trip, we choose path [2,1,3]. The price sum of that path is 5 + 2 + 3 = 10.
// The total price sum of all trips is 6 + 7 + 10 = 23.
// It can be proven, that 23 is the minimum answer that we can achieve.
//
// Constraints:
// 1 <= n <= 50
// 	edges.length == n - 1
// 	0 <= ai, bi <= n - 1
// 	edges represents a valid tree.
// 	price.length == n
// 	price[i] is an even integer.
// 	1 <= price[i] <= 1000
// 	1 <= trips.length <= 100
// 	0 <= starti, endi <= n - 1
//

int minimumTotalPrice(int n, int** edges, int edgesSize, int* edgesColSize, int* price, int priceSize, int** trips, int tripsSize, int* tripsColSize) {
    int graph[50][50] = {0};
    int freq[50] = {0};
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0], v = edges[i][1];
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    for (int t = 0; t < tripsSize; t++) {
        int start = trips[t][0], end = trips[t][1];
        int queue[50], front = 0, back = 0;
        int parent[50];
        memset(parent, -1, sizeof(parent));
        queue[back++] = start;
        parent[start] = start;
        while (front < back) {
            int node = queue[front++];
            if (node == end) break;
            for (int nei = 0; nei < n; nei++) {
                if (graph[node][nei] && parent[nei] == -1) {
                    parent[nei] = node;
                    queue[back++] = nei;
                }
            }
        }
        int cur = end;
        while (cur != start) {
            freq[cur]++;
            cur = parent[cur];
        }
        freq[start]++;
    }

    int dp[50][2]; // dp[i][0]: not halved, dp[i][1]: halved
    memset(dp, 0, sizeof(dp));

    // Post-order DFS to compute dp values
    int visited[50] = {0};
    void dfs(int node, int parent) {
        visited[node] = 1;
        dp[node][0] = freq[node] * price[node];
        dp[node][1] = freq[node] * (price[node] / 2);
        for (int nei = 0; nei < n; nei++) {
            if (graph[node][nei] && nei != parent && !visited[nei]) {
                dfs(nei, node);
                dp[node][0] += fmin(dp[nei][0], dp[nei][1]);
                dp[node][1] += dp[nei][0];
            }
        }
    }

    dfs(0, -1);
    return fmin(dp[0][0], dp[0][1]);        
}
