// Source: https://leetcode.com/problems/sign-of-the-product-of-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Implement a function signFunc(x) that returns:
//
//
// 	1 if x is positive.
// 	-1 if x is negative.
// 	0 if x is equal to 0.
//
//
// You are given an integer array nums. Let product be the product of all values in the array nums.
//
// Return signFunc(product).
//
// Example:
// Input: nums = [-1,-2,-3,-4,3,2,1]
// Output: 1
// Explanation: The product of all values in the array is 144, and signFunc(144) = 1
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-100 <= nums[i] <= 100
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var arraySign = function(nums) {
    let sign = 1;
    for (const num of nums) {
        if (num === 0) {
            return 0;
        } else if (num < 0) {
            sign = -sign;
        }
    }
    return sign;
};
