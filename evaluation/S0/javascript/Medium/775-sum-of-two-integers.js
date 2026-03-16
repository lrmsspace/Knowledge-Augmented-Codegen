// Source: https://leetcode.com/problems/sum-of-two-integers/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers a and b, return the sum of the two integers without using the operators + and -.
//
// Example:
// Input: a = 1, b = 2
// Output: 3
//
// Constraints:
// -1000 <= a, b <= 1000
//

/**
 * @param {number} a
 * @param {number} b
 * @return {number}
 */
var getSum = function(a, b) {
    while (b !== 0) {
        const carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
};
