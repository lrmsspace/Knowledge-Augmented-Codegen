// Source: https://leetcode.com/problems/count-number-of-pairs-with-absolute-difference-k/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of pairs (i, j) where i < j such that |nums[i] - nums[j]| == k.
//
// The value of |x| is defined as:
//
//
// 	x if x >= 0.
// 	-x if x < 0.
//
// Example:
// Input: nums = [1,2,2,1], k = 1
// Output: 4
// Explanation: The pairs with an absolute difference of 1 are:
// - [1,2,2,1]
// - [1,2,2,1]
// - [1,2,2,1]
// - [1,2,2,1]
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 100
// 	1 <= k <= 99
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var countKDifference = function(nums, k) {
    let count = 0;
    const n = nums.length;
    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            if (Math.abs(nums[i] - nums[j]) === k) {
                count++;
            }
        }
    }
    return count;
};