// Source: https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers, x and k. You can perform the following operation any number of times (including zero):
//
//
// 	Increase or decrease any element of nums by 1.
//
//
// Return the minimum number of operations needed to have at least k non-overlapping subarrays of size exactly x in nums, where all elements within each subarray are equal.
//
// Example:
// Input: nums = [5,-2,1,3,7,3,6,4,-1], x = 3, k = 2
//
// Output: 8
//
// Explanation:
//
//
// 	Use 3 operations to add 3 to nums[1] and use 2 operations to subtract 2 from nums[3]. The resulting array is [5, 1, 1, 1, 7, 3, 6, 4, -1].
// 	Use 1 operation to add 1 to nums[5] and use 2 operations to subtract 2 from nums[6]. The resulting array is [5, 1, 1, 1, 7, 4, 4, 4, -1].
// 	Now, all elements within each subarray [1, 1, 1] (from indices 1 to 3) and [4, 4, 4] (from indices 5 to 7) are equal. Since 8 total operations were used, 8 is the output.
//
// Constraints:
// 2 <= nums.length <= 105
// 	-106 <= nums[i] <= 106
// 	2 <= x <= nums.length
// 	1 <= k <= 15
// 	2 <= k * x <= nums.length
//
// Helpful references (internal KB):
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting a subset of items, each with a weight and value, to maximize total value without exceeding a given capacity. It is applicable for resource allocation problems with discrete choices.
//   • Idea: The Knapsack Problem aims to choose items with maximum total value such that their total weight does not exceed a given capacity. It is typically solved using dynamic programming, achieving a time complexity of O(nW) for n items and capacity W.
//   • Invariants: `dp[j]` (in 1D DP) represents the maximum value achievable with capacity `j` using items considered so far.; When processing item `i` and capacity `j` (decreasing `j`), `dp[j-weight_i]` holds the value from previous items for that reduced capacity.
//   • Tips: Initialize DP table with zeros for capacity 0 and unreachable states.; For 0-1 knapsack with 1D DP, iterate capacity `j` in decreasing order.
//   • Pitfalls: Incorrect iteration order for 1D DP in 0-1 knapsack (using increasing `j`).; Off-by-one errors in item indices or capacity calculations.
// - Priority Queues (array, heap, heap-select)
//   • When to use: Use when an in-place sorting algorithm with O(N log N) worst-case time complexity is required, especially when memory constraints are a concern. It's also applicable for efficiently finding the K largest/smallest elements.
//   • Idea: Heapsort is an in-place comparison-based sorting algorithm that uses a binary heap data structure. It first builds a max-heap from the input array, then repeatedly extracts the maximum element and places it at the end of the array, achieving O(N log N) time complexity.
//   • Invariants: During heap construction, the processed subarray forms a valid heap-ordered complete binary tree.; During sortdown, the elements in `arr[0...i]` form a valid heap, and `arr[i+1...N-1]` contains sorted elements.
//   • Tips: Heap construction can be done in linear time using a bottom-up sink-based approach.; Heapsort is an in-place sorting algorithm, requiring O(1) auxiliary space.
//   • Pitfalls: Heapsort is not a stable sorting algorithm; the relative order of equal elements is not preserved.; Cache performance can be poor due to non-sequential memory access patterns during heap operations.
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
    private long[] computeCost(int[] nums, int start, int x) {
        int[] subarray = new int[x];
        System.arraycopy(nums, start, subarray, 0, x);
        Arrays.sort(subarray);
        int median = subarray[x / 2];
        long totalCost = 0;
        for (int num : subarray) {
            totalCost += Math.abs(num - median);
        }
        return new long[]{totalCost};
    }
    public long minOperations(int[] nums, int x, int k) {
        int n = nums.length;
        long[][] cost = new long[n - x + 1][];
        for (int i = 0; i <= n - x; i++) {
            cost[i] = computeCost(nums, i, x);
        }

        long[][] dp = new long[k + 1][n + 1];
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = Long.MAX_VALUE / 2;
            }
        }
        dp[0][0] = 0;

        for (int i = 1; i <= k; i++) {
            for (int j = x; j <= n; j++) {
                dp[i][j] = dp[i][j - 1];
                if (j - x >= 0 && dp[i - 1][j - x] != Long.MAX_VALUE / 2) {
                    dp[i][j] = Math.min(dp[i][j], dp[i - 1][j - x] + cost[j - x][0]);
                }
            }
        }

        return dp[k][n];            
    }
}
