// Source: https://leetcode.com/problems/permutations-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.
//
// Example:
// Input: nums = [1,1,2]
// Output:
// [[1,1,2],
//  [1,2,1],
//  [2,1,1]]
//
// Constraints:
// 1 <= nums.length <= 8
// 	-10 <= nums[i] <= 10
//

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        sort(nums.begin(), nums.end());
        backtrack(nums, used, current, result);
        return result;          
    }
};
