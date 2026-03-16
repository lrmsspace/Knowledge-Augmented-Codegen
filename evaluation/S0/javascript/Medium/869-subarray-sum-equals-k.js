// Source: https://leetcode.com/problems/subarray-sum-equals-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,1,1], k = 2
// Output: 2
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	-1000 <= nums[i] <= 1000
// 	-107 <= k <= 107
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var subarraySum = function(nums, k) {
    const prefixSumCount = new Map();
    prefixSumCount.set(0, 1);
    let currentSum = 0;
    let count = 0;
    for (const num of nums) {
        currentSum += num;
        if (prefixSumCount.has(currentSum - k)) {
            count += prefixSumCount.get(currentSum - k);
        }
        prefixSumCount.set(currentSum, (prefixSumCount.get(currentSum) || 0) + 1);
    }
    return count;
};