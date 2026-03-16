// Source: https://leetcode.com/problems/partition-to-k-equal-sum-subsets/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return true if it is possible to divide this array into k non-empty subsets whose sums are all equal.
//
// Example:
// Input: nums = [4,3,2,3,5,2,1], k = 4
// Output: true
// Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
//
// Constraints:
// 1 <= k <= nums.length <= 16
// 	1 <= nums[i] <= 104
// 	The frequency of each element is in the range [1, 4].
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {boolean}
 */
var canPartitionKSubsets = function(nums, k) {
    const totalSum = nums.reduce((a, b) => a + b, 0);
    if (totalSum % k !== 0) return false;
    const target = totalSum / k;
    nums.sort((a, b) => b - a);
    const subsets = new Array(k).fill(0);

    const backtrack = (index) => {
        if (index === nums.length) {
            return true;
        }
        for (let i = 0; i < k; i++) {
            if (subsets[i] + nums[index] <= target) {
                subsets[i] += nums[index];
                if (backtrack(index + 1)) {
                    return true;
                }
                subsets[i] -= nums[index];
            }
            if (subsets[i] === 0) break;
        }
        return false;
    };

    return backtrack(0);
};