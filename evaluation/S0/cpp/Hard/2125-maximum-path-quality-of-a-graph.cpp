// Source: https://leetcode.com/problems/maximum-path-quality-of-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph with n nodes numbered from 0 to n - 1 (inclusive). You are given a 0-indexed integer array values where values[i] is the value of the ith node. You are also given a 0-indexed 2D integer array edges, where each edges[j] = [uj, vj, timej] indicates that there is an undirected edge between the nodes uj and vj, and it takes timej seconds to travel between the two nodes. Finally, you are given an integer maxTime.
//
// A valid path in the graph is any path that starts at node 0, ends at node 0, and takes at most maxTime seconds to complete. You may visit the same node multiple times. The quality of a valid path is the sum of the values of the unique nodes visited in the path (each node's value is added at most once to the sum).
//
// Return the maximum quality of a valid path.
//
// Note: There are at most four edges connected to each node.
//
// Example:
// Input: values = [0,32,10,43], edges = [[0,1,10],[1,2,15],[0,3,10]], maxTime = 49
// Output: 75
// Explanation:
// One possible path is 0 -> 1 -> 0 -> 3 -> 0. The total time taken is 10 + 10 + 10 + 10 = 40 <= 49.
// The nodes visited are 0, 1, and 3, giving a maximal path quality of 0 + 32 + 43 = 75.
//
// Constraints:
// n == values.length
// 	1 <= n <= 1000
// 	0 <= values[i] <= 108
// 	0 <= edges.length <= 2000
// 	edges[j].length == 3 
// 	0 <= uj < vj <= n - 1
// 	10 <= timej, maxTime <= 100
// 	All the pairs [uj, vj] are unique.
// 	There are at most four edges connected to each node.
// 	The graph may not be connected.
//

class Solution {
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        int n = values.size();
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], time = edge[2];
            graph[u].emplace_back(v, time);
            graph[v].emplace_back(u, time);
        }
        
        int maxQuality = 0;
        vector<bool> visited(n, false);
        
        function<void(int, int, int)> dfs = [&](int node, int timeSpent, int currentQuality) {
            if (timeSpent > maxTime) return;
            if (node == 0) {
                maxQuality = max(maxQuality, currentQuality);
            }
            
            for (const auto& [neighbor, travelTime] : graph[node]) {
                bool firstVisit = !visited[neighbor];
                if (firstVisit) {
                    visited[neighbor] = true;
                    dfs(neighbor, timeSpent + travelTime, currentQuality + values[neighbor]);
                    visited[neighbor] = false;
                } else {
                    dfs(neighbor, timeSpent + travelTime, currentQuality);
                }
            }
        };
        
        visited[0] = true;
        dfs(0, 0, values[0]);
        
        return maxQuality;          
    }
};
