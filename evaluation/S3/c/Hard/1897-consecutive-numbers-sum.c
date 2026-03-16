// Source: https://leetcode.com/problems/consecutive-numbers-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, return the number of ways you can write n as the sum of consecutive positive integers.
//
// Example:
// Input: n = 5
// Output: 2
// Explanation: 5 = 2 + 3
//
// Constraints:
// 1 <= n <= 109
//
// Helpful references (internal KB):
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this approach when you need to calculate the total count or sum of all positive divisors for a given integer, typically by leveraging its prime factorization.
//   • Idea: The number of divisors d(n) and sum of divisors sigma(n) are arithmetic functions derived from the prime factorization of an integer n. Both can be computed efficiently by first finding prime factors and their exponents, resulting in an O(sqrt(N)) or O(log N) complexity with precomputed primes.
//   • Invariants: The current count of divisors is the product of (exponent + 1) for all prime factors found so far.; The current sum of divisors is the product of (1 + p + ... + p^e) for all prime factors found so far.
//   • Tips: Precompute primes using a sieve for efficiency when dealing with multiple queries or large numbers.; For sum of divisors, the formula is sigma(n) = product((1 + p_i + ... + p_i^e_i)) for each prime factor p_i^e_i.
//   • Pitfalls: Forgetting to handle n=1 correctly, which has one divisor.; Integer overflow when calculating sums or products of large powers, especially for sum of divisors.
// - Integer factorization (number, enumeration)
//   • When to use: Use when needing to decompose a composite integer into its prime factors, especially for numbers where trial division is feasible. It's suitable for problems requiring the unique prime components of a number.
//   • Idea: Integer factorization decomposes a given composite number into a product of its prime factors. The most common approach, trial division, involves testing divisibility by prime numbers up to the square root of the number, with optimizations for small primes and patterns like modulo 6.
//   • Invariants: The product of found prime factors multiplied by the current number equals the original number.; All prime factors found so far are less than or equal to the current trial divisor.
//   • Tips: Handle small prime factors (2, 3, 5) separately for efficiency.; Optimize trial division by checking only primes or numbers of form 6k +/- 1.
//   • Pitfalls: Forgetting to handle the case where the remaining number is a prime factor itself.; Inefficiently checking all numbers instead of only potential prime divisors.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int consecutiveNumbersSum(int n) {
    int count = 0;
    int sum = 0;
    for (int i = 1; sum < n; i++) {
        sum += i;
        if ((n - sum) % i == 0) {
            count++;
        }
    }
    return count;       
}
