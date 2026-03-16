// Source: https://leetcode.com/problems/remove-one-element-to-make-the-array-strictly-increasing/   |   Difficulty: Easy
//
// Problem Description:
// Given a 0-indexed integer array nums, return true if it can be made strictly increasing after removing exactly one element, or false otherwise. If the array is already strictly increasing, return true.
//
// The array nums is strictly increasing if nums[i - 1] < nums[i] for each index (1 <= i < nums.length).
//
// Example:
// Input: nums = [1,2,10,5,7]
// Output: true
// Explanation: By removing 10 at index 2 from nums, it becomes [1,2,5,7].
// [1,2,5,7] is strictly increasing, so return true.
//
// Constraints:
// 2 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var canBeIncreasing = function(nums) {
    const isStrictlyIncreasing = (arr) => {
        for (let i = 1; i < arr.length; i++) {
            if (arr[i] <= arr[i - 1]) {
                return false;
            }
        }
        return true;
    };
    for (let i = 0; i < nums.length; i++) {
        const newArr = nums.slice(0, i).concat(nums.slice(i + 1));
        if (isStrictlyIncreasing(newArr)) {
            return true;
        }
    }
    return false;
};
