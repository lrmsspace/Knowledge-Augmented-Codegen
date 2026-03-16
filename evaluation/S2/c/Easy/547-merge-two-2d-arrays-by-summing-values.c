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
// - Minkowski sum of convex polygons (geometry, array, two-pointers, sweep-line)
//   • When to use: Use this algorithm to compute the Minkowski sum of two convex polygons efficiently. It is ideal for applications requiring the union of shapes or collision detection between convex objects.
//   • Idea: This algorithm computes the Minkowski sum of two convex polygons by merging their edge vectors, sorted by polar angle, into a new sequence of edges. The resulting sum polygon is also convex and can be constructed in O(|P| + |Q|) time.
//   • Invariants: The current vertex of the resulting sum polygon is the sum of the current vertices from P and Q.; All edges processed so far from both input polygons have been added to the output in polar angle order.
//   • Tips: Pre-sort polygon vertices to start from the lowest Y-coordinate to ensure consistent orientation.; Orient both input polygons counter-clockwise for correct edge vector generation.
//   • Pitfalls: Incorrectly handling polygon orientation (e.g., mixing clockwise and counter-clockwise).; Precision issues when using floating-point numbers for angle comparisons or vector additions.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting items, each with a weight and value, to maximize total value within a limited capacity, where each item can be chosen multiple times. It is suitable for problems exhibiting optimal substructure and overlapping subproblems.
//   • Idea: The Knapsack Problem involves selecting items to maximize total value within a fixed capacity. The complete knapsack variant, where items can be taken multiple times, is typically solved using dynamic programming in O(nW) time and O(W) space.
//   • Invariants: For 2D DP `f[i][j]`, it represents the maximum value obtainable using only the first `i` items with a total weight not exceeding `j`.; For 1D DP `dp[j]`, after processing item `i`, it stores the maximum value obtainable with a total weight not exceeding `j`, considering all items up to `i`.
//   • Tips: For the complete knapsack, iterate capacity `j` forwards (from `w_i` to `W`) when using 1D DP to allow multiple selections of the current item.; The 1D DP array `dp[j]` stores the maximum value achievable for exactly capacity `j`.
//   • Pitfalls: Confusing 0-1 knapsack with complete knapsack, especially in the 1D DP iteration direction for capacity.; Incorrectly initializing the DP array, leading to incorrect base cases or propagation.
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
    int i = 0, j = 0, k = 0;
    int **result = (int **)malloc((nums1Size + nums2Size) * sizeof(int *));
    *returnColumnSizes = (int *)malloc((nums1Size + nums2Size) * sizeof(int));
    
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i][0] < nums2[j][0]) {
            result[k] = (int *)malloc(2 * sizeof(int));
            result[k][0] = nums1[i][0];
            result[k][1] = nums1[i][1];
            (*returnColumnSizes)[k++] = 2;
            i++;
        } else if (nums1[i][0] > nums2[j][0]) {
            result[k] = (int *)malloc(2 * sizeof(int));
            result[k][0] = nums2[j][0];
            result[k][1] = nums2[j][1];
            (*returnColumnSizes)[k++] = 2;
            j++;
        } else {
            result[k] = (int *)malloc(2 * sizeof(int));
            result[k][0] = nums1[i][0];
            result[k][1] = nums1[i][1] + nums2[j][1];
            (*returnColumnSizes)[k++] = 2;
            i++;
            j++;
        }
    }
    
    while (i < nums1Size) {
        result[k] = (int *)malloc(2 * sizeof(int));
        result[k][0] = nums1[i][0];
        result[k][1] = nums1[i][1];
        (*returnColumnSizes)[k++] = 2;
        i++;
    }
    
    while (j < nums2Size) {
        result[k] = (int *)malloc(2 * sizeof(int));
        result[k][0] = nums2[j][0];
        result[k][1] = nums2[j][1];
        (*returnColumnSizes)[k++] = 2;
        j++;
    }
    
    *returnSize = k;
    return result;      
}
