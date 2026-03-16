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

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxAdjacentDistance = function(nums) {
    let maxDiff = 0;
    const n = nums.length;
    for (let i = 0; i < n; i++) {
        const diff = Math.abs(nums[i] - nums[(i + 1) % n]);
        maxDiff = Math.max(maxDiff, diff);
    }
    return maxDiff;
};
