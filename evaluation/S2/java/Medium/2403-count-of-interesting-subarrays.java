// Source: https://leetcode.com/problems/count-of-interesting-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums, an integer modulo, and an integer k.
//
// Your task is to find the count of subarrays that are interesting.
//
// A subarray nums[l..r] is interesting if the following condition holds:
//
//
// 	Let cnt be the number of indices i in the range [l, r] such that nums[i] % modulo == k. Then, cnt % modulo == k.
//
//
// Return an integer denoting the count of interesting subarrays. 
//
// Note: A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [3,2,4], modulo = 2, k = 1
// Output: 3
// Explanation: In this example the interesting subarrays are: 
// The subarray nums[0..0] which is [3]. 
// - There is only one index, i = 0, in the range [0, 0] that satisfies nums[i] % modulo == k. 
// - Hence, cnt = 1 and cnt % modulo == k.  
// The subarray nums[0..1] which is [3,2].
// - There is only one index, i = 0, in the range [0, 1] that satisfies nums[i] % modulo == k.  
// - Hence, cnt = 1 and cnt % modulo == k.
// The subarray nums[0..2] which is [3,2,4]. 
// - There is only one index, i = 0, in the range [0, 2] that satisfies nums[i] % modulo == k. 
// - Hence, cnt = 1 and cnt % modulo == k. 
// It can be shown that there are no other interesting subarrays. So, the answer is 3.
//
// Constraints:
// 1 <= nums.length <= 105 
// 	1 <= nums[i] <= 109
// 	1 <= modulo <= 109
// 	0 <= k < modulo
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, enumeration)
//   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
//   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
//   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
//   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
//   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long countInterestingSubarrays(List<Integer> nums, int modulo, int k) {
        long count = 0;
        Map<Integer, Long> prefixCount = new HashMap<>();
        prefixCount.put(0, 1L); // Base case: one way to have a prefix sum of 0

        int prefixSum = 0;
        for (int num : nums) {
            // Update the prefix sum based on the current number
            if (num % modulo == k) {
                prefixSum++;
            }
            prefixSum %= modulo;

            // Calculate the required previous prefix sum to form an interesting subarray
            int requiredPrefixSum = (prefixSum - k + modulo) % modulo;

            // Add the count of valid previous prefix sums to the total count
            count += prefixCount.getOrDefault(requiredPrefixSum, 0L);

            // Update the count of the current prefix sum in the map
            prefixCount.put(prefixSum, prefixCount.getOrDefault(prefixSum, 0L) + 1);
        }

        return count;           
    }
}
