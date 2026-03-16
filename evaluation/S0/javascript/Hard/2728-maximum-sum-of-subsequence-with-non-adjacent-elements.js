// Source: https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums consisting of integers. You are also given a 2D array queries, where queries[i] = [posi, xi].
//
// For query i, we first set nums[posi] equal to xi, then we calculate the answer to query i which is the maximum sum of a subsequence of nums where no two adjacent elements are selected.
//
// Return the sum of the answers to all queries.
//
// Since the final answer may be very large, return it modulo 109 + 7.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [3,5,9], queries = [[1,-2],[0,-3]]
//
// Output: 21
//
// Explanation:
// After the 1st query, nums = [3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 3 + 9 = 12.
// After the 2nd query, nums = [-3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 9.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-105 <= nums[i] <= 105
// 	1 <= queries.length <= 5 * 104
// 	queries[i] == [posi, xi]
// 	0 <= posi <= nums.length - 1
// 	-105 <= xi <= 105
//

/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @return {number}
 */
var maximumSumSubsequence = function(nums, queries) {
    const mod = 1e9 + 7;
    const n = nums.length;
    const m = queries.length;
    const dp = new Array(n).fill(0);
    dp[0] = Math.max(0, nums[0]);
    for (let i = 1; i < n; i++) {
        dp[i] = Math.max(dp[i - 1], (i > 1 ? dp[i - 2] : 0) + nums[i]);
    }
    let result = 0;
    for (let i = 0; i < m; i++) {
        const [pos, x] = queries[i];
        const oldVal = nums[pos];
        nums[pos] = x;
        if (pos === 0) {
            dp[0] = Math.max(0, nums[0]);
        }
        for (let j = Math.max(1, pos); j < n; j++) {
            dp[j] = Math.max(dp[j - 1], (j > 1 ? dp[j - 2] : 0) + nums[j]);
        }
        result = (result + dp[n - 1]) % mod;
    }
    return result;
};
