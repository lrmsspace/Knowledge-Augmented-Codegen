// Source: https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, find three non-overlapping subarrays of length k with maximum sum and return them.
//
// Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.
//
// Example:
// Input: nums = [1,2,1,2,6,7,5,1], k = 2
// Output: [0,3,5]
// Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
// We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] < 216
// 	1 <= k <= floor(nums.length / 3)
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
//   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
//   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
//   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
//   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSumOfThreeSubarrays(int* nums, int numsSize, int k, int* returnSize) {
    int prefixSum[numsSize + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int leftMax[numsSize];
    int maxSum = prefixSum[k] - prefixSum[0];
    leftMax[k - 1] = 0;
    for (int i = k; i < numsSize; i++) {
        int currentSum = prefixSum[i + 1] - prefixSum[i + 1 - k];
        if (currentSum > maxSum) {
            maxSum = currentSum;
            leftMax[i] = i + 1 - k;
        } else {
            leftMax[i] = leftMax[i - 1];
        }
    }

    int rightMax[numsSize];
    maxSum = prefixSum[numsSize] - prefixSum[numsSize - k];
    rightMax[numsSize - k] = numsSize - k;
    for (int i = numsSize - k - 1; i >= 0; i--) {
        int currentSum = prefixSum[i + k] - prefixSum[i];
        if (currentSum >= maxSum) {
            maxSum = currentSum;
            rightMax[i] = i;
        } else {
            rightMax[i] = rightMax[i + 1];
        }
    }

    int* result = (int*)malloc(3 * sizeof(int));
    *returnSize = 3;
    maxSum = 0;
    for (int mid = k; mid <= numsSize - 2 * k; mid++) {
        int left = leftMax[mid - 1];
        int right = rightMax[mid + k];
        int totalSum = (prefixSum[left + k] - prefixSum[left]) +
                       (prefixSum[mid + k] - prefixSum[mid]) +
                       (prefixSum[right + k] - prefixSum[right]);
        if (totalSum > maxSum) {
            maxSum = totalSum;
            result[0] = left;
            result[1] = mid;
            result[2] = right;
        }
    }

    return result;      
}
