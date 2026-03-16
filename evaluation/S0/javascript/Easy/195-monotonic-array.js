// Source: https://leetcode.com/problems/monotonic-array/   |   Difficulty: Easy
//
// Problem Description:
// An array is monotonic if it is either monotone increasing or monotone decreasing.
//
// An array nums is monotone increasing if for all i <= j, nums[i] <= nums[j]. An array nums is monotone decreasing if for all i <= j, nums[i] >= nums[j].
//
// Given an integer array nums, return true if the given array is monotonic, or false otherwise.
//
// Example:
// Input: nums = [1,2,2,3]
// Output: true
//
// Constraints:
// 1 <= nums.length <= 105
// 	-105 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var isMonotonic = function(nums) {
    let increasing = true;
    let decreasing = true;
    for (let i = 1; i < nums.length; i++) {
        if (nums[i] > nums[i - 1]) {
            decreasing = false;
        }
        if (nums[i] < nums[i - 1]) {
            increasing = false;
        }
    }
    return increasing || decreasing;
};