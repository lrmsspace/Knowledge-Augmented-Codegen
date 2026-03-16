// Source: https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the decimal value of the binary string formed by concatenating the binary representations of 1 to n in order, modulo 109 + 7.
//
// Example:
// Input: n = 1
// Output: 1
// Explanation: "1" in binary corresponds to the decimal value 1.
//
// Constraints:
// 1 <= n <= 105
//

/**
 * @param {number} n
 * @return {number}
 */
var concatenatedBinary = function(n) {
    const MOD = 1e9 + 7;
    let result = 0;
    let length = 0;
    for (let i = 1; i <= n; i++) {
        if ((i & (i - 1)) === 0) {
            length++;
        }
        result = ((result << length) | i) % MOD;
    }
    return result;
};