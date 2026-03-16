// Source: https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// A split of an integer array is good if:
//
//
// 	The array is split into three non-empty contiguous subarrays - named left, mid, right respectively from left to right.
// 	The sum of the elements in left is less than or equal to the sum of the elements in mid, and the sum of the elements in mid is less than or equal to the sum of the elements in right.
//
//
// Given nums, an array of non-negative integers, return the number of good ways to split nums. As the number may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,1,1]
// Output: 1
// Explanation: The only good way to split nums is [1] [1] [1].
//
// Constraints:
// 3 <= nums.length <= 105
// 	0 <= nums[i] <= 104
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var waysToSplit = function(nums) {
    const MOD = 1e9 + 7;
    const n = nums.length;
    const prefixSums = Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        prefixSums[i + 1] = prefixSums[i] + nums[i];
    }
    let ways = 0;
    for (let i = 1, j = 1, k = 1; i < n - 1; i++) {
        while (j <= i || (j < n && prefixSums[j + 1] - prefixSums[i] < prefixSums[i])) {
            j++;
        }
        while (k <= j || (k < n && prefixSums[k + 1] - prefixSums[i] <= prefixSums[n] - prefixSums[k + 1])) {
            k++;
        }
        ways = (ways + Math.max(0, k - j)) % MOD;
    }
    return ways;
};