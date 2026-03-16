// Source: https://leetcode.com/problems/maximum-xor-product/   |   Difficulty: Medium
//
// Problem Description:
// Given three integers a, b, and n, return the maximum value of (a XOR x) * (b XOR x) where 0 <= x < 2n.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Note that XOR is the bitwise XOR operation.
//
// Example:
// Input: a = 12, b = 5, n = 4
// Output: 98
// Explanation: For x = 2, (a XOR x) = 14 and (b XOR x) = 7. Hence, (a XOR x) * (b XOR x) = 98. 
// It can be shown that 98 is the maximum value of (a XOR x) * (b XOR x) for all 0 <= x < 2n.
//
// Constraints:
// 0 <= a, b < 250
// 	0 <= n <= 50
//

/**
 * @param {number} a
 * @param {number} b
 * @param {number} n
 * @return {number}
 */
var maximumXorProduct = function(a, b, n) {
    const MOD = 1e9 + 7;
    let x = 0;
    for (let i = 0; i < n; i++) {
        const bitA = (a >> i) & 1;
        const bitB = (b >> i) & 1;
        if (bitA === 0 && bitB === 0) {
            x |= (1 << i);
        }
    }
    const result = ((a ^ x) * (b ^ x)) % MOD;
    return result;
};
