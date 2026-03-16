// Source: https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// A sequence x1, x2, ..., xn is Fibonacci-like if:
//
//
// 	n >= 3
// 	xi + xi+1 == xi+2 for all i + 2 <= n
//
//
// Given a strictly increasing array arr of positive integers forming a sequence, return the length of the longest Fibonacci-like subsequence of arr. If one does not exist, return 0.
//
// A subsequence is derived from another sequence arr by deleting any number of elements (including none) from arr, without changing the order of the remaining elements. For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].
//
// Example:
// Input: arr = [1,2,3,4,5,6,7,8]
// Output: 5
// Explanation: The longest subsequence that is fibonacci-like: [1,2,3,5,8].
//
// Constraints:
// 3 <= arr.length <= 1000
// 	1 <= arr[i] < arr[i + 1] <= 109
//
// Helpful references (internal KB):
// - Fibonacci Numbers (array, dp-1d)
//   • When to use: Use this when calculating the n-th Fibonacci number or similar sequences where each term depends on a fixed number of preceding terms. It efficiently avoids redundant computations for moderate 'n' values.
//   • Idea: This algorithm calculates Fibonacci numbers iteratively by storing previously computed values in an array, building up to the desired n-th term. This approach achieves O(N) time complexity and O(N) space complexity.
//   • Invariants: dp[i] correctly stores the i-th Fibonacci number.; For i >= 2, dp[i] is computed as the sum of dp[i-1] and dp[i-2].
//   • Tips: Initialize base cases (F0, F1) correctly to start the sequence.; Use an array or two variables to store only the necessary previous terms.
//   • Pitfalls: Incorrectly initializing the base cases can lead to wrong results.; A naive recursive solution without memoization will lead to exponential time complexity.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int lenLongestFibSubseq(int* arr, int arrSize) {
    int index[10000] = {0};
    for (int i = 0; i < arrSize; ++i) {
        index[arr[i]] = i + 1;
    }

    int dp[1000][1000];
    int max_len = 0;

    for (int i = 0; i < arrSize; ++i) {
        for (int j = 0; j < i; ++j) {
            int prev = arr[i] - arr[j];
            if (prev >= arr[j]) {
                dp[j][i] = 2;
            } else {
                int k = index[prev] - 1;
                if (k >= 0) {
                    dp[j][i] = dp[k][j] + 1;
                } else {
                    dp[j][i] = 2;
                }
            }
            if (dp[j][i] > max_len) {
                max_len = dp[j][i];
            }
        }
    }

    return max_len >= 3 ? max_len : 0;      
}
