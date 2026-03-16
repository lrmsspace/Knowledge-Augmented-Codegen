// Source: https://leetcode.com/problems/maximum-product-of-two-digits/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer n.
//
// Return the maximum product of any two digits in n.
//
// Note: You may use the same digit twice if it appears more than once in n.
//
// Example:
// Input: n = 31
//
// Output: 3
//
// Explanation:
//
//
// 	The digits of n are [3, 1].
// 	The possible products of any two digits are: 3 * 1 = 3.
// 	The maximum product is 3.
//
// Constraints:
// 10 <= n <= 109
//

/**
 * @param {number} n
 * @return {number}
 */
var maxProduct = function(n) {
    const digits = n.toString().split('').map(digit => parseInt(digit));
    let maxProduct = 0;
    for (let i = 0; i < digits.length; i++) {
        for (let j = i + 1; j < digits.length; j++) {
            const product = digits[i] * digits[j];
            if (product > maxProduct) {
                maxProduct = product;
            }
        }
    }
    return maxProduct;
};