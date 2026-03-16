// Source: https://leetcode.com/problems/move-zeroes/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
//
// Note that you must do this in-place without making a copy of the array.
//
// Example:
// Input: nums = [0,1,0,3,12]
// Output: [1,3,12,0,0]
//
// Constraints:
// 1 <= nums.length <= 104
// 	-231 <= nums[i] <= 231 - 1
//
//
//  
// Follow up: Could you minimize the total number of operations done?
//

/**
 * @param {number[]} nums
 * @return {void} Do not return anything, modify nums in-place instead.
 */
var moveZeroes = function(nums) {
    let lastNonZeroIndex = 0;

    // Move all non-zero elements to the front of the array
    for (let i = 0; i < nums.length; i++) {
        if (nums[i] !== 0) {
            nums[lastNonZeroIndex] = nums[i];
            lastNonZeroIndex++;
        }
    }
    // Fill the remaining positions with zeros
    for (let i = lastNonZeroIndex; i < nums.length; i++) {
        nums[i] = 0;
    }
    
};
