// Source: https://leetcode.com/problems/number-of-great-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums consisting of positive integers and an integer k.
//
// Partition the array into two ordered groups such that each element is in exactly one group. A partition is called great if the sum of elements of each group is greater than or equal to k.
//
// Return the number of distinct great partitions. Since the answer may be too large, return it modulo 109 + 7.
//
// Two partitions are considered distinct if some element nums[i] is in different groups in the two partitions.
//
// Example:
// Input: nums = [1,2,3,4], k = 4
// Output: 6
// Explanation: The great partitions are: ([1,2,3], [4]), ([1,3], [2,4]), ([1,4], [2,3]), ([2,3], [1,4]), ([2,4], [1,3]) and ([4], [1,2,3]).
//
// Constraints:
// 1 <= nums.length, k <= 1000
// 	1 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var countPartitions = function(nums, k) {
    const mod = 1e9 + 7;
    const totalSum = nums.reduce((a, b) => a + b, 0);
    if (totalSum < 2 * k) {
        return 0;
    }
    const n = nums.length;
    const dp = new Array(k).fill(0);
    dp[0] = 1;
    for (const num of nums) {
        for (let j = k - 1; j >= num; j--) {
            dp[j] = (dp[j] + dp[j - num]) % mod;
        }
    }
    let count = 0;
    for (let j = 0; j < k; j++) {
        count = (count + dp[j]) % mod;
    }
    return (2 * ((1 << n) - count) % mod) % mod;
};
