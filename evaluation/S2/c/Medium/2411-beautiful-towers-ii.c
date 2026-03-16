// Source: https://leetcode.com/problems/beautiful-towers-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array maxHeights of n integers.
//
// You are tasked with building n towers in the coordinate line. The ith tower is built at coordinate i and has a height of heights[i].
//
// A configuration of towers is beautiful if the following conditions hold:
//
//
// 	1 <= heights[i] <= maxHeights[i]
// 	heights is a mountain array.
//
//
// Array heights is a mountain if there exists an index i such that:
//
//
// 	For all 0 < j <= i, heights[j - 1] <= heights[j]
// 	For all i <= k < n - 1, heights[k + 1] <= heights[k]
//
//
// Return the maximum possible sum of heights of a beautiful configuration of towers.
//
// Example:
// Input: maxHeights = [5,3,4,1,1]
// Output: 13
// Explanation: One beautiful configuration with a maximum sum is heights = [5,3,3,1,1]. This configuration is beautiful since:
// - 1 <= heights[i] <= maxHeights[i]  
// - heights is a mountain of peak i = 0.
// It can be shown that there exists no other beautiful configuration with a sum of heights greater than 13.
//
// Constraints:
// 1 <= n == maxHeights.length <= 105
// 	1 <= maxHeights[i] <= 109
//
// Helpful references (internal KB):
// - Convex hull trick and Li Chao tree (array, number, dp-1d)
//   • When to use: Use when the optimal solution for a subproblem depends only on solutions to smaller, contiguous subproblems. It's effective for optimizing sequential decision-making or finding optimal values in arrays.
//   • Idea: Dynamic Programming 1D solves problems by breaking them into overlapping subproblems and storing results to avoid recomputation. It typically achieves O(N) or O(N log N) time and O(N) or O(1) space complexity.
//   • Invariants: dp[i] correctly stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been computed and are correct.
//   • Tips: Clearly define the state: what does dp[i] represent for the subproblem?; Establish correct base cases for the smallest subproblems.
//   • Pitfalls: Incorrectly defining the state or recurrence relation.; Missing or incorrect base cases, leading to incorrect results.
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
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

long long maximumSumOfHeights(int* maxHeights, int maxHeightsSize) {
    int n = maxHeightsSize;
    long long ans = 0;
    long long* left = (long long*)malloc(n * sizeof(long long));
    long long* right = (long long*)malloc(n * sizeof(long long));
    left[0] = maxHeights[0];
    for (int i = 1; i < n; ++i) {
        left[i] = maxHeights[i] < left[i - 1] ? maxHeights[i] : left[i - 1];
    }
    right[n - 1] = maxHeights[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        right[i] = maxHeights[i] < right[i + 1] ? maxHeights[i] : right[i + 1];
    }
    for (int i = 0; i < n; ++i) {
        ans += left[i] < right[i] ? left[i] : right[i];
    }
    free(left);
    free(right);
    return ans;
}
