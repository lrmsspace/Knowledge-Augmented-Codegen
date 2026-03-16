// Source: https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n denoting the number of nodes of a weighted directed graph. The nodes are numbered from 0 to n - 1.
//
// You are also given a 2D integer array edges where edges[i] = [fromi, toi, weighti] denotes that there exists a directed edge from fromi to toi with weight weighti.
//
// Lastly, you are given three distinct integers src1, src2, and dest denoting three distinct nodes of the graph.
//
// Return the minimum weight of a subgraph of the graph such that it is possible to reach dest from both src1 and src2 via a set of edges of this subgraph. In case such a subgraph does not exist, return -1.
//
// A subgraph is a graph whose vertices and edges are subsets of the original graph. The weight of a subgraph is the sum of weights of its constituent edges.
//
// Example:
// Input: n = 6, edges = [[0,2,2],[0,5,6],[1,0,3],[1,4,5],[2,1,1],[2,3,3],[2,3,4],[3,4,2],[4,5,1]], src1 = 0, src2 = 1, dest = 5
// Output: 9
// Explanation:
// The above figure represents the input graph.
// The blue edges represent one of the subgraphs that yield the optimal answer.
// Note that the subgraph [[1,0,3],[0,5,6]] also yields the optimal answer. It is not possible to get a subgraph with less weight satisfying all the constraints.
//
// Constraints:
// 3 <= n <= 105
// 	0 <= edges.length <= 105
// 	edges[i].length == 3
// 	0 <= fromi, toi, src1, src2, dest <= n - 1
// 	fromi != toi
// 	src1, src2, and dest are pairwise distinct.
// 	1 <= weight[i] <= 105
//

class Solution {
public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        // Build graph and reverse graph
        vector<vector<pair<int, int>>> graph(n);
        vector<vector<pair<int, int>>> revGraph(n);
        
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].emplace_back(v, w);
            revGraph[v].emplace_back(u, w);
        }
        
        // Dijkstra from src1, src2 and dest (on reverse graph)
        auto dijkstra = [&](int start, const vector<vector<pair<int, int>>>& g) {
            vector<long long> dist(n, LLONG_MAX);
            dist[start] = 0;
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
            pq.emplace(0, start);
            
            while (!pq.empty()) {
                auto [d, u] = pq.top(); pq.pop();
                if (d > dist[u]) continue;
                
                for (const auto& [v, w] : g[u]) {
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        pq.emplace(dist[v], v);
                    }
                }
            }
            return dist;
        };
        
        vector<long long> distSrc1 = dijkstra(src1, graph);
        vector<long long> distSrc2 = dijkstra(src2, graph);
        vector<long long> distDest = dijkstra(dest, revGraph);
        
        // Find minimum weight subgraph
        long long minWeight = LLONG_MAX;
        for (int i = 0; i < n; i++) {
            if (distSrc1[i] != LLONG_MAX && distSrc2[i] != LLONG_MAX && distDest[i] != LLONG_MAX) {
                minWeight = min(minWeight, distSrc1[i] + distSrc2[i] + distDest[i]);
            }
        }
        
        return minWeight == LLONG_MAX ? -1 : minWeight;         
    }
};
