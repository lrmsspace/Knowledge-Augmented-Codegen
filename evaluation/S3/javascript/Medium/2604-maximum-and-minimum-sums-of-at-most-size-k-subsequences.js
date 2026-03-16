// Source: https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subsequences of nums with at most k elements.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 24
//
// Explanation:
//
// The subsequences of nums with at most 2 elements are:
//
//
// 	
// 		
// 			Subsequence 
// 			Minimum
// 			Maximum
// 			Sum
// 		
// 		
// 			[1]
// 			1
// 			1
// 			2
// 		
// 		
// 			[2]
// 			2
// 			2
// 			4
// 		
// 		
// 			[3]
// 			3
// 			3
// 			6
// 		
// 		
// 			[1, 2]
// 			1
// 			2
// 			3
// 		
// 		
// 			[1, 3]
// 			1
// 			3
// 			4
// 		
// 		
// 			[2, 3]
// 			2
// 			3
// 			5
// 		
// 		
// 			Final Total
// 			 
// 			 
// 			24
// 		
// 	
//
//
// The output would be 24.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
// 	1 <= k <= min(70, nums.length)
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, number, mod-exp, enumeration)
//   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
//   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
//   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
//   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
//   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Binomial Coefficients (array, enumeration)
//   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
//   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
//   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
//   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
//   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minMaxSums = function(nums, k) {
    const mod = 1e9 + 7;
    nums.sort((a, b) => a - b);
    const n = nums.length;
    let totalSum = 0;
    
    // Calculate the contribution of minimum elements
    for (let i = 0; i < n; i++) {
        const maxSize = Math.min(k - 1, n - 1 - i);
        if (maxSize >= 0) {
            totalSum = (totalSum + nums[i] * binomial(n - 1 - i, maxSize, mod)) % mod;
        }
    }
    
    // Calculate the contribution of maximum elements
    for (let i = n - 1; i >= 0; i--) {
        const maxSize = Math.min(k - 1, i);
        if (maxSize >= 0) {
            totalSum = (totalSum + nums[i] * binomial(i, maxSize, mod)) % mod;
        }
    }
    
    return totalSum;
};
