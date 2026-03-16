// Source: https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k. Your task is to partition nums into one or more non-empty contiguous segments such that in each segment, the difference between its maximum and minimum elements is at most k.
//
// Return the total number of ways to partition nums under this condition.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [9,4,1,3,7], k = 4
//
// Output: 6
//
// Explanation:
//
// There are 6 valid partitions where the difference between the maximum and minimum elements in each segment is at most k = 4:
//
//
// 	[[9], [4], [1], [3], [7]]
// 	[[9], [4], [1], [3, 7]]
// 	[[9], [4], [1, 3], [7]]
// 	[[9], [4, 1], [3], [7]]
// 	[[9], [4, 1], [3, 7]]
// 	[[9], [4, 1, 3], [7]]
//
// Constraints:
// 2 <= nums.length <= 5 * 104
// 	1 <= nums[i] <= 109
// 	0 <= k <= 109
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var countPartitions = function(nums, k) {
    const mod = 1e9 + 7;
    const n = nums.length;
    const dp = Array(n + 1).fill(0);
    dp[0] = 1; 
    let minDeque = [];
    let maxDeque = [];
    let left = 0;
    for (let right = 0; right < n; right++) {
        while (minDeque.length && nums[minDeque[minDeque.length - 1]] >= nums[right]) {
            minDeque.pop();
        }
        minDeque.push(right);
        while (maxDeque.length && nums[maxDeque[maxDeque.length - 1]] <= nums[right]) {
            maxDeque.pop();
        }
        maxDeque.push(right);
        while (nums[maxDeque[0]] - nums[minDeque[0]] > k) {
            if (minDeque[0] === left) {
                minDeque.shift();
            }
            if (maxDeque[0] === left) {
                maxDeque.shift();
            }
            left++;
        }
        dp[right + 1] = (dp[right + 1] + dp[left]) % mod;
    }
    let result = 0;
    for (let i = 1; i <= n; i++) {
        result = (result + dp[i]) % mod;
    }
    return result;
};