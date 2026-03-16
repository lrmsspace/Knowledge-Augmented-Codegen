// Source: https://leetcode.com/problems/digit-operations-to-make-two-integers-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers n and m that consist of the same number of digits.
//
// You can perform the following operations any number of times:
//
//
// 	Choose any digit from n that is not 9 and increase it by 1.
// 	Choose any digit from n that is not 0 and decrease it by 1.
//
//
// The integer n must not be a prime number at any point, including its original value and after each operation.
//
// The cost of a transformation is the sum of all values that n takes throughout the operations performed.
//
// Return the minimum cost to transform n into m. If it is impossible, return -1.
//
// Example:
// Input: n = 10, m = 12
//
// Output: 85
//
// Explanation:
//
// We perform the following operations:
//
//
// 	Increase the first digit, now n = 20.
// 	Increase the second digit, now n = 21.
// 	Increase the second digit, now n = 22.
// 	Decrease the first digit, now n = 12.
//
// Constraints:
// 1 <= n, m < 104
// 	n and m consist of the same number of digits.
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: Use when you need to find all prime numbers up to a certain limit N efficiently. It is ideal for problems requiring primality tests or prime factorizations for multiple numbers within a fixed range.
//   • Idea: The Sieve of Eratosthenes is an efficient algorithm for finding all prime numbers up to a specified integer N. It works by iteratively marking the multiples of each prime number as composite, achieving a time complexity of O(N log log N).
//   • Invariants: For any number `p` processed, all its multiples less than `p*p` are already marked composite.; At the start of an iteration for `i`, if `is_prime[i]` is true, then `i` is a prime number.
//   • Tips: Initialize a boolean array `is_prime` to true for all numbers.; Start marking multiples from `p*p` for each prime `p` to optimize.
//   • Pitfalls: Forgetting to handle 0 and 1 correctly (they are not prime).; Integer overflow when calculating `i*i` for large `i`.
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
//   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
//   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
//   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minOperations(int n, int m) {
        // Step 1: Generate a list of prime numbers up to 9999 using the Sieve of Eratosthenes
        boolean[] isPrime = sieveOfEratosthenes(9999);

        // Step 2: Use BFS to find the minimum cost to transform n into m
        return bfs(n, m, isPrime);          
    }
}
