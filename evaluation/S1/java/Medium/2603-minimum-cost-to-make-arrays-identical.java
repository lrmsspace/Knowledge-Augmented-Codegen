// Source: https://leetcode.com/problems/minimum-cost-to-make-arrays-identical/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays arr and brr of length n, and an integer k. You can perform the following operations on arr any number of times:
//
//
// 	Split arr into any number of contiguous subarrays and rearrange these subarrays in any order. This operation has a fixed cost of k.
// 	
// 	Choose any element in arr and add or subtract a positive integer x to it. The cost of this operation is x.
// 	
//
//
// Return the minimum total cost to make arr equal to brr.
//
// Example:
// Input: arr = [-7,9,5], brr = [7,-2,-5], k = 2
//
// Output: 13
//
// Explanation:
//
//
// 	Split arr into two contiguous subarrays: [-7] and [9, 5] and rearrange them as [9, 5, -7], with a cost of 2.
// 	Subtract 2 from element arr[0]. The array becomes [7, 5, -7]. The cost of this operation is 2.
// 	Subtract 7 from element arr[1]. The array becomes [7, -2, -7]. The cost of this operation is 7.
// 	Add 2 to element arr[2]. The array becomes [7, -2, -5]. The cost of this operation is 2.
//
//
// The total cost to make the arrays equal is 2 + 2 + 7 + 2 = 13.
//
// Constraints:
// 1 <= arr.length == brr.length <= 105
// 	0 <= k <= 2 * 1010
// 	-105 <= arr[i] <= 105
// 	-105 <= brr[i] <= 105
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Elementary Sorts (array, enumeration)
//   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
//   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
//   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
//   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
//   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
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
    public long minCost(int[] arr, int[] brr, long k) {
        int n = arr.length;
        long[][] dp = new long[n][n];
        for (int len = 1; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                if (len == 1) {
                    dp[l][r] = Math.abs(arr[l] - brr[l]);
                } else {
                    dp[l][r] = Long.MAX_VALUE;
                    for (int m = l; m < r; m++) {
                        dp[l][r] = Math.min(dp[l][r], dp[l][m] + dp[m + 1][r] + k);
                    }
                    long cost = 0;
                    for (int i = l; i <= r; i++) {
                        cost += Math.abs(arr[i] - brr[i]);
                    }
                    dp[l][r] = Math.min(dp[l][r], cost);
                }
            }
        }
        return dp[0][n - 1];            
    }
}
