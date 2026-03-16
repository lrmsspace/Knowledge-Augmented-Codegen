// Source: https://leetcode.com/problems/simplified-fractions/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return a list of all simplified fractions between 0 and 1 (exclusive) such that the denominator is less-than-or-equal-to n. You can return the answer in any order.
//
// Example:
// Input: n = 2
// Output: ["1/2"]
// Explanation: "1/2" is the only unique fraction with a denominator less-than-or-equal-to 2.
//
// Constraints:
// 1 <= n <= 100
//

/**
 * @param {number} n
 * @return {string[]}
 */
var simplifiedFractions = function(n) {
    const gcd = (a, b) => {
        if (b === 0) return a;
        return gcd(b, a % b);
    };

    const result = [];
    for (let denominator = 2; denominator <= n; denominator++) {
        for (let numerator = 1; numerator < denominator; numerator++) {
            if (gcd(numerator, denominator) === 1) {
                result.push(`${numerator}/${denominator}`);
            }
        }
    }
    return result;  
            
};
