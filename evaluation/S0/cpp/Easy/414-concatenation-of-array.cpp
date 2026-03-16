// Source: https://leetcode.com/problems/concatenation-of-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums of length n, you want to create an array ans of length 2n where ans[i] == nums[i] and ans[i + n] == nums[i] for 0 <= i < n (0-indexed).
//
// Specifically, ans is the concatenation of two nums arrays.
//
// Return the array ans.
//
// Example:
// Input: nums = [1,2,1]
// Output: [1,2,1,1,2,1]
// Explanation: The array ans is formed as follows:
// - ans = [nums[0],nums[1],nums[2],nums[0],nums[1],nums[2]]
// - ans = [1,2,1,1,2,1]
//
// Constraints:
// n == nums.length
// 	1 <= n <= 1000
// 	1 <= nums[i] <= 1000
//

class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        vector<int> ans;
        ans.reserve(nums.size() * 2);
        ans.insert(ans.end(), nums.begin(), nums.end());
        ans.insert(ans.end(), nums.begin(), nums.end());
        return ans;         
    }
};
