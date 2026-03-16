// Source: https://leetcode.com/problems/ugly-number/   |   Difficulty: Easy
//
// Problem Description:
// An ugly number is a positive integer which does not have a prime factor other than 2, 3, and 5.
//
// Given an integer n, return true if n is an ugly number.
//
// Example:
// Input: n = 6
// Output: true
// Explanation: 6 = 2 × 3
//
// Constraints:
// -231 <= n <= 231 - 1
//

/**
 * @param {number} n
 * @return {boolean}
 */
var isUgly = function(n) {      
    if (n <= 0) return false;
    const factors = [2, 3, 5];
    for (const factor of factors) {
        while (n % factor === 0) {
            n /= factor;
        }
    }       
    return n === 1;     
}
