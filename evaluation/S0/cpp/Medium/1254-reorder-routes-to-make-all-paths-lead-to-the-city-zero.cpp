// Source: https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/   |   Difficulty: Medium
//
// Problem Description:
// There are n cities numbered from 0 to n - 1 and n - 1 roads such that there is only one way to travel between two different cities (this network form a tree). Last year, The ministry of transport decided to orient the roads in one direction because they are too narrow.
//
// Roads are represented by connections where connections[i] = [ai, bi] represents a road from city ai to city bi.
//
// This year, there will be a big event in the capital (city 0), and many people want to travel to this city.
//
// Your task consists of reorienting some roads such that each city can visit the city 0. Return the minimum number of edges changed.
//
// It's guaranteed that each city can reach city 0 after reorder.
//
// Example:
// Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
// Output: 3
// Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).
//
// Constraints:
// 2 <= n <= 5 * 104
// 	connections.length == n - 1
// 	connections[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
//

class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& conn : connections) {
            graph[conn[0]].emplace_back(conn[1], 1); // original direction
            graph[conn[1]].emplace_back(conn[0], 0); // reverse direction
        }

        int changes = 0;
        vector<bool> visited(n, false);
        function<void(int)> dfs = [&](int node) {
            visited[node] = true;
            for (const auto& [neighbor, direction] : graph[node]) {
                if (!visited[neighbor]) {
                    changes += direction; // count if it's in original direction
                    dfs(neighbor);
                }
            }
        };

        dfs(0);
        return changes;         
    }
};
