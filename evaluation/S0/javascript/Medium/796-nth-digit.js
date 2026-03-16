// Source: https://leetcode.com/problems/nth-digit/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the nth digit of the infinite integer sequence [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...].
//
// Example:
// Input: n = 3
// Output: 3
//
// Constraints:
// 1 <= n <= 231 - 1
//

/**
 * @param {number} n
 * @return {number}
 */
var findNthDigit = function(n) {
    let digitLength = 1;
    let count = 9;
    let start = 1;
    while (n > digitLength * count) {
        n -= digitLength * count;
        digitLength++;
        count *= 10;
        start *= 10;
    }
    const number = start + Math.floor((n - 1) / digitLength);
    const digitIndex = (n - 1) % digitLength;
    return Number(number.toString()[digitIndex]);
};