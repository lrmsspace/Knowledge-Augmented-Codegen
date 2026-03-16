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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxSum(vector<int>& nums, int k, int m) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        // dp[i][j]: max sum using first i elements with j subarrays
        vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, LLONG_MIN));
        dp[0][0] = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                // Option 1: Do not take a subarray ending at i-1
                dp[i][j] = dp[i - 1][j];

                // Option 2: Take a subarray ending at i-1 with length at least m
                if (j > 0) {
                    for (int length = m; length <= i; ++length) {
                        long long subarray_sum = prefix[i] - prefix[i - length];
                        if (dp[i - length][j - 1] != LLONG_MIN) {
                            dp[i][j] = max(dp[i][j], dp[i - length][j - 1] + subarray_sum);
                        }
                    }
                }
            }
        }

        return dp[n][k] == LLONG_MIN ? 0 : static_cast<int>(dp[n][k]);          
    }
};
