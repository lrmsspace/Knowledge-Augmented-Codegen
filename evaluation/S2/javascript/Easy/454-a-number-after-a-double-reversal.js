// Source: https://leetcode.com/problems/a-number-after-a-double-reversal/   |   Difficulty: Easy
//
// Problem Description:
// Reversing an integer means to reverse all its digits.
//
//
// 	For example, reversing 2021 gives 1202. Reversing 12300 gives 321 as the leading zeros are not retained.
//
//
// Given an integer num, reverse num to get reversed1, then reverse reversed1 to get reversed2. Return true if reversed2 equals num. Otherwise return false.
//
// Example:
// Input: num = 526
// Output: true
// Explanation: Reverse num to get 625, then reverse 625 to get 526, which equals num.
//
// Constraints:
// 0 <= num <= 106
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
 * @param {number} num
 * @return {boolean}
 */
var isSameAfterReversals = function(num) {
    // If num is 0, it's the same after reversal.
    if (num === 0) return true;
    
    // If num ends with 0, it will not be the same after reversal because the leading zeros are not retained.
    if (num % 10 === 0) return false;
    
    return true;
};
