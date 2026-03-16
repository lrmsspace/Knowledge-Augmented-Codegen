// Source: https://leetcode.com/problems/prime-pairs-with-target-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. We say that two integers x and y form a prime number pair if:
//
//
// 	1 <= x <= y <= n
// 	x + y == n
// 	x and y are prime numbers
//
//
// Return the 2D sorted list of prime number pairs [xi, yi]. The list should be sorted in increasing order of xi. If there are no prime number pairs at all, return an empty array.
//
// Note: A prime number is a natural number greater than 1 with only two factors, itself and 1.
//
// Example:
// Input: n = 10
// Output: [[3,7],[5,5]]
// Explanation: In this example, there are two prime pairs that satisfy the criteria. 
// These pairs are [3,7] and [5,5], and we return them in the sorted order as described in the problem statement.
//
// Constraints:
// 1 <= n <= 106
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
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<vector<int>> findPrimePairs(int n) {
        vector<vector<int>> result;
        if (n < 2) {
            return result; // No prime pairs possible
        }

        // Sieve of Eratosthenes to find all prime numbers up to n
        vector<bool> is_prime(n + 1, true);
        is_prime[0] = is_prime[1] = false; // 0 and 1 are not prime

        for (int i = 2; i * i <= n; ++i) {
            if (is_prime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    is_prime[j] = false;
                }
            }
        }

        // Find prime pairs
        for (int i = 2; i <= n / 2; ++i) {
            if (is_prime[i] && is_prime[n - i]) {
                result.push_back({i, n - i});
            }
        }

        return result;          
    }
};
