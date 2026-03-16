// Source: https://leetcode.com/problems/longest-turbulent-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr, return the length of a maximum size turbulent subarray of arr.
//
// A subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.
//
// More formally, a subarray [arr[i], arr[i + 1], ..., arr[j]] of arr is said to be turbulent if and only if:
//
//
// 	For i <= k < j:
//
// 	
// 		arr[k] > arr[k + 1] when k is odd, and
// 		arr[k] < arr[k + 1] when k is even.
// 	
// 	
// 	Or, for i <= k < j:
// 	
// 		arr[k] > arr[k + 1] when k is even, and
// 		arr[k] < arr[k + 1] when k is odd.
//
// Example:
// Input: arr = [9,4,2,10,7,8,8,1,9]
// Output: 5
// Explanation: arr[1] > arr[2] < arr[3] > arr[4] < arr[5]
//
// Constraints:
// 1 <= arr.length <= 4 * 104
// 	0 <= arr[i] <= 109
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
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

int maxTurbulenceSize(int* arr, int arrSize) {
    if (arrSize < 2) {
        return arrSize;
    }

    int max_len = 1;
    int curr_len = 1;
    int prev_cmp = 0; // 0: equal, 1: greater, -1: less

    for (int i = 1; i < arrSize; i++) {
        int curr_cmp = 0;
        if (arr[i] > arr[i - 1]) {
            curr_cmp = 1;
        } else if (arr[i] < arr[i - 1]) {
            curr_cmp = -1;
        }

        if (curr_cmp == 0) {
            curr_len = 1;
        } else if (curr_cmp != prev_cmp) {
            curr_len++;
        } else {
            curr_len = 2; // reset to length 2 (current and previous)
        }

        max_len = (curr_len > max_len) ? curr_len : max_len;
        prev_cmp = curr_cmp;
    }

    return max_len;     
}
