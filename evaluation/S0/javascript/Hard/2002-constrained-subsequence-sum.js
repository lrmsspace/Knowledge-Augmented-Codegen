    // Source: https://leetcode.com/problems/constrained-subsequence-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence of that array such that for every two consecutive integers in the subsequence, nums[i] and nums[j], where i < j, the condition j - i <= k is satisfied.
//
// A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.
//
// Example:
// Input: nums = [10,2,-10,5,20], k = 2
// Output: 37
// Explanation: The subsequence is [10, 2, 5, 20].
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	-104 <= nums[i] <= 104
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var constrainedSubsetSum = function(nums, k) {
    const n = nums.length;
    const dp = new Array(n).fill(0);
    dp[0] = nums[0];
    const deque = [0];
    let maxSum = nums[0];
    for (let i = 1; i < n; i++) {
        while (deque.length > 0 && deque[0] < i - k) {
            deque.shift();
        }
        dp[i] = nums[i] + Math.max(0, dp[deque[0]]);
        maxSum = Math.max(maxSum, dp[i]);
        while (deque.length > 0 && dp[i] >= dp[deque[deque.length - 1]]) {
            deque.pop();
        }
        deque.push(i);
    }
    return maxSum;                  
};
