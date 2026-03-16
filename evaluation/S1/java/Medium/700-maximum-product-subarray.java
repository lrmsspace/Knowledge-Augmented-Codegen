// Source: https://leetcode.com/problems/maximum-product-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, find a subarray that has the largest product, and return the product.
//
// The test cases are generated so that the answer will fit in a 32-bit integer.
//
// Example:
// Input: nums = [2,3,-2,4]
// Output: 6
// Explanation: [2,3] has the largest product 6.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	-10 <= nums[i] <= 10
// 	The product of any subarray of nums is guaranteed to fit in a 32-bit integer.
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting items, each with a weight and value, to maximize total value within a limited capacity, where each item can be chosen multiple times. It is suitable for problems exhibiting optimal substructure and overlapping subproblems.
//   • Idea: The Knapsack Problem involves selecting items to maximize total value within a fixed capacity. The complete knapsack variant, where items can be taken multiple times, is typically solved using dynamic programming in O(nW) time and O(W) space.
//   • Invariants: For 2D DP `f[i][j]`, it represents the maximum value obtainable using only the first `i` items with a total weight not exceeding `j`.; For 1D DP `dp[j]`, after processing item `i`, it stores the maximum value obtainable with a total weight not exceeding `j`, considering all items up to `i`.
//   • Tips: For the complete knapsack, iterate capacity `j` forwards (from `w_i` to `W`) when using 1D DP to allow multiple selections of the current item.; The 1D DP array `dp[j]` stores the maximum value achievable for exactly capacity `j`.
//   • Pitfalls: Confusing 0-1 knapsack with complete knapsack, especially in the 1D DP iteration direction for capacity.; Incorrectly initializing the DP array, leading to incorrect base cases or propagation.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxProduct(int[] nums) {
        int n = nums.length;
        int maxSoFar = nums[0];
        int minSoFar = nums[0];
        int result = nums[0];

        for (int i = 1; i < n; i++) {
            if (nums[i] < 0) {
                // Swap maxSoFar and minSoFar
                int temp = maxSoFar;
                maxSoFar = minSoFar;
                minSoFar = temp;
            }

            maxSoFar = Math.max(nums[i], maxSoFar * nums[i]);
            minSoFar = Math.min(nums[i], minSoFar * nums[i]);

            result = Math.max(result, maxSoFar);
        }

        return result;          
    }
}
