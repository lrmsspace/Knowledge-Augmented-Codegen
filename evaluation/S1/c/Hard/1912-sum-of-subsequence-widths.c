// Source: https://leetcode.com/problems/sum-of-subsequence-widths/   |   Difficulty: Hard
//
// Problem Description:
// The width of a sequence is the difference between the maximum and minimum elements in the sequence.
//
// Given an array of integers nums, return the sum of the widths of all the non-empty subsequences of nums. Since the answer may be very large, return it modulo 109 + 7.
//
// A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements. For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].
//
// Example:
// Input: nums = [2,1,3]
// Output: 6
// Explanation: The subsequences are [1], [2], [3], [2,1], [2,3], [1,3], [2,1,3].
// The corresponding widths are 0, 0, 0, 1, 1, 2, 2.
// The sum of these widths is 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort)
//   • When to use: Use when a stable, guaranteed O(N log N) time complexity sort is required, especially for large datasets or when external sorting is beneficial. It is also suitable for linked lists where random access is inefficient.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and O(N) space complexity.
//   • Invariants: Before merging, the left subarray `a[lo...mid]` and the right subarray `a[mid+1...hi]` are sorted.; During the merge, `a[lo...k-1]` contains the `k-lo` smallest elements from `aux[lo...hi]` in sorted order.
//   • Tips: Utilize an auxiliary array for merging to maintain stability and simplify the merge logic.; Consider the bottom-up iterative implementation to avoid recursion depth limits and potentially improve cache performance.
//   • Pitfalls: Requires O(N) auxiliary space, which can be a significant concern for memory-constrained environments.; Recursive implementations can lead to stack overflow errors for extremely large input arrays.
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: Use when calculating the area of a simple polygon given its vertices in order. It is efficient for both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing signed trapezoidal areas formed by each edge and the x-axis, or equivalently, using the shoelace formula. It achieves an optimal O(N) time complexity, where N is the number of vertices.
//   • Invariants: Vertices are processed sequentially in their given order, forming edges.; The running sum `current_sum` accumulates the signed contribution from each edge processed so far.
//   • Tips: Ensure vertices are provided in a consistent order (clockwise or counter-clockwise).; Use a data type with sufficient range (e.g., long long or double) for intermediate sums to prevent overflow.
//   • Pitfalls: Incorrect vertex order will result in an incorrect signed area or even zero.; Integer overflow can occur if coordinates are large and sums exceed standard integer limits.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int sumSubseqWidths(int* nums, int numsSize) {
    const int MOD = 1000000007;
    /* Sort nums using mergesort */
    int *aux = (int*)malloc(numsSize * sizeof(int));
    if (!aux) return 0; /* allocation failure */

    void merge(int *a, int lo, int mid, int hi) {
        int i = lo, j = mid + 1, k = lo;
        for (int t = lo; t <= hi; ++t) aux[t] = a[t];
        while (i <= mid && j <= hi) {
            if (aux[i] <= aux[j]) a[k++] = aux[i++];
            else a[k++] = aux[j++];
        }
        while (i <= mid) a[k++] = aux[i++];
        while (j <= hi) a[k++] = aux[j++];
    }

    void sort(int *a, int lo, int hi) {
        if (lo >= hi) return;
        int mid = lo + (hi - lo) / 2;
        sort(a, lo, mid);
        sort(a, mid + 1, hi);
        merge(a, lo, mid, hi);
    }

    sort(nums, 0, numsSize - 1);
    free(aux);

    /* Precompute powers of 2 modulo MOD */
    long long *pow2 = (long long*)malloc(numsSize * sizeof(long long));
    if (!pow2) return 0; /* allocation failure */
    pow2[0] = 1;
    for (int i = 1; i < numsSize; ++i) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    /* Calculate the sum of widths */
    long long result = 0;
    for (int i = 0; i < numsSize; ++i) {
        long long max_contrib = pow2[i];          /* number of subsequences where nums[i] is max */
        long long min_contrib = pow2[numsSize - 1 - i]; /* number of subsequences where nums[i] is min */
        result = (result + (max_contrib - min_contrib) * nums[i]) % MOD;
    }
    free(pow2);

    if (result < 0) result += MOD;
    return (int)result;     
}
