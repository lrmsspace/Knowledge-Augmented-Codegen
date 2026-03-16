// Source: https://leetcode.com/problems/partition-equal-subset-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.
//
// Example:
// Input: nums = [1,5,11,5]
// Output: true
// Explanation: The array can be partitioned as [1, 5, 5] and [11].
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 100
//
// Helpful references (internal KB):
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting a subset of items, each with a weight and value, to maximize total value without exceeding a given capacity. It is applicable for resource allocation problems with discrete choices.
//   • Idea: The Knapsack Problem aims to choose items with maximum total value such that their total weight does not exceed a given capacity. It is typically solved using dynamic programming, achieving a time complexity of O(nW) for n items and capacity W.
//   • Invariants: `dp[j]` (in 1D DP) represents the maximum value achievable with capacity `j` using items considered so far.; When processing item `i` and capacity `j` (decreasing `j`), `dp[j-weight_i]` holds the value from previous items for that reduced capacity.
//   • Tips: Initialize DP table with zeros for capacity 0 and unreachable states.; For 0-1 knapsack with 1D DP, iterate capacity `j` in decreasing order.
//   • Pitfalls: Incorrect iteration order for 1D DP in 0-1 knapsack (using increasing `j`).; Off-by-one errors in item indices or capacity calculations.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool canPartition(int* nums, int numsSize) {
    int totalSum = 0;
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }
    if (totalSum % 2 != 0) {
        return false;
    }
    int target = totalSum / 2;

    bool dp[target + 1];
    for (int j = 0; j <= target; j++) {
        dp[j] = false;
    }
    dp[0] = true;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        for (int j = target; j >= num; j--) {
            dp[j] = dp[j] || dp[j - num];
        }
    }

    return dp[target];      
}
