// Source: https://leetcode.com/problems/equal-rational-numbers/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t, each of which represents a non-negative rational number, return true if and only if they represent the same number. The strings may use parentheses to denote the repeating part of the rational number.
//
// A rational number can be represented using up to three parts: <IntegerPart>, <NonRepeatingPart>, and a <RepeatingPart>. The number will be represented in one of the following three ways:
//
//
// 	<IntegerPart>
//
// 	
// 		For example, 12, 0, and 123.
// 	
// 	
// 	<IntegerPart><.><NonRepeatingPart>
// 	
// 		For example, 0.5, 1., 2.12, and 123.0001.
// 	
// 	
// 	<IntegerPart><.><NonRepeatingPart><(><RepeatingPart><)>
// 	
// 		For example, 0.1(6), 1.(9), 123.00(1212).
// 	
// 	
//
//
// The repeating portion of a decimal expansion is conventionally denoted within a pair of round brackets. For example:
//
//
// 	1/6 = 0.16666666... = 0.1(6) = 0.1666(6) = 0.166(66).
//
// Example:
// Input: s = "0.(52)", t = "0.5(25)"
// Output: true
// Explanation: Because "0.(52)" represents 0.52525252..., and "0.5(25)" represents 0.52525252525..... , the strings represent the same number.
//
// Constraints:
// Each part consists only of digits.
// 	The <IntegerPart> does not have leading zeros (except for the zero itself).
// 	1 <= <IntegerPart>.length <= 4
// 	0 <= <NonRepeatingPart>.length <= 4
// 	1 <= <RepeatingPart>.length <= 4
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
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
var isRationalEqual = function(s, t) {
    function parseRational(str) {
        const [integerPart, decimalPart] = str.split('.');
        let nonRepeatingPart = '';
        let repeatingPart = '';
        if (decimalPart) {
            const parenIndex = decimalPart.indexOf('(');
            if (parenIndex !== -1) {
                nonRepeatingPart = decimalPart.substring(0, parenIndex);
                repeatingPart = decimalPart.substring(parenIndex + 1, decimalPart.length - 1);
            } else {
                nonRepeatingPart = decimalPart;
            }
        }
        return { integerPart, nonRepeatingPart, repeatingPart };
    };

    function toFraction({ integerPart, nonRepeatingPart, repeatingPart }) {
        const intPart = BigInt(integerPart);
        const nonRepeatLen = BigInt(nonRepeatingPart.length);
        const repeatLen = BigInt(repeatingPart.length);
        const nonRepeatNum = BigInt(nonRepeatingPart || '0');
        const repeatNum = BigInt(repeatingPart || '0');
        const denominator = (10n ** nonRepeatLen) * (10n ** repeatLen - 1n);
        const numerator = intPart * denominator + nonRepeatNum * (10n ** repeatLen - 1n) + repeatNum;
        return [numerator, denominator];
    }
    
    const [num1, den1] = toFraction(parseRational(s));
    const [num2, den2] = toFraction(parseRational(t));
    return num1 * den2 === num2 * den1;
    
    };