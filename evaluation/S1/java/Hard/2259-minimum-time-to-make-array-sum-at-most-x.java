// Source: https://leetcode.com/problems/minimum-time-to-make-array-sum-at-most-x/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2 of equal length. Every second, for all indices 0 <= i < nums1.length, value of nums1[i] is incremented by nums2[i]. After this is done, you can do the following operation:
//
//
//  Choose an index 0 <= i < nums1.length and make nums1[i] = 0.
//
//
// You are also given an integer x.
//
// Return the minimum time in which you can make the sum of all elements of nums1 to be less than or equal to x, or -1 if this is not possible.
//
// Example:
// Input: nums1 = [1,2,3], nums2 = [1,2,3], x = 4
// Output: 3
// Explanation: 
// For the 1st second, we apply the operation on i = 0. Therefore nums1 = [0,2+2,3+3] = [0,4,6]. 
// For the 2nd second, we apply the operation on i = 1. Therefore nums1 = [0+1,0,6+3] = [1,0,9]. 
// For the 3rd second, we apply the operation on i = 2. Therefore nums1 = [1+1,0+2,0] = [2,2,0]. 
// Now sum of nums1 = 4. It can be shown that these operations are optimal, so we return 3.
//
// Constraints:
// 1 <= nums1.length <= 103
//  1 <= nums1[i] <= 103
//  0 <= nums2[i] <= 103
//  nums1.length == nums2.length
//  0 <= x <= 106
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumTime(List<Integer> nums1, List<Integer> nums2, int x) {
        int n = nums1.size();
        int left = 0, right = (int)1e6, answer = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canAchieve(nums1, nums2, x, mid)) {
                answer = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return answer;          
    }
}
