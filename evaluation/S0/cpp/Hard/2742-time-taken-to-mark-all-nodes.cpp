// Source: https://leetcode.com/problems/time-taken-to-mark-all-nodes/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.
//
// Initially, all nodes are unmarked. For each node i:
//
//
// 	If i is odd, the node will get marked at time x if there is at least one node adjacent to it which was marked at time x - 1.
// 	If i is even, the node will get marked at time x if there is at least one node adjacent to it which was marked at time x - 2.
//
//
// Return an array times where times[i] is the time when all nodes get marked in the tree, if you mark node i at time t = 0.
//
// Note that the answer for each times[i] is independent, i.e. when you mark node i all other nodes are unmarked.
//
// Example:
// Input: edges = [[0,1],[0,2]]
//
// Output: [2,4,3]
//
// Explanation:
//
//
//
//
// 	For i = 0:
//
// 	
// 		Node 1 is marked at t = 1, and Node 2 at t = 2.
// 	
// 	
// 	For i = 1:
// 	
// 		Node 0 is marked at t = 2, and Node 2 at t = 4.
// 	
// 	
// 	For i = 2:
// 	
// 		Node 0 is marked at t = 2, and Node 1 at t = 3.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= edges[i][0], edges[i][1] <= n - 1
// 	The input is generated such that edges represents a valid tree.
//

class Solution {
public:
    vector<int> timeTaken(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        vector<int> result(n, 0);
        
        function<void(int, int, int, vector<int>&)> dfs = [&](int node, int parent, int time, vector<int>& times) {
            times[node] = time;
            for (int neighbor : graph[node]) {
                if (neighbor != parent) {
                    int nextTime = (node % 2 == 0) ? time + 2 : time + 1;
                    dfs(neighbor, node, nextTime, times);
                }
            }
        };
        
        for (int i = 0; i < n; i++) {
            vector<int> times(n, 0);
            dfs(i, -1, 0, times);
            result[i] = *max_element(times.begin(), times.end());
        }
        
        return result;          
    }
};
