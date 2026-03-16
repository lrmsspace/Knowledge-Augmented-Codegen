// Source: https://leetcode.com/problems/find-if-path-exists-in-graph/   |   Difficulty: Easy
//
// Problem Description:
// There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1 (inclusive). The edges in the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.
//
// You want to determine if there is a valid path that exists from vertex source to vertex destination.
//
// Given edges and the integers n, source, and destination, return true if there is a valid path from source to destination, or false otherwise.
//
// Example:
// Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
// Output: true
// Explanation: There are two paths from vertex 0 to vertex 2:
// - 0 → 1 → 2
// - 0 → 2
//
// Constraints:
// 1 <= n <= 2 * 105
// 	0 <= edges.length <= 2 * 105
// 	edges[i].length == 2
// 	0 <= ui, vi <= n - 1
// 	ui != vi
// 	0 <= source, destination <= n - 1
// 	There are no duplicate edges.
// 	There are no self edges.
//

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<bool> visited(n, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            if (node == destination) {
                return true;
            }

            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return false;           
    }
};
