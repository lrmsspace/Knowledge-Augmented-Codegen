// Source: https://leetcode.com/problems/the-kth-factor-of-n/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers n and k. A factor of an integer n is defined as an integer i where n % i == 0.
//
// Consider a list of all factors of n sorted in ascending order, return the kth factor in this list or return -1 if n has less than k factors.
//
// Example:
// Input: n = 12, k = 3
// Output: 3
// Explanation: Factors list is [1, 2, 3, 4, 6, 12], the 3rd factor is 3.
//
// Constraints:
// 1 <= k <= n <= 1000
//
//
//  
// Follow up:
//
// Could you solve this problem in less than O(n) complexity?
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
var kthFactor = function(n, k) {
    const factors = [];
    for (let i = 1; i * i <= n; i++) {
        if (n % i === 0) {
            factors.push(i);
            if (i !== n / i) {
                factors.push(n / i);
            }
        }
    }
    factors.sort((a, b) => a - b);
    return factors[k - 1] || -1;
};
