// Source: https://leetcode.com/problems/single-number/   |   Difficulty: Easy
//
// Problem Description:
// Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
//
// You must implement a solution with a linear runtime complexity and use only constant extra space.
//
// Example:
// Input: nums = [2,2,1]
//
// Output: 1
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	-3 * 104 <= nums[i] <= 3 * 104
// 	Each element in the array appears twice except for one element which appears only once.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var singleNumber = function(nums) {
    let result = 0;
    for (let num of nums) {
        result ^= num;
    }
    return result;
};
