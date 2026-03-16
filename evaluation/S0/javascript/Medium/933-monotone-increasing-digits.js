// Source: https://leetcode.com/problems/monotone-increasing-digits/   |   Difficulty: Medium
//
// Problem Description:
// An integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.
//
// Given an integer n, return the largest number that is less than or equal to n with monotone increasing digits.
//
// Example:
// Input: n = 10
// Output: 9
//
// Constraints:
// 0 <= n <= 109
//

/**
 * @param {number} n
 * @return {number}
 */
var monotoneIncreasingDigits = function(n) {
    const digits = String(n).split('').map(Number);
    let marker = digits.length;
    for (let i = digits.length - 1; i > 0; i--) {
        if (digits[i] < digits[i - 1]) {
            digits[i - 1]--;
            marker = i;
        }
    }
    for (let i = marker; i < digits.length; i++) {
        digits[i] = 9;
    }
    return Number(digits.join(''));
};