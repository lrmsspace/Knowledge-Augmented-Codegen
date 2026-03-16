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
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* minOperations(int* nums, int numsSize, int* queries, int queriesSize, int* returnSize){
    // Helper function to perform merge sort
    void merge(int* arr, int left, int mid, int right, long long* prefixSum) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int* L = (int*)malloc(n1 * sizeof(int));
        int* R = (int*)malloc(n2 * sizeof(int));

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }

        while (i < n1) {
            arr[k++] = L[i++];
        }

        while (j < n2) {
            arr[k++] = R[j++];
        }

        free(L);
        free(R);
    }

    void mergeSort(int* arr, int left, int right, long long* prefixSum) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid, prefixSum);
            mergeSort(arr, mid + 1, right, prefixSum);
            merge(arr, left, mid, right, prefixSum);
        }
    }

    // Sort nums array
    mergeSort(nums, 0, numsSize - 1, NULL);

    // Create prefix sum array
    long long* prefixSum = (long long*)malloc((numsSize + 1) * sizeof(long long));
    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    // Prepare result array
    long long* result = (long long*)malloc(queriesSize * sizeof(long long));
    *returnSize = queriesSize;

    // Process each query
    for (int q = 0; q < queriesSize; q++) {
        int target = queries[q];

        // Binary search to find the partition index
        int left = 0, right = numsSize - 1, partitionIndex = numsSize;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                partitionIndex = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        // Calculate operations
        long long leftOperations = (long long)target * partitionIndex - prefixSum[partitionIndex];
        long long rightOperations = (prefixSum[numsSize] - prefixSum[partitionIndex]) - (long long)target * (numsSize - partitionIndex);
        result[q] = leftOperations + rightOperations;
    }
    free(prefixSum);
    return result;
}
