// Source: https://leetcode.com/problems/shortest-path-visiting-all-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You have an undirected, connected graph of n nodes labeled from 0 to n - 1. You are given an array graph where graph[i] is a list of all the nodes connected with node i by an edge.
//
// Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.
//
// Example:
// Input: graph = [[1,2,3],[0],[0],[0]]
// Output: 4
// Explanation: One possible path is [1,0,2,0,3]
//
// Constraints:
// n == graph.length
// 	1 <= n <= 12
// 	0 <= graph[i].length < n
// 	graph[i] does not contain i.
// 	If graph[a] contains b, then graph[b] contains a.
// 	The input graph is always connected.
//

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        int finalState = (1 << n) - 1;
        vector<vector<int>> dist(n, vector<int>(1 << n, INT_MAX));
        queue<pair<int, int>> q; // (node, state)
        
        // Initialize the queue with all nodes as starting points
        for (int i = 0; i < n; i++) {
            dist[i][1 << i] = 0;
            q.push({i, 1 << i});
        }
        
        while (!q.empty()) {
            auto [node, state] = q.front();
            q.pop();
            
            for (int neighbor : graph[node]) {
                int nextState = state | (1 << neighbor);
                if (dist[neighbor][nextState] > dist[node][state] + 1) {
                    dist[neighbor][nextState] = dist[node][state] + 1;
                    q.push({neighbor, nextState});
                }
            }
        }
        
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            ans = min(ans, dist[i][finalState]);
        }
        
        return ans;         
    }
};
