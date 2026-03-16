// Source: https://leetcode.com/problems/sum-of-floored-pairs/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the sum of floor(nums[i] / nums[j]) for all pairs of indices 0 <= i, j < nums.length in the array. Since the answer may be too large, return it modulo 109 + 7.
//
// The floor() function returns the integer part of the division.
//
// Example:
// Input: nums = [2,5,9]
// Output: 10
// Explanation:
// floor(2 / 5) = floor(2 / 9) = floor(5 / 9) = 0
// floor(2 / 2) = floor(5 / 5) = floor(9 / 9) = 1
// floor(5 / 2) = 2
// floor(9 / 2) = 4
// floor(9 / 5) = 1
// We calculate the floor of the division for every pair of indices in the array then sum them up.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: When you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It is ideal for scenarios requiring both fast query and update operations on an array.
//   • Idea: A Fenwick tree, or Binary Indexed Tree (BIT), is an array-based data structure that efficiently calculates prefix sums and updates individual elements in an array. It supports both point updates and prefix sum queries in O(log N) time complexity.
//   • Invariants: Each `T[i]` stores the sum of a specific range `[g(i), i]` from the original array.; The `sum(idx)` function correctly aggregates values from `A[0]` to `A[idx]`.
//   • Tips: Understand the bit manipulation (`i & -i`) for navigating parent/child relationships.; Consistently choose and apply either 0-based or 1-based indexing throughout the implementation.
//   • Pitfalls: Incorrectly handling 0-based versus 1-based indexing can lead to off-by-one errors.; Forgetting to initialize the tree or performing updates incorrectly will yield wrong results.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
// - Garner's algorithm
//  (number, array, enumeration)
//   • When to use: Use when reconstructing a large integer from a system of congruences with pairwise coprime moduli, offering an alternative to the direct Chinese Remainder Theorem approach.
//   • Idea: Garner's algorithm efficiently reconstructs an integer from its remainders modulo a set of pairwise coprime numbers, by computing its mixed radix representation coefficients. It typically runs in O(k^2 log M) time, where k is the number of moduli and M is the maximum modulus, assuming modular inverse takes log M time.
//   • Invariants: At the start of iteration j, the partial sum $V_{j-1}$ satisfies $V_{j-1} \equiv a_i \pmod{p_i}$ for all $i < j$.; For each iteration j, the coefficient $x_j$ is uniquely determined in the range $[0, p_j - 1]$.
//   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Precompute modular inverses for efficiency, especially if many are needed.
//   • Pitfalls: Incorrectly calculating modular inverses, leading to wrong coefficients.; Not handling large intermediate products, which can cause integer overflow.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int sumOfFlooredPairs(int* nums, int numsSize) {
    const int MOD = 1000000007;
    const int MAX_NUM = 100000;

    int freq[MAX_NUM + 1];
    memset(freq, 0, sizeof(freq));
    for (int i = 0; i < numsSize; ++i) {
        freq[nums[i]]++;
    }

    /* Prefix sum of frequencies */
    for (int i = 1; i <= MAX_NUM; ++i) {
        freq[i] += freq[i - 1];
    }

    long long result = 0;
    for (int i = 1; i <= MAX_NUM; ++i) {
        if (freq[i] == freq[i - 1]) continue; /* i not in nums */

        for (int multiple = i; multiple <= MAX_NUM; multiple += i) {
            int left = multiple;
            int right = (multiple + i - 1 <= MAX_NUM) ? (multiple + i - 1) : MAX_NUM;
            int countInRange = freq[right] - freq[left - 1];
            result = (result + (long long)(i / i) * countInRange % MOD * (freq[i] - freq[i - 1]) % MOD) % MOD;
        }
    }

    return (int)result;     
}
