// Source: https://leetcode.com/problems/find-the-count-of-monotonic-pairs-i/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums of length n.
//
// We call a pair of non-negative integer arrays (arr1, arr2) monotonic if:
//
//
// 	The lengths of both arrays are n.
// 	arr1 is monotonically non-decreasing, in other words, arr1[0] <= arr1[1] <= ... <= arr1[n - 1].
// 	arr2 is monotonically non-increasing, in other words, arr2[0] >= arr2[1] >= ... >= arr2[n - 1].
// 	arr1[i] + arr2[i] == nums[i] for all 0 <= i <= n - 1.
//
//
// Return the count of monotonic pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,3,2]
//
// Output: 4
//
// Explanation:
//
// The good pairs are:
//
//
// 	([0, 1, 1], [2, 2, 1])
// 	([0, 1, 2], [2, 2, 0])
// 	([0, 2, 2], [2, 1, 0])
// 	([1, 2, 2], [1, 1, 0])
//
// Constraints:
// 1 <= n == nums.length <= 2000
// 	1 <= nums[i] <= 50
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Sparse Table (array, sparse-table, dp-2d)
//   • When to use: Use when you need to answer range queries, especially Range Minimum/Maximum Queries, on an immutable array very quickly. It is ideal for scenarios where the data does not change and query performance is critical.
//   • Idea: Sparse Table is a data structure that precomputes answers for all range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like Range Minimum/Maximum Queries on a static array, with O(N log N) precomputation.
//   • Invariants: st[k][i] holds the result for the segment starting at index i with length 2^k.; For any k > 0, st[k][i] combines the results of two adjacent segments of length 2^(k-1).
//   • Tips: Precompute log2 values to find the largest power of two in O(1).; Best suited for idempotent operations like minimum, maximum, or GCD.
//   • Pitfalls: Does not support array updates; any modification invalidates the structure.; Inefficient for non-idempotent operations like range sum or XOR in O(1).
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var countOfPairs = function(nums) {
    const n = nums.length;
    const mod = 1e9 + 7;
    const dp = Array.from({ length: n }, () => new Array(51).fill(0));
    for (let i = 0; i < n; i++) {
        dp[i][0] = 1;
        for (let j = 1; j <= nums[i]; j++) {
            dp[i][j] = dp[i][j - 1];
            if (i > 0) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
            }
        }
    }
    let result = 0;
    for (let j = 0; j <= 50; j++) {
        result = (result + dp[n - 1][j]) % mod;
    }
    return result;
};
