// Source: https://leetcode.com/problems/longest-special-path-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0, with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi with length lengthi. You are also given an integer array nums, where nums[i] represents the value at node i.
//
// A special path is defined as a downward path from an ancestor node to a descendant node in which all node values are distinct, except for at most one value that may appear twice.
//
// Return an array result of size 2, where result[0] is the length of the longest special path, and result[1] is the minimum number of nodes in all possible longest special paths.
//
// Example:
// Input: edges = [[0,1,1],[1,2,3],[1,3,1],[2,4,6],[4,7,2],[3,5,2],[3,6,5],[6,8,3]], nums = [1,1,0,3,1,2,1,1,0]
//
// Output: [9,3]
//
// Explanation:
//
// In the image below, nodes are colored by their corresponding values in nums.
//
//
//
// The longest special paths are 1 -> 2 -> 4 and 1 -> 3 -> 6 -> 8, both having a length of 9. The minimum number of nodes across all longest special paths is 3.
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
        
        vector<int> result(2, 0); // result[0]: max length, result[1]: min nodes
        unordered_map<int, int> count;
        
        function<pair<int, int>(int, int)> dfs = [&](int node, int parent) {
            count[nums[node]]++;
            vector<pair<int, int>> candidates; // (length, nodes)
            candidates.emplace_back(0, 1); // path of length 0 with 1 node
            
            for (const auto& [neighbor, length] : graph[node]) {
                if (neighbor == parent) continue;
                auto [childLength, childNodes] = dfs(neighbor, node);
                if (childLength > 0 || count[nums[neighbor]] < 2) {
                    candidates.emplace_back(childLength + length, childNodes);
                }
            }
            
            sort(candidates.rbegin(), candidates.rend());
            
            // Update result with the best candidate
            if (candidates[0].first > result[0]) {
                result[0] = candidates[0].first;
                result[1] = candidates[0].second;
            } else if (candidates[0].first == result[0]) {
                result[1] = min(result[1], candidates[0].second);
            }
            
            // Check combinations of two best candidates
            if (candidates.size() > 1) {
                int combinedLength = candidates[0].first + candidates[1].first;
                int combinedNodes = candidates[0].second + candidates[1].second - 1; // subtract 1 for current node
                if (combinedLength > result[0]) {
                    result[0] = combinedLength;
                    result[1] = combinedNodes;
                } else if (combinedLength == result[0]) {
                    result[1] = min(result[1], combinedNodes);
                }
            }
            
            count[nums[node]]--;
            return candidates[0];
        };
        
        dfs(0, -1);         
        return result;
    }
};
