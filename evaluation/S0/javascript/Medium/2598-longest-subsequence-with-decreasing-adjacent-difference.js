// Source: https://leetcode.com/problems/longest-subsequence-with-decreasing-adjacent-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums.
//
// Your task is to find the length of the longest subsequence seq of nums, such that the absolute differences between consecutive elements form a non-increasing sequence of integers. In other words, for a subsequence seq0, seq1, seq2, ..., seqm of nums, |seq1 - seq0| >= |seq2 - seq1| >= ... >= |seqm - seqm - 1|.
//
// Return the length of such a subsequence.
//
// Example:
// Input: nums = [16,6,3]
//
// Output: 3
//
// Explanation: 
//
// The longest subsequence is [16, 6, 3] with the absolute adjacent differences [10, 3].
//
// Constraints:
// 2 <= nums.length <= 104
// 	1 <= nums[i] <= 300
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var longestSubsequence = function(nums) {
    const n = nums.length;
    const dp = Array(n).fill(1);
    for (let i = 1; i < n; i++) {
        for (let j = 0; j < i; j++) {
            if (Math.abs(nums[i] - nums[j]) <= Math.abs(nums[j] - nums[j - 1] || 0)) {
                dp[i] = Math.max(dp[i], dp[j] + 1);
            }
        }
    }
    return Math.max(...dp); 
};
