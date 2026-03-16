// Source: https://leetcode.com/problems/bitwise-and-of-numbers-range/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers left and right that represent the range [left, right], return the bitwise AND of all numbers in this range, inclusive.
//
// Example:
// Input: left = 5, right = 7
// Output: 4
//
// Constraints:
// 0 <= left <= right <= 231 - 1
//

/**
 * @param {number} left
 * @param {number} right
 * @return {number}
 */
var rangeBitwiseAnd = function(left, right) {
    let shift = 0;
    while (left < right) {
        left >>= 1;
        right >>= 1;
        shift++;
    }
    return left << shift;
};
