// Source: https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. You have to partition the array into one or more contiguous subarrays.
//
// We call a partition of the array valid if each of the obtained subarrays satisfies one of the following conditions:
//
//
// 	The subarray consists of exactly 2, equal elements. For example, the subarray [2,2] is good.
// 	The subarray consists of exactly 3, equal elements. For example, the subarray [4,4,4] is good.
// 	The subarray consists of exactly 3 consecutive increasing elements, that is, the difference between adjacent elements is 1. For example, the subarray [3,4,5] is good, but the subarray [1,3,5] is not.
//
//
// Return true if the array has at least one valid partition. Otherwise, return false.
//
// Example:
// Input: nums = [4,4,4,5,6]
// Output: true
// Explanation: The array can be partitioned into the subarrays [4,4] and [4,5,6].
// This partition is valid, so we return true.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var validPartition = function(nums) {
    const n = nums.length;
    const dp = new Array(n + 1).fill(false);
    dp[0] = true;

    for (let i = 2; i <= n; i++) {
        if (nums[i - 1] === nums[i - 2] && dp[i - 2]) {
            dp[i] = true;
        } else if (
            i > 2 &&
            nums[i - 1] === nums[i - 2] &&
            nums[i - 2] === nums[i - 3] &&
            dp[i - 3]
        ) {
            dp[i] = true;
        } else if (
            i > 2 &&
            nums[i - 1] === nums[i - 2] + 1 &&
            nums[i - 2] === nums[i - 3] + 1 &&
            dp[i - 3]
        ) {
            dp[i] = true;
        }
    }

    return dp[n];
};