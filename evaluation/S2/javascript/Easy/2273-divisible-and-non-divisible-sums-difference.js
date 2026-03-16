// Source: https://leetcode.com/problems/divisible-and-non-divisible-sums-difference/   |   Difficulty: Easy
//
// Problem Description:
// You are given positive integers n and m.
//
// Define two integers as follows:
//
//
// 	num1: The sum of all integers in the range [1, n] (both inclusive) that are not divisible by m.
// 	num2: The sum of all integers in the range [1, n] (both inclusive) that are divisible by m.
//
//
// Return the integer num1 - num2.
//
// Example:
// Input: n = 10, m = 3
// Output: 19
// Explanation: In the given example:
// - Integers in the range [1, 10] that are not divisible by 3 are [1,2,4,5,7,8,10], num1 is the sum of those integers = 37.
// - Integers in the range [1, 10] that are divisible by 3 are [3,6,9], num2 is the sum of those integers = 18.
// We return 37 - 18 = 19 as the answer.
//
// Constraints:
// 1 <= n, m <= 1000
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
 * @param {number} n
 * @param {number} m
 * @return {number}
 */
var differenceOfSums = function(n, m) {
    let num1 = 0, num2 = 0;
    
    for (let i = 1; i <= n; i++) {
        if (i % m === 0) {
            num2 += i;
        } else {
            num1 += i;
        }
    }
    return num1 - num2;
};
