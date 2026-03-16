// Source: https://leetcode.com/problems/subtree-inversion-sum/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0, with n nodes numbered from 0 to n - 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates an edge between nodes ui and vi.
//
// You are also given an integer array nums of length n, where nums[i] represents the value at node i, and an integer k.
//
// You may perform inversion operations on a subset of nodes subject to the following rules:
//
//
// 	
// 	Subtree Inversion Operation:
//
// 	
// 		
// 		When you invert a node, every value in the subtree rooted at that node is multiplied by -1.
// 		
// 	
// 	
// 	
// 	Distance Constraint on Inversions:
//
// 	
// 		
// 		You may only invert a node if it is "sufficiently far" from any other inverted node.
// 		
// 		
// 		Specifically, if you invert two nodes a and b such that one is an ancestor of the other (i.e., if LCA(a, b) = a or LCA(a, b) = b), then the distance (the number of edges on the unique path between them) must be at least k.
// 		
// 	
// 	
//
//
// Return the maximum possible sum of the tree's node values after applying inversion operations.
//
// Example:
// Input: edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], nums = [4,-8,-6,3,7,-2,5], k = 2
//
// Output: 27
//
// Explanation:
//
//
//
//
// 	Apply inversion operations at nodes 0, 3, 4 and 6.
// 	The final nums array is [-4, 8, 6, 3, 7, 2, 5], and the total sum is 27.
//
// Constraints:
// 2 <= n <= 5 * 104
// 	edges.length == n - 1
// 	edges[i] = [ui, vi]
// 	0 <= ui, vi < n
// 	nums.length == n
// 	-5 * 104 <= nums[i] <= 5 * 104
// 	1 <= k <= 50
// 	The input is generated such that edges represents a valid tree.
//

class Solution {
public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> tree(n);
        for (auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }
        
        vector<vector<long long>> dp(n, vector<long long>(k + 1, 0));
        
        function<void(int, int)> dfs = [&](int node, int parent) {
            for (int child : tree[node]) {
                if (child == parent) continue;
                dfs(child, node);
            }
            
            for (int dist = 0; dist <= k; dist++) {
                long long sumNoInvert = nums[node];
                long long sumInvert = -nums[node];
                
                for (int child : tree[node]) {
                    if (child == parent) continue;
                    if (dist + 1 <= k) {
                        sumNoInvert += dp[child][dist + 1];
                    } else {
                        sumNoInvert += max(dp[child][0], dp[child][dist + 1]);
                    }
                    
                    if (k > 1) {
                        sumInvert += dp[child][1];
                    } else {
                        sumInvert += max(dp[child][0], dp[child][1]);
                    }
                }
                
                dp[node][dist] = max(sumNoInvert, sumInvert);
            }
        };
        
        dfs(0, -1);
        
        return dp[0][0];            
    }
};
