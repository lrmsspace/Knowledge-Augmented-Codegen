// Source: https://leetcode.com/problems/find-all-good-indices/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of size n and a positive integer k.
//
// We call an index i in the range k <= i < n - k good if the following conditions are satisfied:
//
//
// 	The k elements that are just before the index i are in non-increasing order.
// 	The k elements that are just after the index i are in non-decreasing order.
//
//
// Return an array of all good indices sorted in increasing order.
//
// Example:
// Input: nums = [2,1,1,1,3,4,1], k = 2
// Output: [2,3]
// Explanation: There are two good indices in the array:
// - Index 2. The subarray [2,1] is in non-increasing order, and the subarray [1,3] is in non-decreasing order.
// - Index 3. The subarray [1,1] is in non-increasing order, and the subarray [3,4] is in non-decreasing order.
// Note that the index 4 is not good because [4,1] is not non-decreasing.
//
// Constraints:
// n == nums.length
// 	3 <= n <= 105
// 	1 <= nums[i] <= 106
// 	1 <= k <= n / 2
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
var goodIndices = function(nums, k) {
    const n = nums.length;
    const nonIncreasing = new Array(n).fill(1);
    const nonDecreasing = new Array(n).fill(1);
    const result = [];

    for (let i = 1; i < n; i++) {
        if (nums[i] <= nums[i - 1]) {
            nonIncreasing[i] = nonIncreasing[i - 1] + 1;
        }
    }

    for (let i = n - 2; i >= 0; i--) {
        if (nums[i] <= nums[i + 1]) {
            nonDecreasing[i] = nonDecreasing[i + 1] + 1;
        }
    }

    for (let i = k; i < n - k; i++) {
        if (nonIncreasing[i - 1] >= k && nonDecreasing[i + 1] >= k) {
            result.push(i);
        }
    }

    return result;
};