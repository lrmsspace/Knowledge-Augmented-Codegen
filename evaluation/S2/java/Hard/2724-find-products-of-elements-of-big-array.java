// Source: https://leetcode.com/problems/find-products-of-elements-of-big-array/   |   Difficulty: Hard
//
// Problem Description:
// The powerful array of a non-negative integer x is defined as the shortest sorted array of powers of two that sum up to x. The table below illustrates examples of how the powerful array is determined. It can be proven that the powerful array of x is unique.
//
//
// 	
// 		
// 			num
// 			Binary Representation
// 			powerful array
// 		
// 		
// 			1
// 			00001
// 			[1]
// 		
// 		
// 			8
// 			01000
// 			[8]
// 		
// 		
// 			10
// 			01010
// 			[2, 8]
// 		
// 		
// 			13
// 			01101
// 			[1, 4, 8]
// 		
// 		
// 			23
// 			10111
// 			[1, 2, 4, 16]
// 		
// 	
//
//
// The array big_nums is created by concatenating the powerful arrays for every positive integer i in ascending order: 1, 2, 3, and so on. Thus, big_nums begins as [1, 2, 1, 2, 4, 1, 4, 2, 4, 1, 2, 4, 8, ...].
//
// You are given a 2D integer matrix queries, where for queries[i] = [fromi, toi, modi] you should calculate (big_nums[fromi] * big_nums[fromi + 1] * ... * big_nums[toi]) % modi.
//
// Return an integer array answer such that answer[i] is the answer to the ith query.
//
// Example:
// Input: queries = [[1,3,7]]
//
// Output: [4]
//
// Explanation:
//
// There is one query.
//
// big_nums[1..3] = [2,1,2]. The product of them is 4. The result is 4 % 7 = 4.
//
// Constraints:
// 1 <= queries.length <= 500
// 	queries[i].length == 3
// 	0 <= queries[i][0] <= queries[i][1] <= 1015
// 	1 <= queries[i][2] <= 105
//
// Helpful references (internal KB):
// - Factorial modulo 
// p (number, array, recursion, mod-exp, dp-1d)
//   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
//   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
//   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
//   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
//   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
//   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
//   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
//   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
//   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] findProductsOfElements(long[][] queries) {
        int n = queries.length;
        int[] ans = new int[n];
        for (int i = 0; i < n; i++) {
            long from = queries[i][0];
            long to = queries[i][1];
            long mod = queries[i][2];
            long product = 1;
            for (long j = from; j <= to; j++) {
                product = (product * getPowerfulArrayElement(j)) % mod;
            }
            ans[i] = (int) product;
        }
        return ans;         
    }
}
