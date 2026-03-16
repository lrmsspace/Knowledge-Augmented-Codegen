// Source: https://leetcode.com/problems/find-edges-in-shortest-paths/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted graph of n nodes numbered from 0 to n - 1. The graph consists of m edges represented by a 2D array edges, where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight wi.
//
// Consider all the shortest paths from node 0 to node n - 1 in the graph. You need to find a boolean array answer where answer[i] is true if the edge edges[i] is part of at least one shortest path. Otherwise, answer[i] is false.
//
// Return the array answer.
//
// Note that the graph may not be connected.
//
// Example:
// Input: n = 6, edges = [[0,1,4],[0,2,1],[1,3,2],[1,4,3],[1,5,1],[2,3,1],[3,5,3],[4,5,2]]
//
// Output: [true,true,true,false,true,true,true,false]
//
// Explanation:
//
// The following are all the shortest paths between nodes 0 and 5:
//
//
// 	The path 0 -> 1 -> 5: The sum of weights is 4 + 1 = 5.
// 	The path 0 -> 2 -> 3 -> 5: The sum of weights is 1 + 1 + 3 = 5.
// 	The path 0 -> 2 -> 3 -> 1 -> 5: The sum of weights is 1 + 1 + 2 + 1 = 5.
//
// Constraints:
// 2 <= n <= 5 * 104
// 	m == edges.length
// 	1 <= m <= min(5 * 104, n * (n - 1) / 2)
// 	0 <= ai, bi < n
// 	ai != bi
// 	1 <= wi <= 105
// 	There are no repeated edges.
//

class Solution {
public:
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> graph(n);
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }
        
        auto dijkstra = [&](int start) {
            vector<long long> dist(n, LLONG_MAX);
            dist[start] = 0;
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
            pq.emplace(0, start);
            
            while (!pq.empty()) {
                auto [d, u] = pq.top(); pq.pop();
                if (d > dist[u]) continue;
                
                for (auto& [v, w] : graph[u]) {
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        pq.emplace(dist[v], v);
                    }
                }
            }
            return dist;
        };
        
        vector<long long> distFromStart = dijkstra(0);
        vector<long long> distFromEnd = dijkstra(n - 1);
        
        vector<bool> answer(edges.size(), false);
        long long shortestPathLength = distFromStart[n - 1];
        
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            if (distFromStart[u] + w + distFromEnd[v] == shortestPathLength ||
                distFromStart[v] + w + distFromEnd[u] == shortestPathLength) {
                answer[i] = true;
            }
        }
        
        return answer;          
    }
};
