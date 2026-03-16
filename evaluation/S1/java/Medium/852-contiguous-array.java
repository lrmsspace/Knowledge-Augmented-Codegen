// Source: https://leetcode.com/problems/contiguous-array/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
//
// Example:
// Input: nums = [0,1]
// Output: 2
// Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
//   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
//   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
//   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
//   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int findMaxLength(int[] nums) {
        // Transform 0s to -1s to use prefix sum technique
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == 0) {
                nums[i] = -1;
            }
        }

        // HashMap to store the first occurrence of each prefix sum
        java.util.Map<Integer, Integer> prefixSumIndexMap = new java.util.HashMap<>();
        prefixSumIndexMap.put(0, -1); // Base case: prefix sum 0 at index -1

        int maxLength = 0;
        int prefixSum = 0;

        for (int i = 0; i < nums.length; i++) {
            prefixSum += nums[i];

            if (prefixSumIndexMap.containsKey(prefixSum)) {
                // Calculate the length of the subarray
                int prevIndex = prefixSumIndexMap.get(prefixSum);
                int currentLength = i - prevIndex;
                maxLength = Math.max(maxLength, currentLength);
            } else {
                // Store the first occurrence of this prefix sum
                prefixSumIndexMap.put(prefixSum, i);
            }
        }

        return maxLength;           
    }
}
