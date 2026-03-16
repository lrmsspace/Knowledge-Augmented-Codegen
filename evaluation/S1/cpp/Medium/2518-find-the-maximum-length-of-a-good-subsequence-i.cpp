// Source: https://leetcode.com/problems/find-the-maximum-length-of-a-good-subsequence-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a non-negative integer k. A sequence of integers seq is called good if there are at most k indices i in the range [0, seq.length - 2] such that seq[i] != seq[i + 1].
//
// Return the maximum possible length of a good subsequence of nums.
//
// Example:
// Input: nums = [1,2,1,1,3], k = 2
//
// Output: 4
//
// Explanation:
//
// The maximum length subsequence is [1,2,1,1,3].
//
// Constraints:
// 1 <= nums.length <= 500
// 	1 <= nums[i] <= 109
// 	0 <= k <= min(nums.length, 25)
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size();
        // dp[i][j]: max length of good subsequence using first i elements with j changes
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                // Option 1: Exclude nums[i-1]
                dp[i][j] = dp[i - 1][j];
                // Option 2: Include nums[i-1]
                if (i == 1) {
                    // First element, no previous to compare
                    dp[i][j] = max(dp[i][j], 1);
                } else {
                    if (nums[i - 1] == nums[i - 2]) {
                        // Same as previous, no change needed
                        dp[i][j] = max(dp[i][j], dp[i - 1][j] + 1);
                    } else {
                        // Different from previous
                        if (j > 0) {
                            // Use a change to include this element
                            dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
                        }
                    }
                }
            }
        }
        return dp[n][k];            
    }
};
