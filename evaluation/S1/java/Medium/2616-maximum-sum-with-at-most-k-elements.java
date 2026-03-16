// Source: https://leetcode.com/problems/maximum-sum-with-at-most-k-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, an integer array limits of length n, and an integer k. The task is to find the maximum sum of at most k elements from the matrix grid such that:
//
//
// 	
// 	The number of elements taken from the ith row of grid does not exceed limits[i].
// 	
//
//
// Return the maximum sum.
//
// Example:
// Input: grid = [[1,2],[3,4]], limits = [1,2], k = 2
//
// Output: 7
//
// Explanation:
//
//
// 	From the second row, we can take at most 2 elements. The elements taken are 4 and 3.
// 	The maximum possible sum of at most 2 selected elements is 4 + 3 = 7.
//
// Constraints:
// n == grid.length == limits.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	0 <= grid[i][j] <= 105
// 	0 <= limits[i] <= m
// 	0 <= k <= min(n * m, sum(limits))
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long maxSum(int[][] grid, int[] limits, int k) {
        int n = grid.length;
        int m = grid[0].length;

        // Step 1: Calculate prefix sums for each row
        long[][] prefixSums = new long[n][m + 1];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                prefixSums[i][j + 1] = prefixSums[i][j] + grid[i][j];
            }
        }

        // Step 2: Initialize DP array
        long[] dp = new long[k + 1];

        // Step 3: Fill DP array
        for (int i = 0; i < n; i++) {
            long[] newDp = new long[k + 1];
            System.arraycopy(dp, 0, newDp, 0, k + 1);

            for (int taken = 0; taken <= Math.min(limits[i], m); taken++) {
                long rowSum = prefixSums[i][taken];

                for (int j = k; j >= taken; j--) {
                    newDp[j] = Math.max(newDp[j], dp[j - taken] + rowSum);
                }
            }

            dp = newDp;
        }

        return dp[k];           
    }
}
