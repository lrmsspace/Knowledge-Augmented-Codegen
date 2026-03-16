// Source: https://leetcode.com/problems/ways-to-split-array-into-good-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array nums.
//
// A subarray of an array is good if it contains exactly one element with the value 1.
//
// Return an integer denoting the number of ways to split the array nums into good subarrays. As the number may be too large, return it modulo 109 + 7.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [0,1,0,0,1]
// Output: 3
// Explanation: There are 3 ways to split nums into good subarrays:
// - [0,1] [0,0,1]
// - [0,1,0] [0,1]
// - [0,1,0,0] [1]
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 1
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var numberOfGoodSubarraySplits = function(nums) {
    const mod = 1e9 + 7;
    let result = 1;
    let i = 0;
    const n = nums.length;
    while (i < n && nums[i] === 0) {
        i++;
    }
    if (i === n) {
        return 0;
    }
    while (i < n) {
        let count = 0;
        while (i < n && nums[i] === 0) {
            count++;
            i++;
        }
        if (i < n) {
            result = (result * (count + 1)) % mod;
            i++;
        }
    }
    return result;
};