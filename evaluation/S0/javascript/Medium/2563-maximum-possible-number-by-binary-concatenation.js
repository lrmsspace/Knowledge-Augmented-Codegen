// Source: https://leetcode.com/problems/maximum-possible-number-by-binary-concatenation/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums of size 3.
//
// Return the maximum possible number whose binary representation can be formed by concatenating the binary representation of all elements in nums in some order.
//
// Note that the binary representation of any number does not contain leading zeros.
//
// Example:
// Input: nums = [1,2,3]
//
// Output: 30
//
// Explanation:
//
// Concatenate the numbers in the order [3, 1, 2] to get the result "11110", which is the binary representation of 30.
//
// Constraints:
// nums.length == 3
// 	1 <= nums[i] <= 127
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxGoodNumber = function(nums) {
    const binaryStrings = nums.map(num => num.toString(2));
    binaryStrings.sort((a, b) => (b + a).localeCompare(a + b));
    const concatenatedBinary = binaryStrings.join('');
    return parseInt(concatenatedBinary, 2); 
};
