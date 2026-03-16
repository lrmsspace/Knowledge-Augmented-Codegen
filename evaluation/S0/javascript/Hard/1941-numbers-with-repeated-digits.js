// Source: https://leetcode.com/problems/numbers-with-repeated-digits/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, return the number of positive integers in the range [1, n] that have at least one repeated digit.
//
// Example:
// Input: n = 20
// Output: 1
// Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
//
// Constraints:
// 1 <= n <= 109
//

/**
 * @param {number} n
 * @return {number}
 */
var numDupDigitsAtMostN = function(n) {
    const countUniqueDigits = (x) => {
        const digits = [];
        while (x > 0) {
            digits.push(x % 10);
            x = Math.floor(x / 10);
        }
        digits.reverse();
        const seen = new Set();
        let result = 0;
        for (let i = 0; i < digits.length; i++) {
            for (let d = (i === 0 ? 1 : 0); d < digits[i]; d++) {
                if (!seen.has(d)) {
                    result += factorial(10 - (i + 1)) / factorial(10 - (i + 1) - (digits.length - (i + 1)));
                }
            }
            if (seen.has(digits[i])) {
                break;
            }
            seen.add(digits[i]);
        }
        return result;
    }
    const factorial = (x) => {
        let result = 1;
        for (let i = 2; i <= x; i++) {
            result *= i;
        }
        return result;
    };
    return n - countUniqueDigits(n);
};
