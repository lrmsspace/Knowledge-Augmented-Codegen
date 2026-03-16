// Source: https://leetcode.com/problems/make-array-strictly-increasing/   |   Difficulty: Hard
//
// Problem Description:
// Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.
//
// In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].
//
// If there is no way to make arr1 strictly increasing, return -1.
//
// Example:
// Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
// Output: 1
// Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].
//
// Constraints:
// 1 <= arr1.length, arr2.length <= 2000
// 	0 <= arr1[i], arr2[i] <= 10^9
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int makeArrayIncreasing(int* arr1, int arr1Size, int* arr2, int arr2Size) {
    /* Remove duplicates from arr2 and sort it */
    int *arr2Unique = (int*)malloc(arr2Size * sizeof(int));
    if (!arr2Unique) return -1;
    memcpy(arr2Unique, arr2, arr2Size * sizeof(int));
    qsort(arr2Unique, arr2Size, sizeof(int), cmpInt);
    int uniqueSize = 0;
    for (int i = 0; i < arr2Size; ++i) {
        if (i == 0 || arr2Unique[i] != arr2Unique[i - 1]) {
            arr2Unique[uniqueSize++] = arr2Unique[i];
        }
    }

    /* DP array: dp[i] = minimum operations to make arr1[0..i] strictly increasing */
    int *dp = (int*)malloc((arr1Size + 1) * sizeof(int));
    if (!dp) { free(arr2Unique); return -1; }
    for (int i = 0; i <= arr1Size; ++i) dp[i] = -1;
    dp[0] = 0;

    for (int i = 0; i < arr1Size; ++i) {
        int *newDp = (int*)malloc((arr1Size + 1) * sizeof(int));
        if (!newDp) { free(arr2Unique); free(dp); return -1; }
        for (int j = 0; j <= arr1Size; ++j) newDp[j] = -1;

        for (int j = 0; j <= i; ++j) {
            if (dp[j] == -1) continue;

            /* Case 1: Keep arr1[i] if it's greater than the last kept element */
            if (j == 0 || arr1[i] > arr1[i - 1]) {
                if (newDp[j] == -1 || newDp[j] > dp[j]) {
                    newDp[j] = dp[j];
                }
            }

            /* Case 2: Replace arr1[i] with the smallest element in arr2Unique that is greater than the last kept element */
            int last = (j == 0) ? INT_MIN : arr1[i - 1];
            int idx = upperBound(arr2Unique, uniqueSize, last);
            if (idx < uniqueSize) {
                if (newDp[j + 1] == -1 || newDp[j + 1] > dp[j] + 1) {
                    newDp[j + 1] = dp[j] + 1;
                }
            }
        }

        free(dp);
        dp = newDp;
    }
    int result = -1;
    for (int i = 0; i <= arr1Size; ++i) {
        if (dp[i] != -1) {
            if (result == -1 || dp[i] < result) {
                result = dp[i];
            }
        }
    }
    free(dp);
    free(arr2Unique);
    return result;
}
