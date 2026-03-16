// Source: https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of size n where n is a multiple of 3 and a positive integer k.
//
// Divide the array nums into n / 3 arrays of size 3 satisfying the following condition:
//
//
// 	The difference between any two elements in one array is less than or equal to k.
//
//
// Return a 2D array containing the arrays. If it is impossible to satisfy the conditions, return an empty array. And if there are multiple answers, return any of them.
//
// Example:
// Input: nums = [1,3,4,8,7,9,3,5,1], k = 2
//
// Output: [[1,1,3],[3,4,5],[7,8,9]]
//
// Explanation:
//
// The difference between any two elements in each array is less than or equal to 2.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	n is a multiple of 3
// 	1 <= nums[i] <= 105
// 	1 <= k <= 105
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** divideArray(int* nums, int numsSize, int k, int* returnSize, int** returnColumnSizes) {
    // Sort the array using a simple quicksort implementation
    int compare(const void* a, const void* b) {
        return (*(int*)a - *(int*)b);
    }
    qsort(nums, numsSize, sizeof(int), compare);

    int n = numsSize / 3;
    int** result = (int**)malloc(n * sizeof(int*));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < n; i++) {
        int idx = i * 3;
        if (nums[idx + 2] - nums[idx] <= k) {
            result[*returnSize] = (int*)malloc(3 * sizeof(int));
            result[*returnSize][0] = nums[idx];
            result[*returnSize][1] = nums[idx + 1];
            result[*returnSize][2] = nums[idx + 2];
            (*returnColumnSizes)[*returnSize] = 3;
            (*returnSize)++;
        } else {
            // Free allocated memory before returning empty array
            for (int j = 0; j < *returnSize; j++) {
                free(result[j]);
            }
            free(result);
            free(*returnColumnSizes);
            *returnSize = 0;
            return NULL;
        }
    }

    return result;      
}
