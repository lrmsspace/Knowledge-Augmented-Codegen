// Source: https://leetcode.com/problems/number-of-squareful-arrays/   |   Difficulty: Hard
//
// Problem Description:
// An array is squareful if the sum of every pair of adjacent elements is a perfect square.
//
// Given an integer array nums, return the number of permutations of nums that are squareful.
//
// Two permutations perm1 and perm2 are different if there is some index i such that perm1[i] != perm2[i].
//
// Example:
// Input: nums = [1,17,8]
// Output: 2
// Explanation: [1,8,17] and [17,8,1] are the valid permutations.
//
// Constraints:
// 1 <= nums.length <= 12
// 	0 <= nums[i] <= 109
//

class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        // Build graph based on squareful condition
        vector<vector<int>> graph(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    int sum = nums[i] + nums[j];
                    int root = (int)sqrt(sum);
                    if (root * root == sum) {
                        graph[i].push_back(j);
                    }
                }
            }
        }
        
        vector<bool> visited(n, false);
        int result = 0;
        
        function<void(int, int)> dfs = [&](int node, int depth) {
            if (depth == n) {
                result++;
                return;
            }
            
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    dfs(neighbor, depth + 1);
                    visited[neighbor] = false;
                }
            }
        };
        
        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicates
            visited[i] = true;
            dfs(i, 1);
            visited[i] = false;
        }
        
        return result;          
    }
};
