// Source: https://leetcode.com/problems/shortest-path-in-a-weighted-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 1 with n nodes numbered from 1 to n. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an undirected edge from node ui to vi with weight wi.
//
// You are also given a 2D integer array queries of length q, where each queries[i] is either:
//
//
// 	[1, u, v, w'] – Update the weight of the edge between nodes u and v to w', where (u, v) is guaranteed to be an edge present in edges.
// 	[2, x] – Compute the shortest path distance from the root node 1 to node x.
//
//
// Return an integer array answer, where answer[i] is the shortest path distance from node 1 to x for the ith query of [2, x].
//
// Example:
// Input: n = 2, edges = [[1,2,7]], queries = [[2,2],[1,1,2,4],[2,2]]
//
// Output: [7,4]
//
// Explanation:
//
//
//
//
// 	Query [2,2]: The shortest path from root node 1 to node 2 is 7.
// 	Query [1,1,2,4]: The weight of edge (1,2) changes from 7 to 4.
// 	Query [2,2]: The shortest path from root node 1 to node 2 is 4.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	1 <= ui, vi <= n
// 	1 <= wi <= 104
// 	The input is generated such that edges represents a valid tree.
// 	1 <= queries.length == q <= 105
// 	queries[i].length == 2 or 4
// 	
// 		queries[i] == [1, u, v, w'] or,
// 		queries[i] == [2, x]
// 		1 <= u, v, x <= n
// 		(u, v) is always an edge from edges.
// 		1 <= w' <= 104
//

class Solution {
public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }
        
        vector<long long> dist(n + 1, 0);
        function<void(int, int)> dfs = [&](int node, int parent) {
            for (const auto& [neighbor, weight] : graph[node]) {
                if (neighbor != parent) {
                    dist[neighbor] = dist[node] + weight;
                    dfs(neighbor, node);
                }
            }
        };
        
        dfs(1, -1);
        
        vector<int> result;
        for (const auto& query : queries) {
            if (query[0] == 1) {
                int u = query[1], v = query[2], newWeight = query[3];
                // Update edge weight
                for (auto& [neighbor, weight] : graph[u]) {
                    if (neighbor == v) {
                        weight = newWeight;
                        break;
                    }
                }
                for (auto& [neighbor, weight] : graph[v]) {
                    if (neighbor == u) {
                        weight = newWeight;
                        break;
                    }
                }
                // Recompute distances
                dist[u] = dist[v] = 0;
                dfs(1, -1);
            } else if (query[0] == 2) {
                int x = query[1];
                result.push_back((int)dist[x]);
            }
        }
        
        return result;          
    }
};
