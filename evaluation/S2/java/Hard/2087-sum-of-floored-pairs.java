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
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It provides logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update individual elements and calculate prefix sums in an array. Both operations are performed in O(log N) time.
//   • Invariants: Each `tree[i]` element stores the sum of a contiguous range of elements from the original array, specifically from `i - (i & -i) + 1` to `i` (inclusive, 1-based).; After any `update(idx, val)` operation, `query(idx)` will reflect the new sum up to `idx`.
//   • Tips: Use 1-based indexing for array elements to simplify bitwise logic; The `idx & -idx` operation is key to navigating the implicit tree structure
//   • Pitfalls: Confusing 0-based and 1-based indexing can lead to incorrect results; Off-by-one errors when calculating range sums (e.g., `query(R) - query(L-1)`)
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int sumOfFlooredPairs(int[] nums) {
        int mod = 1_000_000_007;
        int maxNum = 100_000;
        int[] count = new int[maxNum + 1];

        // Count the frequency of each number in nums
        for (int num : nums) {
            count[num]++;
        }

        // Calculate the prefix sums of counts
        for (int i = 1; i <= maxNum; i++) {
            count[i] += count[i - 1];
        }

        long result = 0;

        // Calculate the sum of floor(nums[i] / nums[j]) for all pairs
        for (int i = 1; i <= maxNum; i++) {
            if (count[i] > count[i - 1]) { // If there are occurrences of i
                for (int j = 1; j * i <= maxNum; j++) {
                    result += (long) (count[Math.min(maxNum, j * i + i - 1)] - count[j * i - 1]) * count[i];
                    result %= mod;
                }
            }
        }

        return (int) result;            
    }
}
