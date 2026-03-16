// Source: https://leetcode.com/problems/longest-special-path/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1, represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi with length lengthi. You are also given an integer array nums, where nums[i] represents the value at node i.
//
// A special path is defined as a downward path from an ancestor node to a descendant node such that all the values of the nodes in that path are unique.
//
// Note that a path may start and end at the same node.
//
// Return an array result of size 2, where result[0] is the length of the longest special path, and result[1] is the minimum number of nodes in all possible longest special paths.
//
// Example:
// Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], nums = [2,1,2,1,3,1]
//
// Output: [6,2]
//
// Explanation:
//
// In the image below, nodes are colored by their corresponding values in nums
//
//
//
// The longest special paths are 2 -> 5 and 0 -> 1 -> 4, both having a length of 6. The minimum number of nodes across all longest special paths is 2.
//
// Constraints:
// 2 <= n <= 5 * 104
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ui, vi < n
// 	1 <= lengthi <= 103
// 	nums.length == n
// 	0 <= nums[i] <= 5 * 104
// 	The input is generated such that edges represents a valid tree.
//

class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], length = edge[2];
            graph[u].emplace_back(v, length);
            graph[v].emplace_back(u, length);
        }
        
        vector<int> result(2, 0); // {max_length, min_nodes}
        
        function<tuple<int, int>> dfs = [&](int node, int parent, unordered_set<int>& seen) {
            seen.insert(nums[node]);
            int max_len = 0;
            int min_nodes = 1;
            
            for (const auto& [neighbor, length] : graph[node]) {
                if (neighbor == parent) continue;
                
                if (seen.count(nums[neighbor]) == 0) {
                    auto [child_len, child_nodes] = dfs(neighbor, node, seen);
                    child_len += length;
                    
                    if (child_len > max_len) {
                        max_len = child_len;
                        min_nodes = child_nodes + 1;
                    } else if (child_len == max_len) {
                        min_nodes = min(min_nodes, child_nodes + 1);
                    }
                }
            }
            
            seen.erase(nums[node]);
            
            // Update global result
            if (max_len > result[0]) {
                result[0] = max_len;
                result[1] = min_nodes;
            } else if (max_len == result[0]) {
                result[1] = min(result[1], min_nodes);
            }
            
            return make_tuple(max_len, min_nodes);
        };
        
        unordered_set<int> seen;
        dfs(0, -1, seen);
        
        return result;          
    }
};
