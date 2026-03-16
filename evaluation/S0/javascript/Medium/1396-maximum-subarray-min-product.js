// Source: https://leetcode.com/problems/maximum-subarray-min-product/   |   Difficulty: Medium
//
// Problem Description:
// The min-product of an array is equal to the minimum value in the array multiplied by the array's sum.
//
//
// 	For example, the array [3,2,5] (minimum value is 2) has a min-product of 2 * (3+2+5) = 2 * 10 = 20.
//
//
// Given an array of integers nums, return the maximum min-product of any non-empty subarray of nums. Since the answer may be large, return it modulo 109 + 7.
//
// Note that the min-product should be maximized before performing the modulo operation. Testcases are generated such that the maximum min-product without modulo will fit in a 64-bit signed integer.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1,2,3,2]
// Output: 14
// Explanation: The maximum min-product is achieved with the subarray [2,3,2] (minimum value is 2).
// 2 * (2+3+2) = 2 * 7 = 14.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 107
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxSumMinProduct = function(nums) {
    const MOD = 1e9 + 7;
    const n = nums.length;
    const prefixSum = new Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    const stack = [];
    let maxProduct = 0;

    for (let i = 0; i <= n; i++) {
        const current = i === n ? 0 : nums[i];
        while (stack.length && nums[stack[stack.length - 1]] > current) {
            const minIndex = stack.pop();
            const leftIndex = stack.length ? stack[stack.length - 1] : -1;
            const subarraySum = prefixSum[i] - prefixSum[leftIndex + 1];
            maxProduct = Math.max(maxProduct, nums[minIndex] * subarraySum);
        }
        stack.push(i);
    }

    return maxProduct % MOD;
};