// Source: https://leetcode.com/problems/find-the-maximum-length-of-a-good-subsequence-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a non-negative integer k. A sequence of integers seq is called good if there are at most k indices i in the range [0, seq.length - 2] such that seq[i] != seq[i + 1].
//
// Return the maximum possible length of a good subsequence of nums.
//
// Example:
// Input: nums = [1,2,1,1,3], k = 2
//
// Output: 4
//
// Explanation:
//
// The maximum length subsequence is [1,2,1,1,3].
//
// Constraints:
// 1 <= nums.length <= 5 * 103
// 	1 <= nums[i] <= 109
// 	0 <= k <= min(50, nums.length)
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maximumLength = function(nums, k) {
    const n = nums.length;
    const dp = new Array(n).fill(0).map(() => new Array(k + 1).fill(0));
    for (let i = 0; i < n; i++) {
        dp[i][0] = 1;
        for (let j = 1; j <= k; j++) {
            for (let m = 0; m < i; m++) {
                if (nums[i] === nums[m]) {
                    dp[i][j] = Math.max(dp[i][j], dp[m][j]);
                } else {
                    dp[i][j] = Math.max(dp[i][j], dp[m][j - 1] + 1);
                }
            }
        }    }
    let result = 0;
    for (let i = 0; i < n; i++) {
        for (let j = 0; j <= k; j++) {
            result = Math.max(result, dp[i][j]);
        }
    }
    return result;  
};
