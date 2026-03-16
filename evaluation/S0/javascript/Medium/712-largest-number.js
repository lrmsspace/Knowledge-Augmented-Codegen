// Source: https://leetcode.com/problems/largest-number/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.
//
// Since the result may be very large, so you need to return a string instead of an integer.
//
// Example:
// Input: nums = [10,2]
// Output: "210"
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {string}
 */
var largestNumber = function(nums) {
    nums.sort((a, b) => {
        const strA = a.toString();
        const strB = b.toString();
        return (strB + strA).localeCompare(strA + strB);
    });

    if (nums[0] === 0) {
        return "0";
    }
    return nums.join('');   
};
