// Source: https://leetcode.com/problems/largest-perimeter-triangle/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return the largest perimeter of a triangle with a non-zero area, formed from three of these lengths. If it is impossible to form any triangle of a non-zero area, return 0.
//
// Example:
// Input: nums = [2,1,2]
// Output: 5
// Explanation: You can form a triangle with three side lengths: 1, 2, and 2.
//
// Constraints:
// 3 <= nums.length <= 104
// 	1 <= nums[i] <= 106
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var largestPerimeter = function(nums) {
    nums.sort((a, b) => b - a);
    for (let i = 0; i < nums.length - 2; i++) {
        if (nums[i] < nums[i + 1] + nums[i + 2]) {
            return nums[i] + nums[i + 1] + nums[i + 2];
        }
    }
    return 0;
};
