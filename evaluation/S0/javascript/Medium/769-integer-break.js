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
    product *= n;
    return product; 
};