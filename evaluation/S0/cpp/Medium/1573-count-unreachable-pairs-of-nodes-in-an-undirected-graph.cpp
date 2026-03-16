// Source: https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. There is an undirected graph with n nodes, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// Return the number of pairs of different nodes that are unreachable from each other.
//
// Example:
// Input: n = 3, edges = [[0,1],[0,2],[1,2]]
// Output: 0
// Explanation: There are no pairs of nodes that are unreachable from each other. Therefore, we return 0.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= edges.length <= 2 * 105
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	There are no repeated edges.
//

class Solution {
public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<bool> visited(n, false);
        long long result = 0;
        long long remainingNodes = n;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                long long componentSize = dfs(i, graph, visited);
                result += componentSize * (remainingNodes - componentSize);
                remainingNodes -= componentSize;
            }
        }

        return result;          
    }
};
