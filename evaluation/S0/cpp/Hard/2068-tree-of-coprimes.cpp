// Source: https://leetcode.com/problems/tree-of-coprimes/   |   Difficulty: Hard
//
// Problem Description:
// There is a tree (i.e., a connected, undirected graph that has no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges. Each node has a value associated with it, and the root of the tree is node 0.
//
// To represent this tree, you are given an integer array nums and a 2D array edges. Each nums[i] represents the ith node's value, and each edges[j] = [uj, vj] represents an edge between nodes uj and vj in the tree.
//
// Two values x and y are coprime if gcd(x, y) == 1 where gcd(x, y) is the greatest common divisor of x and y.
//
// An ancestor of a node i is any other node on the shortest path from node i to the root. A node is not considered an ancestor of itself.
//
// Return an array ans of size n, where ans[i] is the closest ancestor to node i such that nums[i] and nums[ans[i]] are coprime, or -1 if there is no such ancestor.
//
// Example:
// Input: nums = [2,3,3,2], edges = [[0,1],[1,2],[1,3]]
// Output: [-1,0,0,1]
// Explanation: In the above figure, each node's value is in parentheses.
// - Node 0 has no coprime ancestors.
// - Node 1 has only one ancestor, node 0. Their values are coprime (gcd(2,3) == 1).
// - Node 2 has two ancestors, nodes 1 and 0. Node 1's value is not coprime (gcd(3,3) == 3), but node 0's
//   value is (gcd(2,3) == 1), so node 0 is the closest valid ancestor.
// - Node 3 has two ancestors, nodes 1 and 0. It is coprime with node 1 (gcd(3,2) == 1), so node 1 is its
//   closest valid ancestor.
//
// Constraints:
// nums.length == n
// 	1 <= nums[i] <= 50
// 	1 <= n <= 105
// 	edges.length == n - 1
// 	edges[j].length == 2
// 	0 <= uj, vj < n
// 	uj != vj
//

class Solution {
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        vector<vector<int>> coprimeWith(51);
        for (int i = 1; i <= 50; ++i) {
            for (int j = 1; j <= 50; ++j) {
                if (__gcd(i, j) == 1) {
                    coprimeWith[i].push_back(j);
                }
            }
        }
        
        vector<int> result(n, -1);
        vector<int> lastSeen(51, -1);
        vector<int> depth(51, -1);
        
        function<void(int, int, int)> dfs = [&](int node, int parent, int d) {
            int val = nums[node];
            int closestAncestor = -1;
            int maxDepth = -1;
            
            for (int cp : coprimeWith[val]) {
                if (lastSeen[cp] != -1 && depth[cp] > maxDepth) {
                    maxDepth = depth[cp];
                    closestAncestor = lastSeen[cp];
                }
            }
            
            result[node] = closestAncestor;
            
            int prevLastSeen = lastSeen[val];
            int prevDepth = depth[val];
            lastSeen[val] = node;
            depth[val] = d;
            
            for (int neighbor : graph[node]) {
                if (neighbor != parent) {
                    dfs(neighbor, node, d + 1);
                }
            }
            
            lastSeen[val] = prevLastSeen;
            depth[val] = prevDepth;
        };
        
        dfs(0, -1, 0);
        
        return result;          
    }
};
