// Source: https://leetcode.com/problems/frog-position-after-t-seconds/   |   Difficulty: Hard
//
// Problem Description:
// Given an undirected tree consisting of n vertices numbered from 1 to n. A frog starts jumping from vertex 1. In one second, the frog jumps from its current vertex to another unvisited vertex if they are directly connected. The frog can not jump back to a visited vertex. In case the frog can jump to several vertices, it jumps randomly to one of them with the same probability. Otherwise, when the frog can not jump to any unvisited vertex, it jumps forever on the same vertex.
//
// The edges of the undirected tree are given in the array edges, where edges[i] = [ai, bi] means that exists an edge connecting the vertices ai and bi.
//
// Return the probability that after t seconds the frog is on the vertex target. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: n = 7, edges = [[1,2],[1,3],[1,7],[2,4],[2,6],[3,5]], t = 2, target = 4
// Output: 0.16666666666666666 
// Explanation: The figure above shows the given graph. The frog starts at vertex 1, jumping with 1/3 probability to the vertex 2 after second 1 and then jumping with 1/2 probability to vertex 4 after second 2. Thus the probability for the frog is on the vertex 4 after 2 seconds is 1/3 * 1/2 = 1/6 = 0.16666666666666666.
//
// Constraints:
// 1 <= n <= 100
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	1 <= t <= 50
// 	1 <= target <= n
//

class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        vector<vector<int>> graph(n + 1);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> visited(n + 1, false);
        double result = 0.0;
        
        function<void(int, int, double)> dfs = [&](int node, int time, double prob) {
            visited[node] = true;
            
            if (time == t) {
                if (node == target) {
                    result += prob;
                }
                visited[node] = false;
                return;
            }
            
            int unvisitedCount = 0;
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    unvisitedCount++;
                }
            }
            
            if (unvisitedCount == 0) {
                if (node == target) {
                    result += prob;
                }
                visited[node] = false;
                return;
            }
            
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    dfs(neighbor, time + 1, prob / unvisitedCount);
                }
            }
            
            visited[node] = false;
        };
        
        dfs(1, 0, 1.0);
        
        return result;          
    }
};
