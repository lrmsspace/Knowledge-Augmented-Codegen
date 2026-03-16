// Source: https://leetcode.com/problems/reverse-integer/   |   Difficulty: Medium
//
// Problem Description:
// Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.
//
// Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
//
// Example:
// Input: x = 123
// Output: 321
//
// Constraints:
// -231 <= x <= 231 - 1
//

/**
 * @param {number} x
 * @return {number}
 */
var reverse = function(x) {
    const INT_MIN = -Math.pow(2, 31);
    const INT_MAX = Math.pow(2, 31) - 1;

    let reversed = 0;
    let sign = x < 0 ? -1 : 1;
    x = Math.abs(x);

    while (x > 0) {
        let digit = x % 10;
        x = Math.floor(x / 10);

        if (reversed > Math.floor((INT_MAX - digit) / 10)) {
            return 0; 
        }

        reversed = reversed * 10 + digit;
    }

    reversed *= sign;

    if (reversed < INT_MIN || reversed > INT_MAX) {
        return 0;
    }

    return reversed;    
};
