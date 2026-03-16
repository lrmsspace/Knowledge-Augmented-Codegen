// Source: https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array, nums, and an integer k. nums comprises of only 0's and 1's. In one move, you can choose two adjacent indices and swap their values.
//
// Return the minimum number of moves required so that nums has k consecutive 1's.
//
// Example:
// Input: nums = [1,0,0,1,0,1], k = 2
// Output: 1
// Explanation: In 1 move, nums could be [1,0,0,0,1,1] and have 2 consecutive 1's.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is 0 or 1.
// 	1 <= k <= sum(nums)
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minMoves(int[] nums, int k) {
        int n = nums.length;
        List<Integer> ones = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) {
                ones.add(i);
            }
        }

        int m = ones.size();
        int[] prefixSum = new int[m + 1];
        for (int i = 0; i < m; i++) {
            prefixSum[i + 1] = prefixSum[i] + ones.get(i);
        }

        int minMoves = Integer.MAX_VALUE;
        for (int i = 0; i <= m - k; i++) {
            int mid = i + k / 2;
            int medianPos = ones.get(mid);
            int leftCost = medianPos * (mid - i) - (prefixSum[mid] - prefixSum[i]);
            int rightCost = (prefixSum[i + k] - prefixSum[mid + 1]) - medianPos * (i + k - mid - 1);
            minMoves = Math.min(minMoves, leftCost + rightCost);
        }

        return minMoves;            
    }
}
