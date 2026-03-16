// Source: https://leetcode.com/problems/find-weighted-median-node-in-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an edge from node ui to vi with weight wi.
//
// The weighted median node is defined as the first node x on the path from ui to vi such that the sum of edge weights from ui to x is greater than or equal to half of the total path weight.
//
// You are given a 2D integer array queries. For each queries[j] = [uj, vj], determine the weighted median node along the path from uj to vj.
//
// Return an array ans, where ans[j] is the node index of the weighted median for queries[j].
//
// Example:
// Input: n = 2, edges = [[0,1,7]], queries = [[1,0],[0,1]]
//
// Output: [0,1]
//
// Explanation:
//
//
//
//
// 	
// 		
// 			Query
// 			Path
// 			Edge
// 			Weights
// 			Total
// 			Path
// 			Weight
// 			Half
// 			Explanation
// 			Answer
// 		
// 	
// 	
// 		
// 			[1, 0]
// 			1 → 0
// 			[7]
// 			7
// 			3.5
// 			Sum from 1 → 0 = 7 >= 3.5, median is node 0.
// 			0
// 		
// 		
// 			[0, 1]
// 			0 → 1
// 			[7]
// 			7
// 			3.5
// 			Sum from 0 → 1 = 7 >= 3.5, median is node 1.
// 			1
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	0 <= ui, vi < n
// 	1 <= wi <= 109
// 	1 <= queries.length <= 105
// 	queries[j] == [uj, vj]
// 	0 <= uj, vj < n
// 	The input is generated such that edges represents a valid tree.
//

class Solution {
public:
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        // Build adjacency list
        vector<vector<pair<int, long long>>> graph(n);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            long long w = edge[2];
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }
        
        // Preprocessing for LCA and distance
        const int LOG = 20;
        vector<vector<int>> parent(n, vector<int>(LOG, -1));
        vector<long long> depth(n, 0);
        vector<long long> dist(n, 0);
        
        function<void(int, int)> dfs = [&](int u, int p) {
            for (const auto& [v, w] : graph[u]) {
                if (v != p) {
                    parent[v][0] = u;
                    depth[v] = depth[u] + 1;
                    dist[v] = dist[u] + w;
                    dfs(v, u);
                }
            }
        };
        
        dfs(0, -1);
        
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i < n; ++i) {
                if (parent[i][j - 1] != -1) {
                    parent[i][j] = parent[parent[i][j - 1]][j - 1];
                }
            }
        }
        
        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);
            for (int j = LOG - 1; j >= 0; --j) {
                if (parent[u][j] != -1 && depth[parent[u][j]] >= depth[v]) {
                    u = parent[u][j];
                }
            }
            if (u == v) return u;
            for (int j = LOG - 1; j >= 0; --j) {
                if (parent[u][j] != parent[v][j]) {
                    u = parent[u][j];
                    v = parent[v][j];
                }
            }
            return parent[u][0];
        };
        
        auto getKthAncestor = [&](int u, long long k) {
            for (int j = 0; j < LOG; ++j) {
                if (k & (1LL << j)) {
                    u = parent[u][j];
                    if (u == -1) break;
                }
            }
            return u;
        };
        vector<int> result;
        for (const auto& query : queries) {
            int u = query[0], v = query[1];
            int ancestor = lca(u, v);
            long long totalDist = dist[u] + dist[v] - 2 * dist[ancestor];
            long long halfDist = (totalDist + 1) / 2;
            
            if (dist[u] - dist[ancestor] >= halfDist) {
                // Move up from u
                int curr = u;
                long long need = halfDist;
                for (int j = LOG - 1; j >= 0; --j) {
                    if (parent[curr][j] != -1 && dist[curr] - dist[parent[curr][j]] <= need) {
                        need -= (dist[curr] - dist[parent[curr][j]]);
                        curr = parent[curr][j];
                    }
                }
                result.push_back(curr);
            } else {
                // Move up from v
                long long need = halfDist - (dist[u] - dist[ancestor]);
                int curr = v;
                for (int j = LOG - 1; j >= 0; --j) {
                    if (parent[curr][j] != -1 && dist[curr] - dist[parent[curr][j]] <= need) {
                        need -= (dist[curr] - dist[parent[curr][j]]);
                        curr = parent[curr][j];
                    }
                }
                result.push_back(curr);
            }
        }
        return result;
    }
};
