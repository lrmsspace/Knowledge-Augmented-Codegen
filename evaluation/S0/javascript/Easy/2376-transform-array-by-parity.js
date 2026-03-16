// Source: https://leetcode.com/problems/transform-array-by-parity/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums. Transform nums by performing the following operations in the exact order specified:
//
//
// 	Replace each even number with 0.
// 	Replace each odd numbers with 1.
// 	Sort the modified array in non-decreasing order.
//
//
// Return the resulting array after performing these operations.
//
// Example:
// Input: nums = [4,3,2,1]
//
// Output: [0,0,1,1]
//
// Explanation:
//
//
// 	Replace the even numbers (4 and 2) with 0 and the odd numbers (3 and 1) with 1. Now, nums = [0, 1, 0, 1].
// 	After sorting nums in non-descending order, nums = [0, 0, 1, 1].
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @return {number[]}
 */
var transformArray = function(nums) {
    const transformed = nums.map(num => (num % 2 === 0 ? 0 : 1));
    transformed.sort((a, b) => a - b);
    return transformed; 
};
