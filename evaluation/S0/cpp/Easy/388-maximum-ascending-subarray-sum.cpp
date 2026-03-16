// Source: https://leetcode.com/problems/maximum-ascending-subarray-sum/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of positive integers nums, return the maximum possible sum of an strictly increasing subarray in nums.
//
// A subarray is defined as a contiguous sequence of numbers in an array.
//
// Example:
// Input: nums = [10,20,30,5,10,50]
// Output: 65
// Explanation: [5,10,50] is the ascending subarray with the maximum sum of 65.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//

class Solution {
public:
    int maxAscendingSum(vector<int>& nums) {
        int maxSum = nums[0];
        int currentSum = nums[0];

        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i - 1]) {
                currentSum += nums[i];
            } else {
                currentSum = nums[i];
            }
            maxSum = max(maxSum, currentSum);
        }

        return maxSum;          
    }
};
