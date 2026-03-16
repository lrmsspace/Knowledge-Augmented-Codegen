// Source: https://leetcode.com/problems/maximum-score-of-a-node-sequence/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph with n nodes, numbered from 0 to n - 1.
//
// You are given a 0-indexed integer array scores of length n where scores[i] denotes the score of node i. You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// A node sequence is valid if it meets the following conditions:
//
//
// 	There is an edge connecting every pair of adjacent nodes in the sequence.
// 	No node appears more than once in the sequence.
//
//
// The score of a node sequence is defined as the sum of the scores of the nodes in the sequence.
//
// Return the maximum score of a valid node sequence with a length of 4. If no such sequence exists, return -1.
//
// Example:
// Input: scores = [5,2,9,8,4], edges = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
// Output: 24
// Explanation: The figure above shows the graph and the chosen node sequence [0,1,2,3].
// The score of the node sequence is 5 + 2 + 9 + 8 = 24.
// It can be shown that no other node sequence has a score of more than 24.
// Note that the sequences [3,1,2,0] and [1,0,2,3] are also valid and have a score of 24.
// The sequence [0,3,2,4] is not valid since no edge connects nodes 0 and 3.
//
// Constraints:
// n == scores.length
// 	4 <= n <= 5 * 104
// 	1 <= scores[i] <= 108
// 	0 <= edges.length <= 5 * 104
// 	edges[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no duplicate edges.
//

class Solution {
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        int n = scores.size();
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        // For each node, keep top 3 neighbors with highest scores
        vector<vector<int>> topNeighbors(n);
        for (int i = 0; i < n; i++) {
            sort(graph[i].begin(), graph[i].end(), [&](int a, int b) {
                return scores[a] > scores[b];
            });
            for (int j = 0; j < min(3, (int)graph[i].size()); j++) {
                topNeighbors[i].push_back(graph[i][j]);
            }
        }
        
        int maxScore = -1;
        
        // Try every edge as the middle edge of the sequence
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            
            for (int a : topNeighbors[u]) {
                if (a == v) continue;
                for (int b : topNeighbors[v]) {
                    if (b == u || b == a) continue;
                    int currentScore = scores[a] + scores[u] + scores[v] + scores[b];
                    maxScore = max(maxScore, currentScore);
                }
            }
        }
        
        return maxScore;            
    }
};
