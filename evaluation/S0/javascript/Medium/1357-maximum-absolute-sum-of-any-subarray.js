// Source: https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).
//
// Return the maximum absolute sum of any (possibly empty) subarray of nums.
//
// Note that abs(x) is defined as follows:
//
//
// 	If x is a negative integer, then abs(x) = -x.
// 	If x is a non-negative integer, then abs(x) = x.
//
// Example:
// Input: nums = [1,-3,2,3,-4]
// Output: 5
// Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxAbsoluteSum = function(nums) {
    let maxEndingHere = 0;
    let minEndingHere = 0;
    let maxAbsoluteSum = 0;
    for (const num of nums) {
        maxEndingHere = Math.max(num, maxEndingHere + num);
        minEndingHere = Math.min(num, minEndingHere + num);
        maxAbsoluteSum = Math.max(maxAbsoluteSum, Math.abs(maxEndingHere), Math.abs(minEndingHere));
    }
    return maxAbsoluteSum;
};