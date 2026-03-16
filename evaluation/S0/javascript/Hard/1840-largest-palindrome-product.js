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

/**
 * @param {number} n
 * @return {number}
 */
var largestPalindrome = function(n) {
    if (n === 1) {
        return 9;
    }
    const upperLimit = Math.pow(10, n) - 1;
    const lowerLimit = Math.pow(10, n - 1);
    for (let i = upperLimit; i >= lowerLimit; i--) {
        const leftPart = i.toString();
        const palindrome = parseInt(leftPart + leftPart.split('').reverse().join(''));
        for (let j = upperLimit; j >= lowerLimit; j--) {
            if (palindrome / j > upperLimit) {
                break;
            }
            if (palindrome % j === 0) {
                return palindrome % 1337;
            }
        }
    }
    return -1;  
};
