// Source: https://leetcode.com/problems/power-of-four/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return true if it is a power of four. Otherwise, return false.
//
// An integer n is a power of four, if there exists an integer x such that n == 4x.
//
// Example:
// Input: n = 16
// Output: true
//
// Constraints:
// -231 <= n <= 231 - 1
//
//
//  
// Follow up: Could you solve it without loops/recursion?
//

/**
 * @param {number} n
 * @return {boolean}
 */
var isPowerOfFour = function(n) {
    if (n < 1) return false;
    while (n % 4 === 0) {
        n /= 4;
    }
    return n === 1;
};
