// Source: https://leetcode.com/problems/ugly-number/   |   Difficulty: Easy
//
// Problem Description:
// An ugly number is a positive integer which does not have a prime factor other than 2, 3, and 5.
//
// Given an integer n, return true if n is an ugly number.
//
// Example:
// Input: n = 6
// Output: true
// Explanation: 6 = 2 × 3
//
// Constraints:
// -231 <= n <= 231 - 1
//
// Helpful references (internal KB):
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
// - Primality tests (number, mod-exp, randomized, probability-statistics, simulation)
//   • When to use: Use when needing to efficiently determine if a large number is prime or composite, especially for cryptographic applications or number theory problems. It's suitable for verifying primality with high probability, or deterministically for numbers within certain bounds.
//   • Idea: The Miller-Rabin primality test is a probabilistic algorithm that determines if a given number is composite or a strong probable prime. It leverages properties of modular arithmetic and Fermat's Little Theorem to achieve a polynomial time complexity, typically O(k * log^3 n) for k iterations.
//   • Invariants: The number `n` being tested is an odd integer greater than 2.; The expression `n-1` is decomposed into `2^s * d`, where `d` is an odd integer.
//   • Tips: Pre-check for small prime divisors to quickly filter out many composite numbers.; Perform multiple iterations with different random bases to increase the certainty of primality.
//   • Pitfalls: The probabilistic version can yield false positives (strong probable primes) if too few bases are tested.; Incorrectly implementing modular exponentiation can lead to incorrect results or performance issues.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @return {boolean}
 */
var isUgly = function(n) {
    if (n <= 0) {
        return false; // Ugly numbers are positive integers
    }
    const primes = [2, 3, 5];
    for (const prime of primes) {
        while (n % prime === 0) {
            n /= prime; // Divide n by the prime factor
        }
    }
    return n === 1; // If n is reduced to 1, it's an ugly number
};
