// Source: https://leetcode.com/problems/smallest-value-after-replacing-with-sum-of-prime-factors/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n.
//
// Continuously replace n with the sum of its prime factors.
//
//
// 	Note that if a prime factor divides n multiple times, it should be included in the sum as many times as it divides n.
//
//
// Return the smallest value n will take on.
//
// Example:
// Input: n = 15
// Output: 5
// Explanation: Initially, n = 15.
// 15 = 3 * 5, so replace n with 3 + 5 = 8.
// 8 = 2 * 2 * 2, so replace n with 2 + 2 + 2 = 6.
// 6 = 2 * 3, so replace n with 2 + 3 = 5.
// 5 is the smallest value n will take on.
//
// Constraints:
// 2 <= n <= 105
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
 * @return {number}
 */
var smallestValue = function(n) {
    const getSumOfPrimeFactors = (num) => {
        let sum = 0;
        let temp_n = num;
        for (let i = 2; i * i <= temp_n; i++) {
            while (temp_n % i === 0) {
                sum += i;
                temp_n /= i;
            }
        }
        if (temp_n > 1) {
            sum += temp_n;
        }
        return sum;
    };

    let currentValue = n;
    while (true) {
        const nextValue = getSumOfPrimeFactors(currentValue);
        if (nextValue >= currentValue) {
            break;
        }
        currentValue = nextValue;
    }
    return currentValue;
};
