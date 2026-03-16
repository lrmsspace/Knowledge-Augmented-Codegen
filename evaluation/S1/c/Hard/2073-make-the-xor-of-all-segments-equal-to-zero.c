// Source: https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums​​​ and an integer k​​​​​. The XOR of a segment [left, right] where left <= right is the XOR of all the elements with indices between left and right, inclusive: nums[left] XOR nums[left+1] XOR ... XOR nums[right].
//
// Return the minimum number of elements to change in the array such that the XOR of all segments of size k​​​​​​ is equal to zero.
//
// Example:
// Input: nums = [1,2,0,3,0], k = 1
// Output: 3
// Explanation: Modify the array from [1,2,0,3,0] to from [0,0,0,0,0].
//
// Constraints:
// 1 <= k <= nums.length <= 2000
// 	​​​​​​0 <= nums[i] < 210
//
// Helpful references (internal KB):
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minChanges(int* nums, int numsSize, int k) {
    const int MAX_XOR = 1 << 10;
    const int INF = 0x3f3f3f3f;

    int dp[k][MAX_XOR];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < MAX_XOR; j++) {
            dp[i][j] = INF;
        }
    }

    for (int i = 0; i < numsSize; i++) {
        int group = i % k;
        if (i < k) {
            dp[group][nums[i]] = 0;
            for (int x = 0; x < MAX_XOR; x++) {
                if (x != nums[i]) {
                    dp[group][x] = 1;
                }
            }
        } else {
            int new_dp[MAX_XOR];
            for (int x = 0; x < MAX_XOR; x++) {
                new_dp[x] = INF;
            }
            for (int x = 0; x < MAX_XOR; x++) {
                for (int y = 0; y < MAX_XOR; y++) {
                    int cost = dp[group][y] + (x == nums[i] ? 0 : 1);
                    if (cost < new_dp[x ^ y]) {
                        new_dp[x ^ y] = cost;
                    }
                }
            }
            for (int x = 0; x < MAX_XOR; x++) {
                dp[group][x] = new_dp[x];
            }
        }
    }

    int result = INF;
    for (int i = 0; i < k; i++) {
        if (dp[i][0] < result) {
            result = dp[i][0];
        }
    }
    return result;      
}
