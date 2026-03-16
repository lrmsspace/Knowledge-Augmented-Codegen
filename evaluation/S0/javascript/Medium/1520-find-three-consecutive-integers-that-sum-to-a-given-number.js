// Source: https://leetcode.com/problems/find-three-consecutive-integers-that-sum-to-a-given-number/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer num, return three consecutive integers (as a sorted array) that sum to num. If num cannot be expressed as the sum of three consecutive integers, return an empty array.
//
// Example:
// Input: num = 33
// Output: [10,11,12]
// Explanation: 33 can be expressed as 10 + 11 + 12 = 33.
// 10, 11, 12 are 3 consecutive integers, so we return [10, 11, 12].
//
// Constraints:
// 0 <= num <= 1015
//

/**
 * @param {number} num
 * @return {number[]}
 */
var sumOfThree = function(num) {
    if (num % 3 !== 0) {
        return [];
    }
    const start = Math.floor(num / 3) - 1;
    return [start, start + 1, start + 2];
};
