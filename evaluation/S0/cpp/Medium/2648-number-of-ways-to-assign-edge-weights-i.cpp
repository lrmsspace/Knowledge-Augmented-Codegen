// Source: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.
//
// Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
//
// The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.
//
// Select any one node x at the maximum depth. Return the number of ways to assign edge weights in the path from node 1 to x such that its total cost is odd.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Note: Ignore all edges not in the path from node 1 to x.
//
// Example:
// Input: edges = [[1,2]]
//
// Output: 1
//
// Explanation:
//
//
// 	The path from Node 1 to Node 2 consists of one edge (1 → 2).
// 	Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi]
// 	1 <= ui, vi <= n
// 	edges represents a valid tree.
//

class Solution {
public:
    int assignEdgeWeights(vector<vector<int>>& edges) {
        const int MOD = 1e9 + 7;
        int n = edges.size() + 1;
        vector<vector<int>> graph(n + 1);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        // BFS to find the maximum depth
        queue<pair<int, int>> q; // {node, depth}
        vector<bool> visited(n + 1, false);
        q.push({1, 0});
        visited[1] = true;
        int maxDepth = 0;

        while (!q.empty()) {
            auto [node, depth] = q.front();
            q.pop();
            maxDepth = max(maxDepth, depth);

            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push({neighbor, depth + 1});
                }
            }
        }

        // The number of ways to assign weights such that the total cost is odd
        // is 2^(maxDepth - 1) since we can choose weights for (maxDepth - 1) edges freely
        // and the last edge must be chosen to make the total cost odd.
        long long result = 1;
        for (int i = 0; i < maxDepth - 1; ++i) {
            result = (result * 2) % MOD;
        }

        return static_cast<int>(result);            
    }
};
