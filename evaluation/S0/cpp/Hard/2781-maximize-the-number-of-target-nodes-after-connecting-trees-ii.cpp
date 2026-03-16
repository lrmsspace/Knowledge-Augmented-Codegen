// Source: https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/   |   Difficulty: Hard
//
// Problem Description:
// There exist two undirected trees with n and m nodes, labeled from [0, n - 1] and [0, m - 1], respectively.
//
// You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.
//
// Node u is target to node v if the number of edges on the path from u to v is even. Note that a node is always target to itself.
//
// Return an array of n integers answer, where answer[i] is the maximum possible number of nodes that are target to node i of the first tree if you had to connect one node from the first tree to another node in the second tree.
//
// Note that queries are independent from each other. That is, for every query you will remove the added edge before proceeding to the next query.
//
// Example:
// Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]
//
// Output: [8,7,7,8,8]
//
// Explanation:
//
//
// 	For i = 0, connect node 0 from the first tree to node 0 from the second tree.
// 	For i = 1, connect node 1 from the first tree to node 4 from the second tree.
// 	For i = 2, connect node 2 from the first tree to node 7 from the second tree.
// 	For i = 3, connect node 3 from the first tree to node 0 from the second tree.
// 	For i = 4, connect node 4 from the first tree to node 4 from the second tree.
//
// Constraints:
// 2 <= n, m <= 105
// 	edges1.length == n - 1
// 	edges2.length == m - 1
// 	edges1[i].length == edges2[i].length == 2
// 	edges1[i] = [ai, bi]
// 	0 <= ai, bi < n
// 	edges2[i] = [ui, vi]
// 	0 <= ui, vi < m
// 	The input is generated such that edges1 and edges2 represent valid trees.
//

class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;
        
        vector<vector<int>> graph1(n);
        vector<vector<int>> graph2(m);
        
        for (const auto& edge : edges1) {
            graph1[edge[0]].push_back(edge[1]);
            graph1[edge[1]].push_back(edge[0]);
        }
        
        for (const auto& edge : edges2) {
            graph2[edge[0]].push_back(edge[1]);
            graph2[edge[1]].push_back(edge[0]);
        }
        
        vector<int> depth1(n, -1);
        vector<int> depth2(m, -1);
        
        function<void(int, int, vector<vector<int>>&, vector<int>&)> dfs = [&](int node, int d, vector<vector<int>>& graph, vector<int>& depth) {
            depth[node] = d;
            for (int neighbor : graph[node]) {
                if (depth[neighbor] == -1) {
                    dfs(neighbor, d + 1, graph, depth);
                }
            }
        };
        
        dfs(0, 0, graph1, depth1);
        dfs(0, 0, graph2, depth2);
        
        int evenCount2 = 0, oddCount2 = 0;
        for (int d : depth2) {
            if (d % 2 == 0) {
                evenCount2++;
            } else {
                oddCount2++;
            }
        }
        
        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            if (depth1[i] % 2 == 0) {
                result[i] = evenCount2 + 1;  // +1 for the node itself
            } else {
                result[i] = oddCount2 + 1;   // +1 for the node itself
            }
        }
        
        return result;          
    }
};
