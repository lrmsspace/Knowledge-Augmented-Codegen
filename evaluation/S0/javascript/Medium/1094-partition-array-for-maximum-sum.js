// Source: https://leetcode.com/problems/partition-array-for-maximum-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr, partition the array into (contiguous) subarrays of length at most k. After partitioning, each subarray has their values changed to become the maximum value of that subarray.
//
// Return the largest sum of the given array after partitioning. Test cases are generated so that the answer fits in a 32-bit integer.
//
// Example:
// Input: arr = [1,15,7,9,2,5,10], k = 3
// Output: 84
// Explanation: arr becomes [15,15,15,9,10,10,10]
//
// Constraints:
// 1 <= arr.length <= 500
// 	0 <= arr[i] <= 109
// 	1 <= k <= arr.length
//

/**
 * @param {number[]} arr
 * @param {number} k
 * @return {number}
 */
var maxSumAfterPartitioning = function(arr, k) {
    const n = arr.length;
    const dp = new Array(n + 1).fill(0);
    for (let i = 1; i <= n; i++) {
        let maxInPartition = 0;
        for (let j = 1; j <= Math.min(k, i); j++) {
            maxInPartition = Math.max(maxInPartition, arr[i - j]);
            dp[i] = Math.max(dp[i], dp[i - j] + maxInPartition * j);
        }
    }
    return dp[n];
        
};
