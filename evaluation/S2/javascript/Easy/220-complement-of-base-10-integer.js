// Source: https://leetcode.com/problems/complement-of-base-10-integer/   |   Difficulty: Easy
//
// Problem Description:
// The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's in its binary representation.
//
//
// 	For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
//
//
// Given an integer n, return its complement.
//
// Example:
// Input: n = 5
// Output: 2
// Explanation: 5 is "101" in binary, with complement "010" in binary, which is 2 in base-10.
//
// Constraints:
// 0 <= n < 109
//
//
//  
// Note: This question is the same as 476: https://leetcode.com/problems/number-complement/
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
var bitwiseComplement = function(n) {
    if (n === 0) return 1;
    
    let mask = 1;
    while (mask <= n) {
        mask <<= 1;
    }
    
    return mask - 1 - n;
};
