// Source: https://leetcode.com/problems/maximize-number-of-nice-divisors/   |   Difficulty: Hard
//
// Problem Description:
// You are given a positive integer primeFactors. You are asked to construct a positive integer n that satisfies the following conditions:
//
//
//   The number of prime factors of n (not necessarily distinct) is at most primeFactors.
//   The number of nice divisors of n is maximized. Note that a divisor of n is nice if it is divisible by every prime factor of n. For example, if n = 12, then its prime factors are [2,2,3], then 6 and 12 are nice divisors, while 3 and 4 are not.
//
//
// Return the number of nice divisors of n. Since that number can be too large, return it modulo 109 + 7.
//
// Note that a prime number is a natural number greater than 1 that is not a product of two smaller natural numbers. The prime factors of a number n is a list of prime numbers such that their product equals n.
//
// Example:
// Input: primeFactors = 5
// Output: 6
// Explanation: 200 is a valid value of n.
// It has 5 prime factors: [2,2,2,5,5], and it has 6 nice divisors: [10,20,40,50,100,200].
// There is not other value of n that has at most 5 prime factors and more nice divisors.
//
// Constraints:
// 1 <= primeFactors <= 109
//
// Helpful references (internal KB):
// - Factorial modulo 
// p (number, array, recursion, mod-exp, dp-1d)
//   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
//   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
//   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
//   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
//   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
// - Primitive Root (number, mod-exp, sieve, enumeration)
//   • When to use: Use when needing to find a generator for the multiplicative group of integers modulo n, or to check if a number is a primitive root. This is often required in number theory problems involving modular arithmetic and cyclic groups.
//   • Idea: This algorithm finds a primitive root modulo n by checking candidate numbers and verifying their order using Euler's totient function and its prime factors. The optimized approach significantly reduces checks from O(phi(n)) to O(k * log(n)) for each candidate, where k is the number of distinct prime factors of phi(n).
//   • Invariants: The current candidate g is coprime to n.; The order of g modulo n is being checked against divisors of phi(n).
//   • Tips: First, determine if a primitive root exists for the given n.; Calculate Euler's totient function phi(n) for the modulus n.
//   • Pitfalls: Forgetting to check the existence condition for primitive roots.; Incorrectly calculating Euler's totient function phi(n).
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} primeFactors
 * @return {number}
 */
var maxNiceDivisors = function(primeFactors) {
    const MOD = 1e9 + 7;
    if (primeFactors <= 3) return primeFactors;
    const a = Math.floor(primeFactors / 3);
    const b = primeFactors % 3;
    if (b === 0) return modPow(3, a, MOD);
    if (b === 1) return (modPow(3, a - 1, MOD) * 4) % MOD;
    return (modPow(3, a, MOD) * 2) % MOD;
};
