// Source: https://leetcode.com/problems/count-good-numbers/   |   Difficulty: Medium
//
// Problem Description:
// A digit string is good if the digits (0-indexed) at even indices are even and the digits at odd indices are prime (2, 3, 5, or 7).
//
//
// 	For example, "2582" is good because the digits (2 and 8) at even positions are even and the digits (5 and 2) at odd positions are prime. However, "3245" is not good because 3 is at an even index but is not even.
//
//
// Given an integer n, return the total number of good digit strings of length n. Since the answer may be large, return it modulo 109 + 7.
//
// A digit string is a string consisting of digits 0 through 9 that may contain leading zeros.
//
// Example:
// Input: n = 1
// Output: 5
// Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".
//
// Constraints:
// 1 <= n <= 1015
//

/**
 * @param {number} n
 * @return {number}
 */
var countGoodNumbers = function(n) {
    const MOD = 1e9 + 7;
    const evenPositions = Math.floor((n + 1) / 2);
    const oddPositions = Math.floor(n / 2);
    const evenChoices = 5; // Even digits: 0, 2, 4, 6, 8
    const oddChoices = 4;  // Prime digits: 2, 3, 5, 7

    // Helper function to perform modular exponentiation
    function modPow(base, exponent, mod) {
        let result = 1;
        let currentBase = base % mod;
        let currentExponent = exponent;

        while (currentExponent > 0) {
            if (currentExponent % 2 === 1) {
                result = (result * currentBase) % mod;
            }
            currentBase = (currentBase * currentBase) % mod;
            currentExponent = Math.floor(currentExponent / 2);
        }

        return result;
    }

    const evenPart = modPow(evenChoices, evenPositions, MOD);
    const oddPart = modPow(oddChoices, oddPositions, MOD);

    return (evenPart * oddPart) % MOD;
};