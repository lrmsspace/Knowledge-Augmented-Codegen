// Source: https://leetcode.com/problems/critical-connections-in-a-network/   |   Difficulty: Hard
//
// Problem Description:
// There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.
//
// A critical connection is a connection that, if removed, will make some servers unable to reach some other server.
//
// Return all critical connections in the network in any order.
//
// Example:
// Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
// Output: [[1,3]]
// Explanation: [[3,1]] is also accepted.
//
// Constraints:
// 2 <= n <= 105
// 	n - 1 <= connections.length <= 105
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no repeated connections.
//

class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> graph(n);
        for (const auto& conn : connections) {
            graph[conn[0]].push_back(conn[1]);
            graph[conn[1]].push_back(conn[0]);
        }
        
        vector<int> disc(n, -1), low(n, -1);
        vector<vector<int>> result;
        int time = 0;
        
        function<void(int, int)> dfs = [&](int u, int parent) {
            disc[u] = low[u] = time++;
            for (int v : graph[u]) {
                if (v == parent) continue; // Skip the parent node
                if (disc[v] == -1) { // If v is not visited
                    dfs(v, u);
                    low[u] = min(low[u], low[v]);
                    if (low[v] > disc[u]) {
                        result.push_back({u, v});
                    }
                } else {
                    low[u] = min(low[u], disc[v]);
                }
            }
        };
        
        for (int i = 0; i < n; i++) {
            if (disc[i] == -1) {
                dfs(i, -1);
            }
        }
        
        return result;          
    }
};
