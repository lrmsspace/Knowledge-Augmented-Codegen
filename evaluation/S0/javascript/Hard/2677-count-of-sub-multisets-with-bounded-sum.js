// Source: https://leetcode.com/problems/count-of-sub-multisets-with-bounded-sum/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array nums of non-negative integers, and two integers l and r.
//
// Return the count of sub-multisets within nums where the sum of elements in each subset falls within the inclusive range of [l, r].
//
// Since the answer may be large, return it modulo 109 + 7.
//
// A sub-multiset is an unordered collection of elements of the array in which a given value x can occur 0, 1, ..., occ[x] times, where occ[x] is the number of occurrences of x in the array.
//
// Note that:
//
//
// 	Two sub-multisets are the same if sorting both sub-multisets results in identical multisets.
// 	The sum of an empty multiset is 0.
//
// Example:
// Input: nums = [1,2,2,3], l = 6, r = 6
// Output: 1
// Explanation: The only subset of nums that has a sum of 6 is {1, 2, 3}.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	0 <= nums[i] <= 2 * 104
// 	Sum of nums does not exceed 2 * 104.
// 	0 <= l <= r <= 2 * 104
//

/**
 * @param {number[]} nums
 * @param {number} l
 * @param {number} r
 * @return {number}
 */
var countSubMultisets = function(nums, l, r) {
    const mod = 1e9 + 7;
    const maxSum = nums.reduce((a, b) => a + b, 0);
    const dp = Array(maxSum + 1).fill(0);
    dp[0] = 1;
    for (const num of nums) {
        for (let sum = maxSum; sum >= num; sum--) {
            dp[sum] = (dp[sum] + dp[sum - num]) % mod;
        }
    }
    let count = 0;
    for (let sum = l; sum <= r; sum++) {
        count = (count + dp[sum]) % mod;
    }
    return count;
};
