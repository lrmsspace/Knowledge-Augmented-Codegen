// Source: https://leetcode.com/problems/minimum-degree-of-a-connected-trio-in-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph. You are given an integer n which is the number of nodes in the graph and an array edges, where each edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi.
//
// A connected trio is a set of three nodes where there is an edge between every pair of them.
//
// The degree of a connected trio is the number of edges where one endpoint is in the trio, and the other is not.
//
// Return the minimum degree of a connected trio in the graph, or -1 if the graph has no connected trios.
//
// Example:
// Input: n = 6, edges = [[1,2],[1,3],[3,2],[4,1],[5,2],[3,6]]
// Output: 3
// Explanation: There is exactly one trio, which is [1,2,3]. The edges that form its degree are bolded in the figure above.
//
// Constraints:
// 2 <= n <= 400
// 	edges[i].length == 2
// 	1 <= edges.length <= n * (n-1) / 2
// 	1 <= ui, vi <= n
// 	ui != vi
// 	There are no repeated edges.
//

class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<vector<bool>> graph(n + 1, vector<bool>(n + 1, false));
        vector<int> degree(n + 1, 0);
        
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            graph[u][v] = true;
            graph[v][u] = true;
            degree[u]++;
            degree[v]++;
        }
        
        int minDegree = INT_MAX;
        
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (graph[i][j]) {
                    for (int k = j + 1; k <= n; k++) {
                        if (graph[i][k] && graph[j][k]) {
                            int currentDegree = degree[i] + degree[j] + degree[k] - 6;
                            minDegree = min(minDegree, currentDegree);
                        }
                    }
                }
            }
        }
        
        return (minDegree == INT_MAX) ? -1 : minDegree;         
    }
};
