// Source: https://leetcode.com/problems/diagonal-traverse-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D integer array nums, return all elements of nums in diagonal order as shown in the below images.
//
// Example:
// Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,4,2,7,5,3,8,6,9]
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i].length <= 105
// 	1 <= sum(nums[i].length) <= 105
// 	1 <= nums[i][j] <= 105
//

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        map<int, vector<int>> diagonalMap;
        int maxDiagonal = 0;

        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums[i].size(); ++j) {
                diagonalMap[i + j].push_back(nums[i][j]);
                maxDiagonal = max(maxDiagonal, i + j);
            }
        }

        vector<int> result;
        for (int d = 0; d <= maxDiagonal; ++d) {
            auto& diagonal = diagonalMap[d];
            result.insert(result.end(), diagonal.rbegin(), diagonal.rend());
        }

        return result;          
    }
};
