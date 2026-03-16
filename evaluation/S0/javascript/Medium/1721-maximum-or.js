// Source: https://leetcode.com/problems/maximum-or/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n and an integer k. In an operation, you can choose an element and multiply it by 2.
//
// Return the maximum possible value of nums[0] | nums[1] | ... | nums[n - 1] that can be obtained after applying the operation on nums at most k times.
//
// Note that a | b denotes the bitwise or between two integers a and b.
//
// Example:
// Input: nums = [12,9], k = 1
// Output: 30
// Explanation: If we apply the operation to index 1, our new array nums will be equal to [12,18]. Thus, we return the bitwise or of 12 and 18, which is 30.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 15
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maximumOr = function(nums, k) {
    const n = nums.length;
    let baseOr = 0;
    for (let num of nums) {
        baseOr |= num;
    }
    let maxOr = baseOr;
    for (let i = 0; i < n; i++) {
        const newNum = nums[i] * (1 << k);
        const currentOr = baseOr | newNum;
        maxOr = Math.max(maxOr, currentOr);
    }
    return maxOr;
        
};
