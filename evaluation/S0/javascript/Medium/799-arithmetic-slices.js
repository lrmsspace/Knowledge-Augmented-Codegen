// Source: https://leetcode.com/problems/arithmetic-slices/   |   Difficulty: Medium
//
// Problem Description:
// An integer array is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
//
//
// 	For example, [1,3,5,7,9], [7,7,7,7], and [3,-1,-5,-9] are arithmetic sequences.
//
//
// Given an integer array nums, return the number of arithmetic subarrays of nums.
//
// A subarray is a contiguous subsequence of the array.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 3
// Explanation: We have 3 arithmetic slices in nums: [1, 2, 3], [2, 3, 4] and [1,2,3,4] itself.
//
// Constraints:
// 1 <= nums.length <= 5000
// 	-1000 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var numberOfArithmeticSlices = function(nums) {
    let totalSlices = 0;
    let currentSlices = 0;
    for (let i = 2; i < nums.length; i++) {
        if (nums[i] - nums[i - 1] === nums[i - 1] - nums[i - 2]) {
            currentSlices++;
            totalSlices += currentSlices;
        } else {
            currentSlices = 0;
        }
    }
    return totalSlices;
};