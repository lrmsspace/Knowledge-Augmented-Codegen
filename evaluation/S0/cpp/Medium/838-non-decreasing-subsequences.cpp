// Source: https://leetcode.com/problems/non-decreasing-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements. You may return the answer in any order.
//
// Example:
// Input: nums = [4,6,7,7]
// Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
//
// Constraints:
// 1 <= nums.length <= 15
// 	-100 <= nums[i] <= 100
//

class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(nums, 0, current, result);
        return result;          
    }
};
