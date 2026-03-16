// Source: https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, find three non-overlapping subarrays of length k with maximum sum and return them.
//
// Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.
//
// Example:
// Input: nums = [1,2,1,2,6,7,5,1], k = 2
// Output: [0,3,5]
// Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
// We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] < 216
// 	1 <= k <= floor(nums.length / 3)
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
var maxSumOfThreeSubarrays = function(nums, k) {
    


    let n = nums.length;
    let sum = new Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + nums[i];
    }

    let left = new Array(n).fill(0);
    let maxLeft = 0;
    for (let i = k - 1; i < n; i++) {
        let currentSum = sum[i + 1] - sum[i + 1 - k];
        if (currentSum > sum[maxLeft + k] - sum[maxLeft]) {
            maxLeft = i + 1 - k;
        }
        left[i] = maxLeft;
    }

    let right = new Array(n).fill(0);
    let maxRight = n - k;
    for (let i = n - k; i >= 0; i--) {
        let currentSum = sum[i + k] - sum[i];
        if (currentSum >= sum[maxRight + k] - sum[maxRight]) {
            maxRight = i;
        }
        right[i] = maxRight;
    }

    let maxTotal = 0;
    
};
