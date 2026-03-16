// Source: https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph (the "original graph") with n nodes labeled from 0 to n - 1. You decide to subdivide each edge in the graph into a chain of nodes, with the number of new nodes varying between each edge.
//
// The graph is given as a 2D array of edges where edges[i] = [ui, vi, cnti] indicates that there is an edge between nodes ui and vi in the original graph, and cnti is the total number of new nodes that you will subdivide the edge into. Note that cnti == 0 means you will not subdivide the edge.
//
// To subdivide the edge [ui, vi], replace it with (cnti + 1) new edges and cnti new nodes. The new nodes are x1, x2, ..., xcnti, and the new edges are [ui, x1], [x1, x2], [x2, x3], ..., [xcnti-1, xcnti], [xcnti, vi].
//
// In this new graph, you want to know how many nodes are reachable from the node 0, where a node is reachable if the distance is maxMoves or less.
//
// Given the original graph and maxMoves, return the number of nodes that are reachable from node 0 in the new graph.
//
// Example:
// Input: edges = [[0,1,10],[0,2,1],[1,2,2]], maxMoves = 6, n = 3
// Output: 13
// Explanation: The edge subdivisions are shown in the image above.
// The nodes that are reachable are highlighted in yellow.
//
// Constraints:
// 0 <= edges.length <= min(n * (n - 1) / 2, 104)
// 	edges[i].length == 3
// 	0 <= ui < vi < n
// 	There are no multiple edges in the graph.
// 	0 <= cnti <= 104
// 	0 <= maxMoves <= 109
// 	1 <= n <= 3000
//

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        // Build graph
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], cnt = edge[2];
            graph[u].emplace_back(v, cnt + 1);
            graph[v].emplace_back(u, cnt + 1);
        }
        
        // Dijkstra's algorithm
        vector<long long> dist(n, LLONG_MAX);
        dist[0] = 0;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        pq.emplace(0, 0);
        
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            
            for (const auto& [v, w] : graph[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
        
        // Count reachable nodes
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (dist[i] <= maxMoves) {
                result++;
            }
        }
        
        // Count reachable new nodes on edges
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], cnt = edge[2];
            long long usedFromU = max(0LL, maxMoves - dist[u]);
            long long usedFromV = max(0LL, maxMoves - dist[v]);
            result += min((long long)cnt, usedFromU + usedFromV);
        }
        
        return result;          
    }
};
