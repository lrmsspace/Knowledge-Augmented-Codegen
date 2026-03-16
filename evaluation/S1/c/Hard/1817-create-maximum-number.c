// Source: https://leetcode.com/problems/create-maximum-number/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 of lengths m and n respectively. nums1 and nums2 represent the digits of two numbers. You are also given an integer k.
//
// Create the maximum number of length k <= m + n from digits of the two numbers. The relative order of the digits from the same array must be preserved.
//
// Return an array of the k digits representing the answer.
//
// Example:
// Input: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5
// Output: [9,8,6,5,3]
//
// Constraints:
// m == nums1.length
// 	n == nums2.length
// 	1 <= m, n <= 500
// 	0 <= nums1[i], nums2[i] <= 9
// 	1 <= k <= m + n
// 	nums1 and nums2 do not have leading zeros.
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, greedy, dp-1d)
//   • When to use: Use when finding the longest sequence of elements in a given array such that each element is greater than the preceding one, without changing their relative order. It's applicable for optimizing problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of an array where elements are in strictly increasing order. It can be solved in O(N log N) time using a greedy approach with binary search, or O(N^2) using dynamic programming.
//   • Invariants: The 'tails' array elements are always in strictly increasing order.; tails[i] stores the smallest possible ending element of an increasing subsequence of length i+1.
//   • Tips: Prefer the O(N log N) greedy approach with binary search for better performance.; The 'tails' array in the greedy approach stores the smallest tail of all increasing subsequences of a certain length.
//   • Pitfalls: Confusing LIS with Longest Common Subsequence (LCS) or contiguous subarrays.; Incorrectly handling duplicate elements when 'strictly increasing' is required.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxNumber(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize) {
    *returnSize = k;
    int *result = (int*)malloc(k * sizeof(int));
    if (!result) return NULL;

    /* Helper function to get the maximum subsequence of length len from nums */
    int* getMaxSubsequence(int* nums, int numsSize, int len) {
        int* subseq = (int*)malloc(len * sizeof(int));
        int top = -1;
        int toRemove = numsSize - len;
        for (int i = 0; i < numsSize; i++) {
            while (top >= 0 && subseq[top] < nums[i] && toRemove > 0) {
                top--;
                toRemove--;
            }
            if (top + 1 < len) {
                subseq[++top] = nums[i];
            } else {
                toRemove--;
            }
        }
        return subseq;
    }

    /* Helper function to merge two subsequences into the maximum number */
    void merge(int* subseq1, int len1, int* subseq2, int len2, int* merged, int k) {
        int i = 0, j = 0, r = 0;
        while (r < k) {
            if (memcmp(subseq1 + i, subseq2 + j, (len1 - i) * sizeof(int)) > 0) {
                merged[r++] = subseq1[i++];
            } else {
                merged[r++] = subseq2[j++];
            }
        }
    }

    for (int i = 0; i <= k; i++) {
        if (i > nums1Size || k - i > nums2Size) continue;
        int* subseq1 = getMaxSubsequence(nums1, nums1Size, i);
        int* subseq2 = getMaxSubsequence(nums2, nums2Size, k - i);
        int* merged = (int*)malloc(k * sizeof(int));
        merge(subseq1, i, subseq2, k - i, merged, k);
        if (memcmp(merged, result, k * sizeof(int)) > 0) {
            memcpy(result, merged, k * sizeof(int));
        }
        free(subseq1);
        free(subseq2);
        free(merged);
    }

    return result;      
}
