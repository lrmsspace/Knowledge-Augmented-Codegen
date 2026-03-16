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
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It provides logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update individual elements and calculate prefix sums in an array. Both operations are performed in O(log N) time.
//   • Invariants: Each `tree[i]` element stores the sum of a contiguous range of elements from the original array, specifically from `i - (i & -i) + 1` to `i` (inclusive, 1-based).; After any `update(idx, val)` operation, `query(idx)` will reflect the new sum up to `idx`.
//   • Tips: Use 1-based indexing for array elements to simplify bitwise logic; The `idx & -idx` operation is key to navigating the implicit tree structure
//   • Pitfalls: Confusing 0-based and 1-based indexing can lead to incorrect results; Off-by-one errors when calculating range sums (e.g., `query(R) - query(L-1)`)
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: When you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It is ideal for scenarios requiring both fast query and update operations on an array.
//   • Idea: A Fenwick tree, or Binary Indexed Tree (BIT), is an array-based data structure that efficiently calculates prefix sums and updates individual elements in an array. It supports both point updates and prefix sum queries in O(log N) time complexity.
//   • Invariants: Each `T[i]` stores the sum of a specific range `[g(i), i]` from the original array.; The `sum(idx)` function correctly aggregates values from `A[0]` to `A[idx]`.
//   • Tips: Understand the bit manipulation (`i & -i`) for navigating parent/child relationships.; Consistently choose and apply either 0-based or 1-based indexing throughout the implementation.
//   • Pitfalls: Incorrectly handling 0-based versus 1-based indexing can lead to off-by-one errors.; Forgetting to initialize the tree or performing updates incorrectly will yield wrong results.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minMoves(int[] nums, int k) {
        List<Integer> ones = new ArrayList<>();
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == 1) {
                ones.add(i);
            }
        }

        int n = ones.size();
        int[] prefixSum = new int[n + 1];
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + ones.get(i);
        }

        int minMoves = Integer.MAX_VALUE;
        for (int i = 0; i <= n - k; i++) {
            int mid = i + k / 2;
            int medianPos = ones.get(mid);
            int leftCost = medianPos * (mid - i) - (prefixSum[mid] - prefixSum[i]);
            int rightCost = (prefixSum[i + k] - prefixSum[mid + 1]) - medianPos * (i + k - mid - 1);
            minMoves = Math.min(minMoves, leftCost + rightCost);
        }

        return minMoves;            
    }
}
