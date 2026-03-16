// Source: https://leetcode.com/problems/longest-arithmetic-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.
//
// Note that:
//
//
// 	A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
// 	A sequence seq is arithmetic if seq[i + 1] - seq[i] are all the same value (for 0 <= i < seq.length - 1).
//
// Example:
// Input: nums = [3,6,9,12]
// Output: 4
// Explanation:  The whole array is an arithmetic sequence with steps of length = 3.
//
// Constraints:
// 2 <= nums.length <= 1000
// 	0 <= nums[i] <= 500
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var longestArithSeqLength = function(nums) {
    
    const n = nums.length;
    const dp = new Array(n).fill(0).map(() => new Map());
    let maxLength = 2; // Minimum length of arithmetic subsequence is 2

    for (let i = 1; i < n; i++) {
        for (let j = 0; j < i; j++) {
            const diff = nums[i] - nums[j];
            const prevLength = dp[j].get(diff) || 1;
            const currLength = prevLength + 1;
            dp[i].set(diff, currLength);
            maxLength = Math.max(maxLength, currLength);
        }
    }
    return maxLength;
    
};
