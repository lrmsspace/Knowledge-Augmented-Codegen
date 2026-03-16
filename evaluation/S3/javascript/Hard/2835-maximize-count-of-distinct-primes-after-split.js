// Source: https://leetcode.com/problems/maximize-count-of-distinct-primes-after-split/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums having length n and a 2D integer array queries where queries[i] = [idx, val].
//
// For each query:
//
//
// 	Update nums[idx] = val.
// 	Choose an integer k with 1 <= k < n to split the array into the non-empty prefix nums[0..k-1] and suffix nums[k..n-1] such that the sum of the counts of distinct prime values in each part is maximum.
//
//
// Note: The changes made to the array in one query persist into the next query.
//
// Return an array containing the result for each query, in the order they are given.
//
// Example:
// Input: nums = [2,1,3,1,2], queries = [[1,2],[3,3]]
//
// Output: [3,4]
//
// Explanation:
//
//
// 	Initially nums = [2, 1, 3, 1, 2].
// 	After 1st query, nums = [2, 2, 3, 1, 2]. Split nums into [2] and [2, 3, 1, 2]. [2] consists of 1 distinct prime and [2, 3, 1, 2] consists of 2 distinct primes. Hence, the answer for this query is 1 + 2 = 3.
// 	After 2nd query, nums = [2, 2, 3, 3, 2]. Split nums into [2, 2, 3] and [3, 2] with an answer of 2 + 2 = 4.
// 	The output is [3, 4].
//
// Constraints:
// 2 <= n == nums.length <= 5 * 104
// 	1 <= queries.length <= 5 * 104
// 	1 <= nums[i] <= 105
// 	0 <= queries[i][0] < nums.length
// 	1 <= queries[i][1] <= 105
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
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @return {number[]}
 */
var maximumCount = function(nums, queries) {
    const MAX_NUM = 100000;
    const isPrime = new Array(MAX_NUM + 1).fill(true);
    isPrime[0] = isPrime[1] = false;
    
    for (let i = 2; i * i <= MAX_NUM; i++) {
        if (isPrime[i]) {
            for (let j = i * i; j <= MAX_NUM; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    const results = [];
    for (const [left, right] of queries) {
        let count = 0;
        for (let i = left; i <= right; i++) {
            if (isPrime[i]) {
                count++;
            }
        }
        results.push(count);
    }
    return results;
};
