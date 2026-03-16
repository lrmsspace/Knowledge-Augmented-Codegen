// Source: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.
//
// Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
//
// The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.
//
// You are given a 2D integer array queries. For each queries[i] = [ui, vi], determine the number of ways to assign weights to edges in the path such that the cost of the path between ui and vi is odd.
//
// Return an array answer, where answer[i] is the number of valid assignments for queries[i].
//
// Since the answer may be large, apply modulo 109 + 7 to each answer[i].
//
// Note: For each query, disregard all edges not in the path between node ui and vi.
//
// Example:
// Input: edges = [[1,2]], queries = [[1,1],[1,2]]
//
// Output: [0,1]
//
// Explanation:
//
//
// 	Query [1,1]: The path from Node 1 to itself consists of no edges, so the cost is 0. Thus, the number of valid assignments is 0.
// 	Query [1,2]: The path from Node 1 to Node 2 consists of one edge (1 → 2). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi]
// 	1 <= queries.length <= 105
// 	queries[i] == [ui, vi]
// 	1 <= ui, vi <= n
// 	edges represents a valid tree.
//

class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;
        int n = edges.size() + 1;
        vector<vector<int>> graph(n + 1);
        
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        vector<int> depth(n + 1, -1);
        depth[1] = 0;
        queue<int> q;
        q.push(1);
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbor : graph[node]) {
                if (depth[neighbor] == -1) {
                    depth[neighbor] = depth[node] + 1;
                    q.push(neighbor);
                }
            }
        }
        
        vector<int> result;
        
        for (const auto& query : queries) {
            int u = query[0], v = query[1];
            int dist = abs(depth[u] - depth[v]);
            
            if (dist % 2 == 1) {
                // Odd distance
                result.push_back(1);
            } else {
                // Even distance
                result.push_back(0);
            }
        }
        
        return result;          
    }
};
