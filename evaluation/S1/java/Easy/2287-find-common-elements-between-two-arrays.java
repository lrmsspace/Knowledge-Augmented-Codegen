// Source: https://leetcode.com/problems/find-common-elements-between-two-arrays/   |   Difficulty: Easy
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 of sizes n and m, respectively. Calculate the following values:
//
//
// 	answer1 : the number of indices i such that nums1[i] exists in nums2.
// 	answer2 : the number of indices i such that nums2[i] exists in nums1.
//
//
// Return [answer1,answer2].
//
// Example:
// Input: nums1 = [2,3,2], nums2 = [1,2]
//
// Output: [2,1]
//
// Explanation:
//
// Constraints:
// n == nums1.length
// 	m == nums2.length
// 	1 <= n, m <= 100
// 	1 <= nums1[i], nums2[i] <= 100
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Binomial Coefficients (array, enumeration)
//   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
//   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
//   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
//   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
//   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
//   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
//   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
//   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
//   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] findIntersectionValues(int[] nums1, int[] nums2) {
        boolean[] existsInNums2 = new boolean[101];
        for (int num : nums2) {
            existsInNums2[num] = true;
        }

        int answer1 = 0;
        for (int num : nums1) {
            if (existsInNums2[num]) {
                answer1++;
            }
        }

        boolean[] existsInNums1 = new boolean[101];
        for (int num : nums1) {
            existsInNums1[num] = true;
        }

        int answer2 = 0;
        for (int num : nums2) {
            if (existsInNums1[num]) {
                answer2++;
            }
        }

        return new int[]{answer1, answer2};         
    }
}
