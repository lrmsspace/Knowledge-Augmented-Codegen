// Source: https://leetcode.com/problems/partition-equal-subset-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.
//
// Example:
// Input: nums = [1,5,11,5]
// Output: true
// Explanation: The array can be partitioned as [1, 5, 5] and [11].
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 100
//

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var canPartition = function(nums) {
    const totalSum = nums.reduce((acc, num) => acc + num, 0);
    if (totalSum % 2 !== 0) return false;
    const target = totalSum / 2;
    const dp = new Array(target + 1).fill(false);
    dp[0] = true;

    for (const num of nums) {
        for (let j = target; j >= num; j--) {
            dp[j] = dp[j] || dp[j - num];
        }
    }

    return dp[target];
};