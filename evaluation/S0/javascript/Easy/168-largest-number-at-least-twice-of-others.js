// Source: https://leetcode.com/problems/largest-number-at-least-twice-of-others/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums where the largest integer is unique.
//
// Determine whether the largest element in the array is at least twice as much as every other number in the array. If it is, return the index of the largest element, or return -1 otherwise.
//
// Example:
// Input: nums = [3,6,1,0]
// Output: 1
// Explanation: 6 is the largest integer.
// For every other number in the array x, 6 is at least twice as big as x.
// The index of value 6 is 1, so we return 1.
//
// Constraints:
// 2 <= nums.length <= 50
// 	0 <= nums[i] <= 100
// 	The largest element in nums is unique.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var dominantIndex = function(nums) {
    let maxIndex = 0;
    for (let i = 1; i < nums.length; i++) {
        if (nums[i] > nums[maxIndex]) {
            maxIndex = i;
        }
    }
    for (let i = 0; i < nums.length; i++) {
        if (i !== maxIndex && nums[maxIndex] < 2 * nums[i]) {
            return -1;
        }
    }
    return maxIndex;
};
