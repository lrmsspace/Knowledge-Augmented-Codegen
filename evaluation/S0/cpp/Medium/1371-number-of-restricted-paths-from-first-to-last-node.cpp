// Source: https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected weighted connected graph. You are given a positive integer n which denotes that the graph has n nodes labeled from 1 to n, and an array edges where each edges[i] = [ui, vi, weighti] denotes that there is an edge between nodes ui and vi with weight equal to weighti.
//
// A path from node start to node end is a sequence of nodes [z0, z1, z2, ..., zk] such that z0 = start and zk = end and there is an edge between zi and zi+1 where 0 <= i <= k-1.
//
// The distance of a path is the sum of the weights on the edges of the path. Let distanceToLastNode(x) denote the shortest distance of a path between node n and node x. A restricted path is a path that also satisfies that distanceToLastNode(zi) > distanceToLastNode(zi+1) where 0 <= i <= k-1.
//
// Return the number of restricted paths from node 1 to node n. Since that number may be too large, return it modulo 109 + 7.
//
// Example:
// Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
// Output: 3
// Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The three restricted paths are:
// 1) 1 --> 2 --> 5
// 2) 1 --> 2 --> 3 --> 5
// 3) 1 --> 3 --> 5
//
// Constraints:
// 1 <= n <= 2 * 104
// 	n - 1 <= edges.length <= 4 * 104
// 	edges[i].length == 3
// 	1 <= ui, vi <= n
// 	ui != vi
// 	1 <= weighti <= 105
// 	There is at most one edge between any two nodes.
// 	There is at least one path between any two nodes.
//

class Solution {
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        const int MOD = 1e9 + 7;

        // Build the graph
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto& edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
            graph[edge[1]].emplace_back(edge[0], edge[2]);
        }

        // Dijkstra's algorithm to find shortest distances from node n
        vector<int> dist(n + 1, INT_MAX);
        dist[n] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, n);

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;

            for (const auto& [v, w] : graph[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }

        // DP to count restricted paths
        vector<int> dp(n + 1, -1);
        function<int(int)> dfs = [&](int u) {
            if (u == n) return 1;
            if (dp[u] != -1) return dp[u];

            int count = 0;
            for (const auto& [v, _] : graph[u]) {
                if (dist[u] > dist[v]) {
                    count = (count + dfs(v)) % MOD;
                }
            }
            return dp[u] = count;
        };

        return dfs(1);          
    }
};
