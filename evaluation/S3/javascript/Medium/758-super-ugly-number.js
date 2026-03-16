// Source: https://leetcode.com/problems/super-ugly-number/   |   Difficulty: Medium
//
// Problem Description:
// A super ugly number is a positive integer whose prime factors are in the array primes.
//
// Given an integer n and an array of integers primes, return the nth super ugly number.
//
// The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
//
// Example:
// Input: n = 12, primes = [2,7,13,19]
// Output: 32
// Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 super ugly numbers given primes = [2,7,13,19].
//
// Constraints:
// 1 <= n <= 105
// 	1 <= primes.length <= 100
// 	2 <= primes[i] <= 1000
// 	primes[i] is guaranteed to be a prime number.
// 	All the values of primes are unique and sorted in ascending order.
//
// Helpful references (internal KB):
// - Linear Sieve (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a given limit N, or the smallest prime factor for every number up to N, with optimal linear time complexity.
//   • Idea: The Linear Sieve efficiently computes all prime numbers up to a limit N and the smallest prime factor for each integer. It processes every composite number exactly once by its smallest prime factor, achieving O(N) time complexity.
//   • Invariants: For all `k < i`, `lp[k]` correctly stores the smallest prime factor of `k` (or `k` itself if prime).; The `pr` list contains all prime numbers less than `i` in ascending order.
//   • Tips: Initialize an array `lp` to store the smallest prime factor for each number.; Maintain a dynamically growing list of prime numbers found so far.
//   • Pitfalls: Incorrectly marking composite numbers multiple times, leading to non-linear complexity.; Failing to stop the inner loop when `p > lp[i]`, which breaks the linearity guarantee.
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
//   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
//   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
//   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
//   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[]} primes
 * @return {number}
 */
var nthSuperUglyNumber = function(n, primes) {
    const dp = new Array(n).fill(0);
    dp[0] = 1; // The first super ugly number is always 1

    const k = primes.length;
    const indices = new Array(k).fill(0); // To track the index for each prime
    const nextMultiples = primes.slice(); // Initialize the next multiples for each prime

    for (let i = 1; i < n; i++) {
        // Find the next super ugly number by taking the minimum of the next multiples
        dp[i] = Math.min(...nextMultiples);

        // Update the indices and next multiples for all primes that match the current super ugly number
        for (let j = 0; j < k; j++) {
            if (dp[i] === nextMultiples[j]) {
                indices[j]++;
                nextMultiples[j] = dp[indices[j]] * primes[j];
            }
        }
    }

    return dp[n - 1];
};
