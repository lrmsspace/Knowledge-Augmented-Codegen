// Source: https://leetcode.com/problems/shortest-path-with-alternating-colors/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n, the number of nodes in a directed graph where the nodes are labeled from 0 to n - 1. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.
//
// You are given two arrays redEdges and blueEdges where:
//
//
// 	redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the graph, and
// 	blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the graph.
//
//
// Return an array answer of length n, where each answer[x] is the length of the shortest path from node 0 to node x such that the edge colors alternate along the path, or -1 if such a path does not exist.
//
// Example:
// Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
// Output: [0,1,-1]
//
// Constraints:
// 1 <= n <= 100
// 	0 <= redEdges.length, blueEdges.length <= 400
// 	redEdges[i].length == blueEdges[j].length == 2
// 	0 <= ai, bi, uj, vj < n
//

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : redEdges) {
            graph[edge[0]].emplace_back(edge[1], 0); // 0 for red
        }
        for (const auto& edge : blueEdges) {
            graph[edge[0]].emplace_back(edge[1], 1); // 1 for blue
        }

        vector<int> result(n, -1);
        queue<tuple<int, int, int>> q; // node, color, distance
        q.emplace(0, -1, 0); // start from node 0 with no color
        vector<vector<bool>> visited(n, vector<bool>(2, false));
        visited[0][0] = visited[0][1] = true;

        while (!q.empty()) {
            auto [node, color, dist] = q.front();
            q.pop();

            if (result[node] == -1) {
                result[node] = dist;
            }

            for (const auto& [neighbor, edgeColor] : graph[node]) {
                if (edgeColor != color && !visited[neighbor][edgeColor]) {
                    visited[neighbor][edgeColor] = true;
                    q.emplace(neighbor, edgeColor, dist + 1);
                }
            }
        }

        return result;          
    }
};
