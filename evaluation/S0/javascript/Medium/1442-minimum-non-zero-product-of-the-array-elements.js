// Source: https://leetcode.com/problems/minimum-non-zero-product-of-the-array-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer p. Consider an array nums (1-indexed) that consists of the integers in the inclusive range [1, 2p - 1] in their binary representations. You are allowed to do the following operation any number of times:
//
//
// 	Choose two elements x and y from nums.
// 	Choose a bit in x and swap it with its corresponding bit in y. Corresponding bit refers to the bit that is in the same position in the other integer.
//
//
// For example, if x = 1101 and y = 0011, after swapping the 2nd bit from the right, we have x = 1111 and y = 0001.
//
// Find the minimum non-zero product of nums after performing the above operation any number of times. Return this product modulo 109 + 7.
//
// Note: The answer should be the minimum product before the modulo operation is done.
//
// Example:
// Input: p = 1
// Output: 1
// Explanation: nums = [1].
// There is only one element, so the product equals that element.
//
// Constraints:
// 1 <= p <= 60
//

/**
 * @param {number} p
 * @return {number}
 */
var minNonZeroProduct = function(p) {
    const MOD = 10n ** 9n + 7n;
    const maxNum = (1n << BigInt(p)) - 1n;
    const base = maxNum - 1n;
    const exponent = (maxNum >> 1n);
    let result = 1n;
    let b = base % MOD;
    let e = exponent;
    while (e > 0) {
        if (e & 1n) {
            result = (result * b) % MOD;
        }
        b = (b * b) % MOD;
        e >>= 1n;
    }
    return (result * maxNum) % MOD;
};