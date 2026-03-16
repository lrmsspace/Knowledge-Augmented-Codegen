// Source: https://leetcode.com/problems/circular-permutation-in-binary-representation/   |   Difficulty: Medium
//
// Problem Description:
// Given 2 integers n and start. Your task is return any permutation p of (0,1,2.....,2^n -1) such that :
//
//
// 	p[0] = start
// 	p[i] and p[i+1] differ by only one bit in their binary representation.
// 	p[0] and p[2^n -1] must also differ by only one bit in their binary representation.
//
// Example:
// Input: n = 2, start = 3
// Output: [3,2,0,1]
// Explanation: The binary representation of the permutation is (11,10,00,01). 
// All the adjacent element differ by one bit. Another valid permutation is [3,1,0,2]
//
// Constraints:
// 1 <= n <= 16
// 	0 <= start < 2 ^ n
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

 * @param {number} start

 * @return {number[]}

 */

var circularPermutation = function(n, start) {

    const result = [];
    for (let i = 0; i < 1 << n; i++) {
        result.push(i ^ (i >> 1) ^ start);
    }
    return result;

};
