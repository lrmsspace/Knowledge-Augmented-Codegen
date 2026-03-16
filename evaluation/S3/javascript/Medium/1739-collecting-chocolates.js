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
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
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
    let minCost = Infinity;
    for (let shift = 0; shift < n; shift++) {
        let currentCost = 0;
        for (let i = 0; i < n; i++) {
            currentCost += nums[(i + shift) % n];
        }
        minCost = Math.min(minCost, currentCost);
    }
    return minCost;
};
