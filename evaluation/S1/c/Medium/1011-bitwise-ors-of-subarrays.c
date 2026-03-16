// Source: https://leetcode.com/problems/bitwise-ors-of-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty subarrays of arr.
//
// The bitwise OR of a subarray is the bitwise OR of each integer in the subarray. The bitwise OR of a subarray of one integer is that integer.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: arr = [0]
// Output: 1
// Explanation: There is only one possible result: 0.
//
// Constraints:
// 1 <= arr.length <= 5 * 104
// 	0 <= arr[i] <= 109
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int subarrayBitwiseORs(int* arr, int arrSize) {
    // Use a hash set to store unique bitwise OR results
    #define MAX_BITS 32
    int resultSet[1 << MAX_BITS];
    int resultCount = 0;

    // Temporary array to store current subarray OR results
    int currentSet[1 << MAX_BITS];
    int currentCount = 0;

    for (int i = 0; i < arrSize; i++) {
        // Start a new set for the current element
        int newCurrentSet[1 << MAX_BITS];
        int newCurrentCount = 0;

        // Add the current element itself
        newCurrentSet[newCurrentCount++] = arr[i];

        // Combine with previous subarray OR results
        for (int j = 0; j < currentCount; j++) {
            int orResult = currentSet[j] | arr[i];
            // Check if this OR result is already in newCurrentSet
            int found = 0;
            for (int k = 0; k < newCurrentCount; k++) {
                if (newCurrentSet[k] == orResult) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                newCurrentSet[newCurrentCount++] = orResult;
            }
        }

        // Update currentSet to newCurrentSet
        for (int j = 0; j < newCurrentCount; j++) {
            currentSet[j] = newCurrentSet[j];
        }
        currentCount = newCurrentCount;

        // Add currentSet results to resultSet
        for (int j = 0; j < currentCount; j++) {
            int found = 0;
            for (int k = 0; k < resultCount; k++) {
                if (resultSet[k] == currentSet[j]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                resultSet[resultCount++] = currentSet[j];
            }
        }
    }

    return resultCount;     
}
