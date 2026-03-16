// Source: https://leetcode.com/problems/max-number-of-k-sum-pairs/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// In one operation, you can pick two numbers from the array whose sum equals k and remove them from the array.
//
// Return the maximum number of operations you can perform on the array.
//
// Example:
// Input: nums = [1,2,3,4], k = 5
// Output: 2
// Explanation: Starting with nums = [1,2,3,4]:
// - Remove numbers 1 and 4, then nums = [2,3]
// - Remove numbers 2 and 3, then nums = []
// There are no more pairs that sum up to 5, hence a total of 2 operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 109
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maxOperations = function(nums, k) {
    const numCounts = new Map();
    let operations = 0;
    for (const num of nums) {
        const complement = k - num;
        if (numCounts.get(complement) > 0) {
            operations++;
            numCounts.set(complement, numCounts.get(complement) - 1);
        } else {
            numCounts.set(num, (numCounts.get(num) || 0) + 1);
        }
    }
    return operations;
};