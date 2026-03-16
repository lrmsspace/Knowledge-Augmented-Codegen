// Source: https://leetcode.com/problems/integer-break/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, break it into the sum of k positive integers, where k >= 2, and maximize the product of those integers.
//
// Return the maximum product you can get.
//
// Example:
// Input: n = 2
// Output: 1
// Explanation: 2 = 1 + 1, 1 × 1 = 1.
//
// Constraints:
// 2 <= n <= 58
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
var integerBreak = function(n) {
    if (n <= 3) return n - 1;
    let product = 1;
    while (n > 4) {
        product *= 3;
        n -= 3;
    }
    return product * n;
};
