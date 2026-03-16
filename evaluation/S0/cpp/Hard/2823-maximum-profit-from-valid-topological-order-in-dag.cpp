// Source: https://leetcode.com/problems/maximum-profit-from-valid-topological-order-in-dag/   |   Difficulty: Hard
//
// Problem Description:
// You are given a Directed Acyclic Graph (DAG) with n nodes labeled from 0 to n - 1, represented by a 2D array edges, where edges[i] = [ui, vi] indicates a directed edge from node ui to vi. Each node has an associated score given in an array score, where score[i] represents the score of node i.
//
// You must process the nodes in a valid topological order. Each node is assigned a 1-based position in the processing order.
//
// The profit is calculated by summing up the product of each node's score and its position in the ordering.
//
// Return the maximum possible profit achievable with an optimal topological order.
//
// A topological order of a DAG is a linear ordering of its nodes such that for every directed edge u → v, node u comes before v in the ordering.
//
// Example:
// Input: n = 2, edges = [[0,1]], score = [2,3]
//
// Output: 8
//
// Explanation:
//
//
//
// Node 1 depends on node 0, so a valid order is [0, 1].
//
//
// 	
// 		
// 			Node
// 			Processing Order
// 			Score
// 			Multiplier
// 			Profit Calculation
// 		
// 	
// 	
// 		
// 			0
// 			1st
// 			2
// 			1
// 			2 × 1 = 2
// 		
// 		
// 			1
// 			2nd
// 			3
// 			2
// 			3 × 2 = 6
// 		
// 	
//
//
// The maximum total profit achievable over all valid topological orders is 2 + 6 = 8.
//
// Constraints:
// 1 <= n == score.length <= 22
// 	1 <= score[i] <= 105
// 	0 <= edges.length <= n * (n - 1) / 2
// 	edges[i] == [ui, vi] denotes a directed edge from ui to vi.
// 	0 <= ui, vi < n
// 	ui != vi
// 	The input graph is guaranteed to be a DAG.
// 	There are no duplicate edges.
//

class Solution {
public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        vector<int> inDegree(n, 0);
        vector<vector<int>> graph(n);
        
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            inDegree[v]++;
        }
        
        // Topological Sort using Kahn's Algorithm
        priority_queue<pair<int, int>> pq; // max-heap based on score
        
        for (int i = 0; i < n; ++i) {
            if (inDegree[i] == 0) {
                pq.push({score[i], i});
            }
        }
        
        int position = n;
        long long totalProfit = 0;
        
        while (!pq.empty()) {
            auto [currScore, node] = pq.top();
            pq.pop();
            
            totalProfit += (long long)currScore * position;
            position--;
            
            for (int neighbor : graph[node]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    pq.push({score[neighbor], neighbor});
                }
            }
        }
        
        return totalProfit;         
    }
};
