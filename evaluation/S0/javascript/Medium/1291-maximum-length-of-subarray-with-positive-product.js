// Source: https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums, find the maximum length of a subarray where the product of all its elements is positive.
//
// A subarray of an array is a consecutive sequence of zero or more values taken out of that array.
//
// Return the maximum length of a subarray with positive product.
//
// Example:
// Input: nums = [1,-2,-3,4]
// Output: 4
// Explanation: The array nums already has a positive product of 24.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var getMaxLen = function(nums) {
    let maxLength = 0;
    let positiveLength = 0;
    let negativeLength = 0;
    for (const num of nums) {
        if (num === 0) {
            positiveLength = 0;
            negativeLength = 0;
        } else if (num > 0) {
            positiveLength++;
            negativeLength = negativeLength > 0 ? negativeLength + 1 : 0;
        } else {
            const temp = positiveLength;
            positiveLength = negativeLength > 0 ? negativeLength + 1 : 0;
            negativeLength = temp + 1;
        }
        maxLength = Math.max(maxLength, positiveLength);
    }
    return maxLength;
};