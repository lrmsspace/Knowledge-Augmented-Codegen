// Source: https://leetcode.com/problems/maximum-product-of-three-numbers/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, find three numbers whose product is maximum and return the maximum product.
//
// Example:
// Input: nums = [1,2,3]
// Output: 6
//
// Constraints:
// 3 <= nums.length <= 104
// 	-1000 <= nums[i] <= 1000
//

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        return max(nums[0] * nums[1] * nums[n - 1], nums[n - 1] * nums[n - 2] * nums[n - 3]);           
    }
};
