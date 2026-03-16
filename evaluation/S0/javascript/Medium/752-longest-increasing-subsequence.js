// Source: https://leetcode.com/problems/longest-increasing-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the length of the longest strictly increasing subsequence.
//
// Example:
// Input: nums = [10,9,2,5,3,7,101,18]
// Output: 4
// Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
//
// Constraints:
// 1 <= nums.length <= 2500
// 	-104 <= nums[i] <= 104
//
//
//  
// Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var lengthOfLIS = function(nums) {
    const dp = new Array(nums.length).fill(1);
    for (let i = 1; i < nums.length; i++) {
        for (let j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = Math.max(dp[i], dp[j] + 1);
            }
        }
    }
    return Math.max(...dp);
};
