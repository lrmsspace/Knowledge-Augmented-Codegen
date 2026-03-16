// Source: https://leetcode.com/problems/maximum-product-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, find a subarray that has the largest product, and return the product.
//
// The test cases are generated so that the answer will fit in a 32-bit integer.
//
// Example:
// Input: nums = [2,3,-2,4]
// Output: 6
// Explanation: [2,3] has the largest product 6.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	-10 <= nums[i] <= 10
// 	The product of any subarray of nums is guaranteed to fit in a 32-bit integer.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxProduct = function(nums) {
    let maxProd = nums[0];
    let minProd = nums[0];
    let result = nums[0];

    for (let i = 1; i < nums.length; i++) {
        if (nums[i] < 0) {
            [maxProd, minProd] = [minProd, maxProd];
        }

        maxProd = Math.max(nums[i], maxProd * nums[i]);
        minProd = Math.min(nums[i], minProd * nums[i]);

        result = Math.max(result, maxProd);
    }

    return result;
};