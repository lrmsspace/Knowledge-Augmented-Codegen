// Source: https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/   |   Difficulty: Medium
//
// Problem Description:
// There is an integer array nums that consists of n unique elements, but you have forgotten it. However, you do remember every pair of adjacent elements in nums.
//
// You are given a 2D integer array adjacentPairs of size n - 1 where each adjacentPairs[i] = [ui, vi] indicates that the elements ui and vi are adjacent in nums.
//
// It is guaranteed that every adjacent pair of elements nums[i] and nums[i+1] will exist in adjacentPairs, either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]]. The pairs can appear in any order.
//
// Return the original array nums. If there are multiple solutions, return any of them.
//
// Example:
// Input: adjacentPairs = [[2,1],[3,4],[3,2]]
// Output: [1,2,3,4]
// Explanation: This array has all its adjacent pairs in adjacentPairs.
// Notice that adjacentPairs[i] may not be in left-to-right order.
//
// Constraints:
// nums.length == n
// 	adjacentPairs.length == n - 1
// 	adjacentPairs[i].length == 2
// 	2 <= n <= 105
// 	-105 <= nums[i], ui, vi <= 105
// 	There exists some nums that has adjacentPairs as its pairs.
//

class Solution {
public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        unordered_map<int, vector<int>> graph;
        for (const auto& pair : adjacentPairs) {
            graph[pair[0]].push_back(pair[1]);
            graph[pair[1]].push_back(pair[0]);
        }

        // Find one of the endpoints (a node with only one neighbor)
        int start = 0;
        for (const auto& entry : graph) {
            if (entry.second.size() == 1) {
                start = entry.first;
                break;
            }
        }

        vector<int> result;
        unordered_set<int> visited;
        int current = start;
        int prev = INT_MIN; // Use INT_MIN as a sentinel value

        while (true) {
            result.push_back(current);
            visited.insert(current);

            const auto& neighbors = graph[current];
            int next = INT_MIN;
            for (int neighbor : neighbors) {
                if (neighbor != prev) {
                    next = neighbor;
                    break;
                }
            }

            if (next == INT_MIN) {
                break; // No unvisited neighbors left
            }

            prev = current;
            current = next;
        }

        return result;          
    }
};
