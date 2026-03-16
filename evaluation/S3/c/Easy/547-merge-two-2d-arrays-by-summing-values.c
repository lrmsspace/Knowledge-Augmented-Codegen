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
// - Minkowski sum of convex polygons (geometry, array, two-pointers)
//   • When to use: When needing to compute the sum of two convex polygons, or efficiently determine the minimum distance or intersection between them.
//   • Idea: The Minkowski sum of two convex polygons P and Q is a new convex polygon formed by vector addition of all points from P and Q. It can be computed in O(|P| + |Q|) time by merging their edge vectors.
//   • Invariants: The current edge added to the Minkowski sum is the one with the smallest angle among the remaining edges from both polygons.; The sequence of edges in the Minkowski sum maintains convexity.
//   • Tips: The vertices of P+Q are sums of vertices of P and Q.; The edges of P+Q are the edges of P and Q, sorted by angle.
//   • Pitfalls: Incorrectly handling edge cases like collinear edges or degenerate polygons.; Floating point precision issues in geometric calculations.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
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
    int** result = (int**)malloc((nums1Size + nums2Size) * sizeof(int*));
    *returnColumnSizes = (int*)malloc((nums1Size + nums2Size) * sizeof(int));
    
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i][0] == nums2[j][0]) {
            result[k] = (int*)malloc(2 * sizeof(int));
            result[k][0] = nums1[i][0];
            result[k][1] = nums1[i][1] + nums2[j][1];
            (*returnColumnSizes)[k++] = 2;
            i++;
            j++;
        } else if (nums1[i][0] < nums2[j][0]) {
            result[k] = (int*)malloc(2 * sizeof(int));
            result[k][0] = nums1[i][0];
            result[k][1] = nums1[i][1];
            (*returnColumnSizes)[k++] = 2;
            i++;
        } else {
            result[k] = (int*)malloc(2 * sizeof(int));
            result[k][0] = nums2[j][0];
            result[k][1] = nums2[j][1];
            (*returnColumnSizes)[k++] = 2;
            j++;
        }
    }
    
    while (i < nums1Size) {
        result[k] = (int*)malloc(2 * sizeof(int));
        result[k][0] = nums1[i][0];
        result[k][1] = nums1[i][1];
        (*returnColumnSizes)[k++] = 2;
        i++;
    }
    
    while (j < nums2Size) {
        result[k] = (int*)malloc(2 * sizeof(int));
        result[k][0] = nums2[j][0];
        result[k][1] = nums2[j][1];
        (*returnColumnSizes)[k++] = 2;
        j++;
    }
    
    *returnSize = k;
    return result;      
}
