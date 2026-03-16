// Source: https://leetcode.com/problems/maximum-product-of-three-numbers/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, find three numbers whose product is maximum and return the maximum product.
//
// Example:
// Input: nums = [1,2,3]
// Output: 6
//
// Constraints:
// 3 <= nums.length <= 104
// 	-1000 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maximumProduct = function(nums) {
    nums.sort((a, b) => a - b);
    const n = nums.length;
    const product1 = nums[n - 1] * nums[n - 2] * nums[n - 3];
    const product2 = nums[0] * nums[1] * nums[n - 1];
    return Math.max(product1, product2);            
};
