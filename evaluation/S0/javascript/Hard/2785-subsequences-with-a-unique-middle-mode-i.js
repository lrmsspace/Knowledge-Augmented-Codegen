// Source: https://leetcode.com/problems/subsequences-with-a-unique-middle-mode-i/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, find the number of subsequences of size 5 of nums with a unique middle mode.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// A mode of a sequence of numbers is defined as the element that appears the maximum number of times in the sequence.
//
// A sequence of numbers contains a unique mode if it has only one mode.
//
// A sequence of numbers seq of size 5 contains a unique middle mode if the middle element (seq[2]) is a unique mode.
//
// Example:
// Input: nums = [1,1,1,1,1,1]
//
// Output: 6
//
// Explanation:
//
// [1, 1, 1, 1, 1] is the only subsequence of size 5 that can be formed, and it has a unique middle mode of 1. This subsequence can be formed in 6 different ways, so the output is 6.
//
// Constraints:
// 5 <= nums.length <= 1000
//  -109 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var subsequencesWithMiddleMode = function(nums) {
    const MOD = 1e9 + 7;
    const n = nums.length;
    let result = 0;
    for (let mid = 2; mid <= n - 3; mid++) {
        const leftCount = new Map();
        const rightCount = new Map();
        for (let i = 0; i < mid; i++) {
            leftCount.set(nums[i], (leftCount.get(nums[i]) || 0) + 1);
        }
        for (let i = mid + 1; i < n; i++) {
            rightCount.set(nums[i], (rightCount.get(nums[i]) || 0) + 1);
        }
        for (const [num, count] of leftCount) {
            if (num === nums[mid]) continue;
            const leftWays = count;
            const rightWays = rightCount.get(num) || 0;
            result = (result + leftWays * rightWays) % MOD;
        }
    }
    return result;
};
