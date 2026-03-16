// Source: https://leetcode.com/problems/number-of-zero-filled-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the number of subarrays filled with 0.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,3,0,0,2,0,0,4]
// Output: 6
// Explanation: 
// There are 4 occurrences of [0] as a subarray.
// There are 2 occurrences of [0,0] as a subarray.
// There is no occurrence of a subarray with a size more than 2 filled with 0. Therefore, we return 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var zeroFilledSubarray = function(nums) {
    let count = 0;
    let zeroCount = 0;
    for (const num of nums) {
        if (num === 0) {
            zeroCount++;
            count += zeroCount;
        } else {
            zeroCount = 0;
        }
    }
    return count;
};