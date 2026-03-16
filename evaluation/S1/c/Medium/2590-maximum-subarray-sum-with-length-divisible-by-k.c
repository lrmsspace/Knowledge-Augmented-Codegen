// Source: https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums and an integer k.
//
// Return the maximum sum of a subarray of nums, such that the size of the subarray is divisible by k.
//
// Example:
// Input: nums = [1,2], k = 1
//
// Output: 3
//
// Explanation:
//
// The subarray [1, 2] with sum 3 has length equal to 2 which is divisible by 1.
//
// Constraints:
// 1 <= k <= nums.length <= 2 * 105
// 	-109 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
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

long long maxSubarraySum(int* nums, int numsSize, int k) {
    long long max_sum = -0x7FFFFFFFFFFFFFFFLL;
    long long prefix_sum[numsSize + 1];
    prefix_sum[0] = 0;
    for (int i = 0; i < numsSize; ++i) {
        prefix_sum[i + 1] = prefix_sum[i] + nums[i];
    }

    long long min_prefix_sum[k];
    for (int i = 0; i < k; ++i) {
        min_prefix_sum[i] = 0x7FFFFFFFFFFFFFFFLL;
    }

    for (int i = 0; i <= numsSize; ++i) {
        int mod_index = i % k;
        if (prefix_sum[i] - min_prefix_sum[mod_index] > max_sum) {
            max_sum = prefix_sum[i] - min_prefix_sum[mod_index];
        }
        if (prefix_sum[i] < min_prefix_sum[mod_index]) {
            min_prefix_sum[mod_index] = prefix_sum[i];
        }
    }

    return max_sum;     
}
