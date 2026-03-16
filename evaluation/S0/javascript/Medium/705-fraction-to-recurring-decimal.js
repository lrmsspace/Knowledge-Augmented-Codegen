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

/**
 * @param {number} numerator
 * @param {number} denominator
 * @return {string}
 */
var fractionToDecimal = function(numerator, denominator) {
    if (numerator === 0) return "0";

    let result = "";
    if (Math.sign(numerator) !== Math.sign(denominator)) {
        result += "-";
    }
    const num = Math.abs(numerator);
    const den = Math.abs(denominator);
    result += Math.floor(num / den);

    let remainder = num % den;
    if (remainder === 0) return result;

    result += ".";
    const map = new Map();
    let decimalPart = "";
    let index = 0;
    while (remainder !== 0) {
        if (map.has(remainder)) {
            const repeatIndex = map.get(remainder);
            decimalPart = decimalPart.slice(0, repeatIndex) + "(" + decimalPart.slice(repeatIndex) + ")";
            break;
        }
        map.set(remainder, index);
        remainder *= 10;
        decimalPart += Math.floor(remainder / den);
        remainder = remainder % den;
        index++;
    }
    result += decimalPart;
    return result;  
};
