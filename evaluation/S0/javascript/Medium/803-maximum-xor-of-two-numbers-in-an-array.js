// Source: https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 <= i <= j < n.
//
// Example:
// Input: nums = [3,10,5,25,2,8]
// Output: 28
// Explanation: The maximum result is 5 XOR 25 = 28.
//
// Constraints:
// 1 <= nums.length <= 2 * 105
// 	0 <= nums[i] <= 231 - 1
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var findMaximumXOR = function(nums) {
    let maxXOR = 0;
    let mask = 0;
    for (let i = 31; i >= 0; i--) {
        mask = mask | (1 << i);
        const prefixes = new Set();
        for (const num of nums) {
            prefixes.add(num & mask);
        }
        const temp = maxXOR | (1 << i);
        for (const prefix of prefixes) {
            if (prefixes.has(prefix ^ temp)) {
                maxXOR = temp;
                break;
            }
        }
    }
    return maxXOR;
};