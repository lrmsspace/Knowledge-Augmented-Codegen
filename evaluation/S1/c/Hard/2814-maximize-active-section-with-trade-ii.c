// Source: https://leetcode.com/problems/maximize-active-section-with-trade-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s of length n, where:
//
//
//  '1' represents an active section.
//  '0' represents an inactive section.
//
//
// You can perform at most one trade to maximize the number of active sections in s. In a trade, you:
//
//
//  Convert a contiguous block of '1's that is surrounded by '0's to all '0's.
//  Afterward, convert a contiguous block of '0's that is surrounded by '1's to all '1's.
//
//
// Additionally, you are given a 2D array queries, where queries[i] = [li, ri] represents a substring s[li...ri].
//
// For each query, determine the maximum possible number of active sections in s after making the optimal trade on the substring s[li...ri].
//
// Return an array answer, where answer[i] is the result for queries[i].
//
// Note
//
//
//  For each query, treat s[li...ri] as if it is augmented with a '1' at both ends, forming t = '1' + s[li...ri] + '1'. The augmented '1's do not contribute to the final count.
//  The queries are independent of each other.
//
// Example:
// Input: s = "01", queries = [[0,1]]
//
// Output: [1]
//
// Explanation:
//
// Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.
//
// Constraints:
// 1 <= n == s.length <= 105
//  1 <= queries.length <= 105
//  s[i] is either '0' or '1'.
//  queries[i] = [li, ri]
//  0 <= li <= ri < n
//
// Helpful references (internal KB):
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
//   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
//   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
//   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
//   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
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
int* maxActiveSectionsAfterTrade(char* s, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int n = strlen(s);
    int* prefixOnes = (int*)malloc((n + 1) * sizeof(int));
    prefixOnes[0] = 0;
    for (int i = 0; i < n; ++i) {
        prefixOnes[i + 1] = prefixOnes[i] + (s[i] == '1' ? 1 : 0);
    }

    int* result = (int*)malloc(queriesSize * sizeof(int));
    for (int q = 0; q < queriesSize; ++q) {
        int l = queries[q][0];
        int r = queries[q][1];

        int totalOnes = prefixOnes[r + 1] - prefixOnes[l];

        int maxGain = 0;
        int currentGain = 0;
        for (int i = l; i <= r; ++i) {
            if (s[i] == '0') {
                currentGain += 1;
            } else {
                currentGain -= 1;
            }
            if (currentGain < 0) {
                currentGain = 0;
            }
            if (currentGain > maxGain) {
                maxGain = currentGain;
            }
        }

        result[q] = totalOnes + maxGain;
    }

    free(prefixOnes);
    *returnSize = queriesSize;
    return result;      
}
