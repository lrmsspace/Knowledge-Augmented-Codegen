// Source: https://leetcode.com/problems/contiguous-array/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
//
// Example:
// Input: nums = [0,1]
// Output: 2
// Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var findMaxLength = function(nums) {
    const countMap = new Map();
    countMap.set(0, -1);
    let maxLength = 0;
    let count = 0;
    for (let i = 0; i < nums.length; i++) {
        count += nums[i] === 1 ? 1 : -1;
        if (countMap.has(count)) {
            maxLength = Math.max(maxLength, i - countMap.get(count));
        } else {
            countMap.set(count, i);
        }
    }
    return maxLength;
};  