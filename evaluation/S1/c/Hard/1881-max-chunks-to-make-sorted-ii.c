// Source: https://leetcode.com/problems/max-chunks-to-make-sorted-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array arr.
//
// We split arr into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array.
//
// Return the largest number of chunks we can make to sort the array.
//
// Example:
// Input: arr = [5,4,3,2,1]
// Output: 1
// Explanation:
// Splitting into two or more chunks will not return the required result.
// For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.
//
// Constraints:
// 1 <= arr.length <= 2000
// 	0 <= arr[i] <= 108
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxChunksToSorted(int* arr, int arrSize) {
    int *maxLeft = (int*)malloc(arrSize * sizeof(int));
    int *minRight = (int*)malloc(arrSize * sizeof(int));
    if (!maxLeft || !minRight) {
        free(maxLeft); free(minRight);
        return 0; /* allocation failure */
    }

    /* Compute maxLeft */
    int currentMax = arr[0];
    for (int i = 0; i < arrSize; ++i) {
        if (arr[i] > currentMax) currentMax = arr[i];
        maxLeft[i] = currentMax;
    }

    /* Compute minRight */
    int currentMin = arr[arrSize - 1];
    for (int i = arrSize - 1; i >= 0; --i) {
        if (arr[i] < currentMin) currentMin = arr[i];
        minRight[i] = currentMin;
    }

    /* Count valid chunk boundaries */
    int chunkCount = 0;
    for (int i = 0; i < arrSize - 1; ++i) {
        if (maxLeft[i] <= minRight[i + 1]) {
            chunkCount++;
        }
    }

    free(maxLeft);
    free(minRight);
    return chunkCount + 1; /* number of chunks is boundaries + 1 */     
}
