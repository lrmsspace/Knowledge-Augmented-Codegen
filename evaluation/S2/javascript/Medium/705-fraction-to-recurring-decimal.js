// Source: https://leetcode.com/problems/fraction-to-recurring-decimal/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
//
// If the fractional part is repeating, enclose the repeating part in parentheses
//
// If multiple answers are possible, return any of them.
//
// It is guaranteed that the length of the answer string is less than 104 for all the given inputs.
//
// Note that if the fraction can be represented as a finite length string, you must return it.
//
// Example:
// Input: numerator = 1, denominator = 2
// Output: "0.5"
//
// Constraints:
// -231 <= numerator, denominator <= 231 - 1
// 	denominator != 0
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} numerator
 * @param {number} denominator
 * @return {string}
 */
var fractionToDecimal = function(numerator, denominator) {
    if (numerator === 0) return '0';
    const sign = (numerator < 0) ^ (denominator < 0) ? '-' : '';
    const num = Math.abs(numerator), den = Math.abs(denominator);
    const integerPart = Math.floor(num / den);
    let remainder = num % den;
    if (remainder === 0) return sign + integerPart.toString();
    
    const map = new Map();
    let decimalPart = '';
    while (remainder !== 0) {
        if (map.has(remainder)) {
            decimalPart = decimalPart.slice(0, map.get(remainder)) + '(' + decimalPart.slice(map.get(remainder)) + ')';
            break;
        }
        map.set(remainder, decimalPart.length);
        remainder *= 10;
        decimalPart += Math.floor(remainder / den).toString();
        remainder %= den;
    }
    
    return sign + integerPart.toString() + '.' + decimalPart;
};
