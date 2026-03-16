// Source: https://leetcode.com/problems/minimum-operations-to-make-all-array-elements-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// You are also given an integer array queries of size m. For the ith query, you want to make all of the elements of nums equal to queries[i]. You can perform the following operation on the array any number of times:
//
//
// 	Increase or decrease an element of the array by 1.
//
//
// Return an array answer of size m where answer[i] is the minimum number of operations to make all elements of nums equal to queries[i].
//
// Note that after each query the array is reset to its original state.
//
// Example:
// Input: nums = [3,1,6,8], queries = [1,5]
// Output: [14,10]
// Explanation: For the first query we can do the following operations:
// - Decrease nums[0] 2 times, so that nums = [1,1,6,8].
// - Decrease nums[2] 5 times, so that nums = [1,1,1,8].
// - Decrease nums[3] 7 times, so that nums = [1,1,1,1].
// So the total number of operations for the first query is 2 + 5 + 7 = 14.
// For the second query we can do the following operations:
// - Increase nums[0] 2 times, so that nums = [5,1,6,8].
// - Increase nums[1] 4 times, so that nums = [5,5,6,8].
// - Decrease nums[2] 1 time, so that nums = [5,5,5,8].
// - Decrease nums[3] 3 times, so that nums = [5,5,5,5].
// So the total number of operations for the second query is 2 + 4 + 1 + 3 = 10.
//
// Constraints:
// n == nums.length
// 	m == queries.length
// 	1 <= n, m <= 105
// 	1 <= nums[i], queries[i] <= 109
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - MEX (minimal excluded) of a sequence (tree, binary-search)
//   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
//   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
//   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
//   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
//   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Long> minOperations(int[] nums, int[] queries) {
        Arrays.sort(nums);
        int n = nums.length;
        long[] prefixSum = new long[n + 1];
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        List<Long> result = new ArrayList<>();
        for (int query : queries) {
            int index = Arrays.binarySearch(nums, query);
            if (index < 0) {
                index = -(index + 1);
            }

            long leftOperations = (long) query * index - prefixSum[index];
            long rightOperations = (prefixSum[n] - prefixSum[index]) - (long) query * (n - index);
            result.add(leftOperations + rightOperations);
        }

        return result;          
    }
}
