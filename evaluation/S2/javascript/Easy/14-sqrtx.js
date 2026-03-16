// Source: https://leetcode.com/problems/sqrtx/   |   Difficulty: Easy
//
// Problem Description:
// Given a non-negative integer x, return the square root of x rounded down to the nearest integer. The returned integer should be non-negative as well.
//
// You must not use any built-in exponent function or operator.
//
//
// 	For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.
//
// Example:
// Input: x = 4
// Output: 2
// Explanation: The square root of 4 is 2, so we return 2.
//
// Constraints:
// 0 <= x <= 231 - 1
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
 * @param {number} x
 * @return {number}
 */
var mySqrt = function(x) {
    if (x < 2) return x;
    
    let left = 1, right = Math.floor(x / 2);
    
    while (left <= right) {
        const mid = left + Math.floor((right - left) / 2);
        const midSquared = mid * mid;
        
        if (midSquared === x) {
            return mid;
        } else if (midSquared < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return right;
};
