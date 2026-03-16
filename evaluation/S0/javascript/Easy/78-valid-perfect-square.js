// Source: https://leetcode.com/problems/valid-perfect-square/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer num, return true if num is a perfect square or false otherwise.
//
// A perfect square is an integer that is the square of an integer. In other words, it is the product of some integer with itself.
//
// You must not use any built-in library function, such as sqrt.
//
// Example:
// Input: num = 16
// Output: true
// Explanation: We return true because 4 * 4 = 16 and 4 is an integer.
//
// Constraints:
// 1 <= num <= 231 - 1
//

/**
 * @param {number} num
 * @return {boolean}
 */
var isPerfectSquare = function(num) {
    if (num < 1) return false;
    let left = 1;
    let right = num;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        const square = mid * mid;
        if (square === num) {
            return true;
        } else if (square < num) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
};