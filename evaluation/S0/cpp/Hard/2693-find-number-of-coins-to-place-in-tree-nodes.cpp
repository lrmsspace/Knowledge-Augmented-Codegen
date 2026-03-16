// Source: https://leetcode.com/problems/find-number-of-coins-to-place-in-tree-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// You are also given a 0-indexed integer array cost of length n, where cost[i] is the cost assigned to the ith node.
//
// You need to place some coins on every node of the tree. The number of coins to be placed at node i can be calculated as:
//
//
// 	If size of the subtree of node i is less than 3, place 1 coin.
// 	Otherwise, place an amount of coins equal to the maximum product of cost values assigned to 3 distinct nodes in the subtree of node i. If this product is negative, place 0 coins.
//
//
// Return an array coin of size n such that coin[i] is the number of coins placed at node i.
//
// Example:
// Input: edges = [[0,1],[0,2],[0,3],[0,4],[0,5]], cost = [1,2,3,4,5,6]
// Output: [120,1,1,1,1,1]
// Explanation: For node 0 place 6 * 5 * 4 = 120 coins. All other nodes are leaves with subtree of size 1, place 1 coin on each of them.
//
// Constraints:
// 2 <= n <= 2 * 104
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	cost.length == n
// 	1 <= |cost[i]| <= 104
// 	The input is generated such that edges represents a valid tree.
//

class Solution {
public:
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        int n = cost.size();
        vector<vector<int>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        vector<long long> result(n, 0);
        
        function<tuple<int, vector<int>>(int, int)> dfs = [&](int node, int parent) {
            vector<int> costs;
            int size = 1;
            
            for (int neighbor : graph[node]) {
                if (neighbor == parent) continue;
                auto [subtreeSize, subCosts] = dfs(neighbor, node);
                size += subtreeSize;
                costs.insert(costs.end(), subCosts.begin(), subCosts.end());
            }
            
            costs.push_back(cost[node]);
            
            if (size < 3) {
                result[node] = 1;
            } else {
                sort(costs.begin(), costs.end(), greater<int>());
                long long prod1 = (long long)costs[0] * costs[1] * costs[2];
                long long prod2 = (long long)costs[costs.size() - 1] * costs[costs.size() - 2] * costs[0];
                result[node] = max(0LL, max(prod1, prod2));
            }
            
            return make_tuple(size, costs);
        };
        
        dfs(0, -1);
        return result;          
    }
};
