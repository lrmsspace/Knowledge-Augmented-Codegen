// Source: https://leetcode.com/problems/count-special-integers/   |   Difficulty: Hard
//
// Problem Description:
// We call a positive integer special if all of its digits are distinct.
//
// Given a positive integer n, return the number of special integers that belong to the interval [1, n].
//
// Example:
// Input: n = 20
// Output: 19
// Explanation: All the integers from 1 to 20, except 11, are special. Thus, there are 19 special integers.
//
// Constraints:
// 1 <= n <= 2 * 109
//

/**
 * @param {number} n
 * @return {number}
 */
var countSpecialNumbers = function(n) {
    const digits = String(n).split('').map(Number);
    const m = digits.length;
    let count = 0;
    for (let i = 1; i < m; i++) {
        count += 9 * factorial(9) / factorial(10 - i);
    }
    const used = new Set();
    for (let i = 0; i < m; i++) {
        const digit = digits[i];
        for (let d = i === 0 ? 1 : 0; d < digit; d++) {
            if (!used.has(d)) {
                count += factorial(9 - i) / factorial(10 - m);
            }
        }
        if (used.has(digit)) {
            break;
        }
        used.add(digit);
    }
    return count;

    function factorial(n) {
        let result = 1;
        for (let i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
};