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
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Primality tests (number, mod-exp, randomized, probability-statistics, simulation)
//   • When to use: Use when needing to efficiently determine if a large number is prime or composite, especially for cryptographic applications or number theory problems. It's suitable for verifying primality with high probability, or deterministically for numbers within certain bounds.
//   • Idea: The Miller-Rabin primality test is a probabilistic algorithm that determines if a given number is composite or a strong probable prime. It leverages properties of modular arithmetic and Fermat's Little Theorem to achieve a polynomial time complexity, typically O(k * log^3 n) for k iterations.
//   • Invariants: The number `n` being tested is an odd integer greater than 2.; The expression `n-1` is decomposed into `2^s * d`, where `d` is an odd integer.
//   • Tips: Pre-check for small prime divisors to quickly filter out many composite numbers.; Perform multiple iterations with different random bases to increase the certainty of primality.
//   • Pitfalls: The probabilistic version can yield false positives (strong probable primes) if too few bases are tested.; Incorrectly implementing modular exponentiation can lead to incorrect results or performance issues.
// - Factorial modulo 
// p (number, array, recursion, mod-exp, dp-1d)
//   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
//   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
//   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
//   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
//   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
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
var countGoodNumbers = function(n) {
    const MOD = 1e9 + 7;
    const evenCount = Math.ceil(n / 2);
    const oddCount = Math.floor(n / 2);
    const evenChoices = 5; // Digits at even indices can be 0, 2, 4, 6, 8
    const oddChoices = 4; // Digits at odd indices can be 2, 3, 5, 7
    return (modExp(evenChoices, evenCount, MOD) * modExp(oddChoices, oddCount, MOD)) % MOD;
};
