// Source: https://leetcode.com/problems/prime-subtraction-operation/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n.
//
// You can perform the following operation as many times as you want:
//
//
// 	Pick an index i that you haven’t picked before, and pick a prime p strictly less than nums[i], then subtract p from nums[i].
//
//
// Return true if you can make nums a strictly increasing array using the above operation and false otherwise.
//
// A strictly increasing array is an array whose each element is strictly greater than its preceding element.
//
// Example:
// Input: nums = [4,9,6,10]
// Output: true
// Explanation: In the first operation: Pick i = 0 and p = 3, and then subtract 3 from nums[0], so that nums becomes [1,9,6,10].
// In the second operation: i = 1, p = 7, subtract 7 from nums[1], so nums becomes equal to [1,2,6,10].
// After the second operation, nums is sorted in strictly increasing order, so the answer is true.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
// 	nums.length == n
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
//   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
//   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool primeSubOperation(int* nums, int numsSize) {
    // Step 1: Generate all prime numbers less than 1000 using the Sieve of Eratosthenes
    bool is_prime[1000];
    for (int i = 0; i < 1000; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false; // 0 and 1 are not prime numbers
    for (int i = 2; i * i < 1000; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < 1000; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // Step 2: Create an array of primes less than 1000
    int primes[168]; // There are 168 prime numbers less than 1000
    int prime_count = 0;
    for (int i = 2; i < 1000; i++) {
        if (is_prime[i]) {
            primes[prime_count++] = i;
        }
    }

    // Step 3: Try to make the array strictly increasing by subtracting primes
    for (int i = numsSize - 1; i > 0; i--) {
        if (nums[i] <= nums[i - 1]) {
            bool can_subtract = false;
            for (int j = prime_count - 1; j >= 0; j--) {
                if (primes[j] < nums[i] && nums[i] - primes[j] > nums[i - 1]) {
                    nums[i] -= primes[j];
                    can_subtract = true;
                    break;
                }
            }
            if (!can_subtract) {
                return false; // If we can't make it strictly increasing, return false
            }
        }
    }

    return true; // If we successfully made the array strictly increasing, return true      
}
