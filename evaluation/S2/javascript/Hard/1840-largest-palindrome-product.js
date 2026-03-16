// Source: https://leetcode.com/problems/largest-palindrome-product/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, return the largest palindromic integer that can be represented as the product of two n-digits integers. Since the answer can be very large, return it modulo 1337.
//
// Example:
// Input: n = 2
// Output: 987
// Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
//
// Constraints:
// 1 <= n <= 8
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
var largestPalindrome = function(n) {
    if (n === 1) return 9;
    
    const upperLimit = Math.pow(10, n) - 1;
    const lowerLimit = Math.pow(10, n - 1);
    
    for (let i = upperLimit; i >= lowerLimit; i--) {
        const palindrome = createPalindrome(i);
        
        for (let j = upperLimit; j >= lowerLimit; j--) {
            if (palindrome / j > upperLimit) break;
            if (palindrome % j === 0) {
                return palindrome % 1337;
            }
        }
    }
    
    return -1;
};
