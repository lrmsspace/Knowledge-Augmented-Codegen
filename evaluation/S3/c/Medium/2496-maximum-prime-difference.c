// Source: https://leetcode.com/problems/maximum-prime-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// Return an integer that is the maximum distance between the indices of two (not necessarily different) prime numbers in nums.
//
// Example:
// Input: nums = [4,2,9,5,3]
//
// Output: 3
//
// Explanation: nums[1], nums[3], and nums[4] are prime. So the answer is |4 - 1| = 3.
//
// Constraints:
// 1 <= nums.length <= 3 * 105
// 	1 <= nums[i] <= 100
// 	The input is generated such that the number of prime numbers in the nums is at least one.
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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumPrimeDifference(int* nums, int numsSize) {
    // Step 1: Create a sieve of Eratosthenes to identify prime numbers up to 100
    int is_prime[101] = {0}; // 0 means non-prime, 1 means prime
    for (int i = 2; i <= 100; i++) {
        is_prime[i] = 1; // Assume all numbers are prime initially
    }
    for (int i = 2; i * i <= 100; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= 100; j += i) {
                is_prime[j] = 0; // Mark multiples of i as non-prime
            }
        }
    }

    // Step 2: Find the indices of the first and last prime numbers in the input array
    int first_prime_index = -1;
    int last_prime_index = -1;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] <= 100 && is_prime[nums[i]]) { // Check if the number is prime
            if (first_prime_index == -1) {
                first_prime_index = i; // Set the first prime index
            }
            last_prime_index = i; // Update the last prime index
        }
    }

    // Step 3: Calculate and return the maximum distance between the first and last prime indices
    if (first_prime_index != -1 && last_prime_index != -1) {
        return last_prime_index - first_prime_index;
    }

    return 0; // In case there are no primes, though the problem guarantees at least one prime      
}
