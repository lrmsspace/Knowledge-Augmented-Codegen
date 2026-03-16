// Source: https://leetcode.com/problems/count-primes/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the number of prime numbers that are strictly less than n.
//
// Example:
// Input: n = 10
// Output: 4
// Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
//
// Constraints:
// 0 <= n <= 5 * 106
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
//   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
//   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
//   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
// - Euler's totient function
//  (array, number, sieve, enumeration)
//   • When to use: Use when needing to count positive integers up to a given integer n that are relatively prime to n. It is also useful for problems involving modular arithmetic, group theory, and cryptographic applications.
//   • Idea: Euler's totient function, φ(n), counts the number of positive integers up to a given integer n that are relatively prime to n. It can be computed using prime factorization in O(sqrt(N)) or for a range using a sieve in O(N log log N).
//   • Invariants: For a sieve, phi[i] correctly stores the totient value for i after processing all its prime factors.; When factorizing n, n is continuously reduced by its smallest prime factor until it becomes 1.
//   • Tips: For a single n, find its prime factors and apply the product formula.; For computing φ(n) for all n up to a limit, use a sieve similar to Sieve of Eratosthenes.
//   • Pitfalls: Incorrectly handling repeated prime factors in the formula.; Integer overflow when calculating products for very large n.
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countPrimes(int n) {
    if (n < 3) {
        return 0;
    }

    // Sieve of Eratosthenes
    char is_prime[n];
    for (int i = 2; i < n; i++) {
        is_prime[i] = 1; // Assume all numbers are prime initially
    }

    for (int p = 2; p * p < n; p++) {
        if (is_prime[p]) {
            for (int multiple = p * p; multiple < n; multiple += p) {
                is_prime[multiple] = 0; // Mark multiples of p as non-prime
            }
        }
    }

    int prime_count = 0;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            prime_count++;
        }
    }

    return prime_count;     
}
