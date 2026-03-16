// Source: https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of integers nums. Return the length of the longest subarray of nums which is either strictly increasing or strictly decreasing.
//
// Example:
// Input: nums = [1,4,3,3,2]
//
// Output: 2
//
// Explanation:
//
// The strictly increasing subarrays of nums are [1], [2], [3], [3], [4], and [1,4].
//
// The strictly decreasing subarrays of nums are [1], [2], [3], [3], [4], [3,2], and [4,3].
//
// Hence, we return 2.
//
// Constraints:
// 1 <= nums.length <= 50
// 	1 <= nums[i] <= 50
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var longestMonotonicSubarray = function(nums) {
    let maxLength = 1;
    let currentIncLength = 1;
    let currentDecLength = 1;
    for (let i = 1; i < nums.length; i++) {
        if (nums[i] > nums[i - 1]) {
            currentIncLength++;
            currentDecLength = 1;
        } else if (nums[i] < nums[i - 1]) {
            currentDecLength++;
            currentIncLength = 1;
        } else {
            currentIncLength = 1;
            currentDecLength = 1;
        }
        maxLength = Math.max(maxLength, currentIncLength, currentDecLength);
    }
    return maxLength;
};