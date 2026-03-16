// Source: https://leetcode.com/problems/subtract-the-product-and-sum-of-digits-of-an-integer/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer number n, return the difference between the product of its digits and the sum of its digits.
//
// Example:
// Input: n = 234
// Output: 15 
// Explanation: 
// Product of digits = 2 * 3 * 4 = 24 
// Sum of digits = 2 + 3 + 4 = 9 
// Result = 24 - 9 = 15
//
// Constraints:
// 1 <= n <= 10^5
//

/**
 * @param {number} n
 * @return {number}
 */
var subtractProductAndSum = function(n) {
    let product = 1;
    let sum = 0;
    while (n > 0) {
        const digit = n % 10;
        product *= digit;
        sum += digit;
        n = Math.floor(n / 10);
    }
    return product - sum;
};