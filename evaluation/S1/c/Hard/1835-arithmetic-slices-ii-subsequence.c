// Source: https://leetcode.com/problems/arithmetic-slices-ii-subsequence/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the number of all the arithmetic subsequences of nums.
//
// A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
//
//
// 	For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.
// 	For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.
//
//
// A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.
//
//
// 	For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
//
//
// The test cases are generated so that the answer fits in 32-bit integer.
//
// Example:
// Input: nums = [2,4,6,8,10]
// Output: 7
// Explanation: All arithmetic subsequence slices are:
// [2,4,6]
// [4,6,8]
// [6,8,10]
// [2,4,6,8]
// [4,6,8,10]
// [2,4,6,8,10]
// [2,6,10]
//
// Constraints:
// 1  <= nums.length <= 1000
// 	-231 <= nums[i] <= 231 - 1
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
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

int numberOfArithmeticSlices(int* nums, int numsSize) {
    if (numsSize < 3) return 0;

    int total = 0;
    /* dp[i]: array of (difference -> count of subsequences ending at i with that difference) */
    typedef struct DiffCount {
        long long diff;
        int count;
        struct DiffCount *next;
    } DiffCount;

    DiffCount **dp = (DiffCount**)calloc(numsSize, sizeof(DiffCount*));
    if (!dp) return 0;

    for (int i = 0; i < numsSize; ++i) {
        for (int j = 0; j < i; ++j) {
            long long diff = (long long)nums[i] - (long long)nums[j];
            /* Find count of subsequences ending at j with this difference */
            int countAtJ = 0;
            DiffCount *curr = dp[j];
            while (curr) {
                if (curr->diff == diff) {
                    countAtJ = curr->count;
                    break;
                }
                curr = curr->next;
            }
            /* Update dp[i] */
            DiffCount *newNode = (DiffCount*)malloc(sizeof(DiffCount));
            if (!newNode) {
                /* Free allocated memory before returning */
                for (int k = 0; k < numsSize; ++k) {
                    DiffCount *node = dp[k];
                    while (node) {
                        DiffCount *tmp = node->next;
                        free(node);
                        node = tmp;
                    }
                }
                free(dp);
                return 0;
            }
            newNode->diff = diff;
            newNode->count = countAtJ + 1; /* +1 for the pair (nums[j], nums[i]) */
            newNode->next = dp[i];
            dp[i] = newNode;

            total += countAtJ; /* Only subsequences of length >= 3 contribute to total */
        }
    }

    /* Free allocated memory */
    for (int i = 0; i < numsSize; ++i) {
        DiffCount *node = dp[i];
        while (node) {
            DiffCount *tmp = node->next;
            free(node);
            node = tmp;
        }
    }
    free(dp);

    return total;       
}
