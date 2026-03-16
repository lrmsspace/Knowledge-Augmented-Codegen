// Source: https://leetcode.com/problems/largest-palindromic-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string num consisting of digits only.
//
// Return the largest palindromic integer (in the form of a string) that can be formed using digits taken from num. It should not contain leading zeroes.
//
// Example:
// Input: num = "444947137"
// Output: "7449447"
// Explanation: 
// Use the digits "4449477" from "444947137" to form the palindromic integer "7449447".
// It can be shown that "7449447" is the largest palindromic integer that can be formed.
//
// Constraints:
// 1 <= num.length <= 105
// 	num consists of digits.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} num
 * @return {string}
 */
var largestPalindromic = function(num) {
    const count = new Array(10).fill(0);
    for (const digit of num) {
        count[parseInt(digit)]++;
    }   
    let leftHalf = '';
    let middleDigit = '';
    for (let d = 9; d >= 0; d--) {
        if (count[d] % 2 === 1 && middleDigit === '') {
            middleDigit = d.toString();
        }
        const pairs = Math.floor(count[d] / 2);
        leftHalf += d.toString().repeat(pairs);
    }
    // Remove leading zeros from leftHalf
    leftHalf = leftHalf.replace(/^0+/, '');
    if (leftHalf === '' && middleDigit === '') {
        return '0';
    }
    const rightHalf = leftHalf.split('').reverse().join('');
    return leftHalf + middleDigit + rightHalf;
};
