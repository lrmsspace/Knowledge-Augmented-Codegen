// Source: https://leetcode.com/problems/nth-magical-number/   |   Difficulty: Hard
//
// Problem Description:
// A positive integer is magical if it is divisible by either a or b.
//
// Given the three integers n, a, and b, return the nth magical number. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 1, a = 2, b = 3
// Output: 2
//
// Constraints:
// 1 <= n <= 109
// 	2 <= a, b <= 4 * 104
//

/**
 * @param {number} n
 * @param {number} a
 * @param {number} b
 * @return {number}
 */
var nthMagicalNumber = function(n, a, b) {
    const MOD = 1e9 + 7;
    const lcm = (a * b) / gcd(a, b);
    const count = (x) => Math.floor(x / a) + Math.floor(x / b) - Math.floor(x / lcm);
    let left = 1;
    let right = n * Math.min(a, b);

    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        if (count(mid) < n) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left % MOD;
};