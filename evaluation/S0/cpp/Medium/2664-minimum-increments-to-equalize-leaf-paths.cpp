// Source: https://leetcode.com/problems/minimum-increments-to-equalize-leaf-paths/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n and an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi] indicates an edge from node ui to vi .
//
// Each node i has an associated cost given by cost[i], representing the cost to traverse that node.
//
// The score of a path is defined as the sum of the costs of all nodes along the path.
//
// Your goal is to make the scores of all root-to-leaf paths equal by increasing the cost of any number of nodes by any non-negative amount.
//
// Return the minimum number of nodes whose cost must be increased to make all root-to-leaf path scores equal.
//
// Example:
// Input: n = 3, edges = [[0,1],[0,2]], cost = [2,1,3]
//
// Output: 1
//
// Explanation:
//
//
//
// There are two root-to-leaf paths:
//
//
// 	Path 0 → 1 has a score of 2 + 1 = 3.
// 	Path 0 → 2 has a score of 2 + 3 = 5.
//
//
// To make all root-to-leaf path scores equal to 5, increase the cost of node 1 by 2.
// Only one node is increased, so the output is 1.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi]
// 	0 <= ui, vi < n
// 	cost.length == n
// 	1 <= cost[i] <= 109
// 	The input is generated such that edges represents a valid tree.
//

class Solution {
public:
    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
        vector<vector<int>> tree(n);
        for (const auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }

        function<pair<long long, int>(int, int)> dfs = [&](int node, int parent) {
            if (tree[node].size() == 1 && tree[node][0] == parent) {
                return make_pair((long long)cost[node], 0);
            }

            long long maxPathSum = 0;
            int increments = 0;

            for (int neighbor : tree[node]) {
                if (neighbor == parent) continue;
                auto [childPathSum, childIncrements] = dfs(neighbor, node);
                maxPathSum = max(maxPathSum, childPathSum);
                increments += childIncrements;
            }

            for (int neighbor : tree[node]) {
                if (neighbor == parent) continue;
                auto [childPathSum, _] = dfs(neighbor, node);
                if (childPathSum < maxPathSum) {
                    increments++;
                }
            }

            return make_pair(maxPathSum + cost[node], increments);
        };

        return dfs(0, -1).second;           
    }
};
