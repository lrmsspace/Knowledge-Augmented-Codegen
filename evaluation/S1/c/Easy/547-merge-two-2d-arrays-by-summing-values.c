// Source: https://leetcode.com/problems/merge-two-2d-arrays-by-summing-values/   |   Difficulty: Easy
//
// Problem Description:
// You are given two 2D integer arrays nums1 and nums2.
//
//
// 	nums1[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
// 	nums2[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
//
//
// Each array contains unique ids and is sorted in ascending order by id.
//
// Merge the two arrays into one array that is sorted in ascending order by id, respecting the following conditions:
//
//
// 	Only ids that appear in at least one of the two arrays should be included in the resulting array.
// 	Each id should be included only once and its value should be the sum of the values of this id in the two arrays. If the id does not exist in one of the two arrays, then assume its value in that array to be 0.
//
//
// Return the resulting array. The returned array must be sorted in ascending order by id.
//
// Example:
// Input: nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
// Output: [[1,6],[2,3],[3,2],[4,6]]
// Explanation: The resulting array contains the following:
// - id = 1, the value of this id is 2 + 4 = 6.
// - id = 2, the value of this id is 3.
// - id = 3, the value of this id is 2.
// - id = 4, the value of this id is 5 + 1 = 6.
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 200
// 	nums1[i].length == nums2[j].length == 2
// 	1 <= idi, vali <= 1000
// 	Both arrays contain unique ids.
// 	Both arrays are in strictly ascending order by id.
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Minkowski sum of convex polygons (geometry, array, two-pointers)
//   • When to use: When needing to compute the sum of two convex polygons, or efficiently determine the minimum distance or intersection between them.
//   • Idea: The Minkowski sum of two convex polygons P and Q is a new convex polygon formed by vector addition of all points from P and Q. It can be computed in O(|P| + |Q|) time by merging their edge vectors.
//   • Invariants: The current edge added to the Minkowski sum is the one with the smallest angle among the remaining edges from both polygons.; The sequence of edges in the Minkowski sum maintains convexity.
//   • Tips: The vertices of P+Q are sums of vertices of P and Q.; The edges of P+Q are the edges of P and Q, sorted by angle.
//   • Pitfalls: Incorrectly handling edge cases like collinear edges or degenerate polygons.; Floating point precision issues in geometric calculations.
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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** mergeArrays(int** nums1, int nums1Size, int* nums1ColSize, int** nums2, int nums2Size, int* nums2ColSize, int* returnSize, int** returnColumnSizes) {
    int maxPossibleSize = nums1Size + nums2Size;
    int** result = (int**)malloc(maxPossibleSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxPossibleSize * sizeof(int));
    int i = 0, j = 0, k = 0;

    while (i < nums1Size && j < nums2Size) {
        if (nums1[i][0] < nums2[j][0]) {
            result[k] = (int*)malloc(2 * sizeof(int));
            result[k][0] = nums1[i][0];
            result[k][1] = nums1[i][1];
            (*returnColumnSizes)[k] = 2;
            i++;
        } else if (nums1[i][0] > nums2[j][0]) {
            result[k] = (int*)malloc(2 * sizeof(int));
            result[k][0] = nums2[j][0];
            result[k][1] = nums2[j][1];
            (*returnColumnSizes)[k] = 2;
            j++;
        } else {
            result[k] = (int*)malloc(2 * sizeof(int));
            result[k][0] = nums1[i][0];
            result[k][1] = nums1[i][1] + nums2[j][1];
            (*returnColumnSizes)[k] = 2;
            i++;
            j++;
        }
        k++;
    }

    while (i < nums1Size) {
        result[k] = (int*)malloc(2 * sizeof(int));
        result[k][0] = nums1[i][0];
        result[k][1] = nums1[i][1];
        (*returnColumnSizes)[k] = 2;
        i++;
        k++;
    }

    while (j < nums2Size) {
        result[k] = (int*)malloc(2 * sizeof(int));
        result[k][0] = nums2[j][0];
        result[k][1] = nums2[j][1];
        (*returnColumnSizes)[k] = 2;
        j++;
        k++;
    }

    *returnSize = k;
    return result;      
}
