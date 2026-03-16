// Source: https://leetcode.com/problems/largest-sum-of-averages/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k. You can partition the array into at most k non-empty adjacent subarrays. The score of a partition is the sum of the averages of each subarray.
//
// Note that the partition must use every integer in nums, and that the score is not necessarily an integer.
//
// Return the maximum score you can achieve of all the possible partitions. Answers within 10-6 of the actual answer will be accepted.
//
// Example:
// Input: nums = [9,1,2,3,9], k = 3
// Output: 20.00000
// Explanation: 
// The best choice is to partition nums into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
// We could have also partitioned nums into [9, 1], [2], [3, 9], for example.
// That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 104
// 	1 <= k <= nums.length
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var largestSumOfAverages = function(nums, k) {
    const n = nums.length;
    const prefixSums = new Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        prefixSums[i + 1] = prefixSums[i] + nums[i];
    }

    const dp = new Array(n + 1).fill(0).map(() => new Array(k + 1).fill(0));
    for (let i = 1; i <= n; i++) {
        dp[i][1] = prefixSums[i] / i;
    }

    for (let j = 2; j <= k; j++) {
        for (let i = j; i <= n; i++) {
            for (let m = j - 1; m < i; m++) {
                dp[i][j] = Math.max(dp[i][j], dp[m][j - 1] + (prefixSums[i] - prefixSums[m]) / (i - m));
            }
        }
    }

    return dp[n][k];
};