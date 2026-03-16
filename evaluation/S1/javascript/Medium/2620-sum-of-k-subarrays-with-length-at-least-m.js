// Source: https://leetcode.com/problems/sum-of-k-subarrays-with-length-at-least-m/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and two integers, k and m.
//
// Return the maximum sum of k non-overlapping subarrays of nums, where each subarray has a length of at least m.
//
// Example:
// Input: nums = [1,2,-1,3,3,4], k = 2, m = 2
//
// Output: 13
//
// Explanation:
//
// The optimal choice is:
//
//
// 	Subarray nums[3..5] with sum 3 + 3 + 4 = 10 (length is 3 >= m).
// 	Subarray nums[0..1] with sum 1 + 2 = 3 (length is 2 >= m).
//
//
// The total sum is 10 + 3 = 13.
//
// Constraints:
// 1 <= nums.length <= 2000
// 	-104 <= nums[i] <= 104
// 	1 <= k <= floor(nums.length / m)
// 	1 <= m <= 3
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Sparse Table (array, sparse-table, dp-2d)
//   • When to use: Use when you need to answer range queries, especially Range Minimum/Maximum Queries, on an immutable array very quickly. It is ideal for scenarios where the data does not change and query performance is critical.
//   • Idea: Sparse Table is a data structure that precomputes answers for all range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like Range Minimum/Maximum Queries on a static array, with O(N log N) precomputation.
//   • Invariants: st[k][i] holds the result for the segment starting at index i with length 2^k.; For any k > 0, st[k][i] combines the results of two adjacent segments of length 2^(k-1).
//   • Tips: Precompute log2 values to find the largest power of two in O(1).; Best suited for idempotent operations like minimum, maximum, or GCD.
//   • Pitfalls: Does not support array updates; any modification invalidates the structure.; Inefficient for non-idempotent operations like range sum or XOR in O(1).
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
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
 * @param {number} m
 * @return {number}
 */
var maxSum = function(nums, k, m) {
    const n = nums.length;
    // Step 1: Compute prefix sums for O(1) range sum queries
    const prefixSum = new Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    // Step 2: Create a sparse table to find the maximum subarray sum of length at least m in O(1)
    const maxSubarraySum = new Array(n).fill(0);
    for (let length = m; length <= n; length++) {
        for (let start = 0; start + length <= n; start++) {
            const end = start + length;
            maxSubarraySum[start] = Math.max(maxSubarraySum[start], prefixSum[end] - prefixSum[start]);
        }
    }

    // Step 3: Use a max heap to find the top k non-overlapping subarrays
    const heap = [];
    for (let i = 0; i < n; i++) {
        if (maxSubarraySum[i] > 0) {
            heap.push({ sum: maxSubarraySum[i], index: i });
        }
    }
    heap.sort((a, b) => b.sum - a.sum); // Max heap based on sum

    let totalMaxSum = 0;
    const selectedIndices = new Set();
    
    while (k > 0 && heap.length > 0) {
        const { sum, index } = heap.shift(); // Get the largest sum
        if (!selectedIndices.has(index)) {
            totalMaxSum += sum;
            selectedIndices.add(index);
            // Mark overlapping indices as unavailable
            for (let j = index; j < index + m && j < n; j++) {
                selectedIndices.add(j);
            }
            k--;
        }
    }

    return totalMaxSum;
};
