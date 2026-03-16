// Source: https://leetcode.com/problems/split-with-minimum-sum/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer num, split it into two non-negative integers num1 and num2 such that:
//
//
// 	The concatenation of num1 and num2 is a permutation of num.
//
// 	
// 		In other words, the sum of the number of occurrences of each digit in num1 and num2 is equal to the number of occurrences of that digit in num.
// 	
// 	
// 	num1 and num2 can contain leading zeros.
//
//
// Return the minimum possible sum of num1 and num2.
//
// Example:
// Input: num = 4325
// Output: 59
// Explanation: We can split 4325 so that num1 is 24 and num2 is 35, giving a sum of 59. We can prove that 59 is indeed the minimal possible sum.
//
// Constraints:
// 10 <= num <= 109
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} num
 * @return {number}
 */
var splitNum = function(num) {
    const digits = num.toString().split('').map(Number);
    digits.sort((a, b) => a - b);
    let num1 = 0;
    let num2 = 0;
    for (let i = 0; i < digits.length; i++) {
        if (i % 2 === 0) {
            num1 = num1 * 10 + digits[i];
        } else {
            num2 = num2 * 10 + digits[i];
        }
    }
    return num1 + num2;
};