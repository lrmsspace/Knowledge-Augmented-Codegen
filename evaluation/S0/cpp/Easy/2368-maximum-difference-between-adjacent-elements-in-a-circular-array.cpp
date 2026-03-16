// Source: https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/   |   Difficulty: Easy
//
// Problem Description:
// Given a circular array nums, find the maximum absolute difference between adjacent elements.
//
// Note: In a circular array, the first and last elements are adjacent.
//
// Example:
// Input: nums = [1,2,4]
//
// Output: 3
//
// Explanation:
//
// Because nums is circular, nums[0] and nums[2] are adjacent. They have the maximum absolute difference of |4 - 1| = 3.
//
// Constraints:
// 2 <= nums.length <= 100
// 	-100 <= nums[i] <= 100
//

class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int n = nums.size();
        int maxDiff = abs(nums[0] - nums[n - 1]);

        for (int i = 1; i < n; ++i) {
            maxDiff = max(maxDiff, abs(nums[i] - nums[i - 1]));
        }

        return maxDiff;         
    }
};
