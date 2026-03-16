// Source: https://leetcode.com/problems/count-the-number-of-complete-components/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. There is an undirected graph with n vertices, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting vertices ai and bi.
//
// Return the number of complete connected components of the graph.
//
// A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
//
// A connected component is said to be complete if there exists an edge between every pair of its vertices.
//
// Example:
// Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
// Output: 3
// Explanation: From the picture above, one can see that all of the components of this graph are complete.
//
// Constraints:
// 1 <= n <= 50
// 	0 <= edges.length <= n * (n - 1) / 2
// 	edges[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no repeated edges.
//

class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<bool> visited(n, false);
        int completeComponents = 0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                vector<int> component;
                dfs(i, graph, visited, component);

                int size = component.size();
                int edgeCount = 0;
                for (int node : component) {
                    edgeCount += graph[node].size();
                }
                edgeCount /= 2; // Each edge is counted twice

                if (edgeCount == size * (size - 1) / 2) {
                    completeComponents++;
                }
            }
        }

        return completeComponents;          
    }
};
