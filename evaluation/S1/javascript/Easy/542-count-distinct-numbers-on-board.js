// Source: https://leetcode.com/problems/count-distinct-numbers-on-board/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer n, that is initially placed on a board. Every day, for 109 days, you perform the following procedure:
//
//
// 	For each number x present on the board, find all numbers 1 <= i <= n such that x % i == 1.
// 	Then, place those numbers on the board.
//
//
// Return the number of distinct integers present on the board after 109 days have elapsed.
//
// Note:
//
//
// 	Once a number is placed on the board, it will remain on it until the end.
// 	% stands for the modulo operation. For example, 14 % 3 is 2.
//
// Example:
// Input: n = 5
// Output: 4
// Explanation: Initially, 5 is present on the board. 
// The next day, 2 and 4 will be added since 5 % 2 == 1 and 5 % 4 == 1. 
// After that day, 3 will be added to the board because 4 % 3 == 1. 
// At the end of a billion days, the distinct numbers on the board will be 2, 3, 4, and 5.
//
// Constraints:
// 1 <= n <= 100
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
 * @return {number}
 */
var distinctIntegers = function(n) {
    return n === 1 ? 1 : n - 1;     
};
