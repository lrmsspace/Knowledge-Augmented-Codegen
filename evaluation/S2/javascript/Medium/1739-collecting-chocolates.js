// Source: https://leetcode.com/problems/collecting-chocolates/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of size n representing the cost of collecting different chocolates. The cost of collecting the chocolate at the index i is nums[i]. Each chocolate is of a different type, and initially, the chocolate at the index i is of ith type.
//
// In one operation, you can do the following with an incurred cost of x:
//
//
// 	Simultaneously change the chocolate of ith type to ((i + 1) mod n)th type for all chocolates.
//
//
// Return the minimum cost to collect chocolates of all types, given that you can perform as many operations as you would like.
//
// Example:
// Input: nums = [20,1,15], x = 5
// Output: 13
// Explanation: Initially, the chocolate types are [0,1,2]. We will buy the 1st type of chocolate at a cost of 1.
// Now, we will perform the operation at a cost of 5, and the types of chocolates will become [1,2,0]. We will buy the 2nd type of chocolate at a cost of 1.
// Now, we will again perform the operation at a cost of 5, and the chocolate types will become [2,0,1]. We will buy the 0th type of chocolate at a cost of 1. 
// Thus, the total cost will become (1 + 5 + 1 + 5 + 1) = 13. We can prove that this is optimal.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 109
// 	1 <= x <= 109
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - bucket-sort (array, bucket-sort)
//   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
//   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
//   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
//   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
// - Chinese Remainder Theorem (number, recursion, mod-exp)
//   • When to use: When you need to find a unique integer solution that satisfies a system of linear congruences with pairwise coprime moduli. It is used to reconstruct a number from its remainders modulo several divisors.
//   • Idea: The Chinese Remainder Theorem (CRT) finds a unique solution x modulo the product of several pairwise coprime moduli, given a system of congruences. It typically involves computing modular inverses and combining solutions, with a complexity often dominated by modular exponentiation or extended Euclidean algorithm, usually O(N log M) or O(N log(max_modulus)).
//   • Invariants: The current combined solution 'x' satisfies 'x % m_i == a_i' for all congruences '(a_i, m_i)' processed so far.; The current combined modulus 'M' is the product of all individual moduli processed so far.
//   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Use the Extended Euclidean Algorithm to find modular inverses.
//   • Pitfalls: Forgetting to check if moduli are pairwise coprime.; Incorrectly calculating modular inverses.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} x
 * @return {number}
 */
var minCost = function(nums, x) {
    const n = nums.length;
    const extendedNums = nums.concat(nums);
    const prefixSums = new Array(2 * n).fill(0);
    for (let i = 0; i < 2 * n; i++) {
        prefixSums[i] = extendedNums[i] + (i > 0 ? prefixSums[i - 1] : 0);
    }
    let minCost = Infinity;
    for (let start = 0; start < n; start++) {
        const cost = prefixSums[start + n - 1] - (start > 0 ? prefixSums[start - 1] : 0) + x * Math.floor(start / n);
        minCost = Math.min(minCost, cost);
    }
    return minCost;
};
