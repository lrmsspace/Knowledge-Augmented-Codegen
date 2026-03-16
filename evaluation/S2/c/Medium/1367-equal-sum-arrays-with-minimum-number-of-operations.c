// Source: https://leetcode.com/problems/equal-sum-arrays-with-minimum-number-of-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays of integers nums1 and nums2, possibly of different lengths. The values in the arrays are between 1 and 6, inclusive.
//
// In one operation, you can change any integer's value in any of the arrays to any value between 1 and 6, inclusive.
//
// Return the minimum number of operations required to make the sum of values in nums1 equal to the sum of values in nums2. Return -1​​​​​ if it is not possible to make the sum of the two arrays equal.
//
// Example:
// Input: nums1 = [1,2,3,4,5,6], nums2 = [1,1,2,2,2,2]
// Output: 3
// Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed.
// - Change nums2[0] to 6. nums1 = [1,2,3,4,5,6], nums2 = [6,1,2,2,2,2].
// - Change nums1[5] to 1. nums1 = [1,2,3,4,5,1], nums2 = [6,1,2,2,2,2].
// - Change nums1[2] to 2. nums1 = [1,2,2,4,5,1], nums2 = [6,1,2,2,2,2].
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 105
// 	1 <= nums1[i], nums2[i] <= 6
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Hungarian algorithm for solving the assignment problem (matrix, graph, array, greedy, bfs, enumeration)
//   • When to use: Use when finding a minimum cost perfect matching in a bipartite graph, typically represented as an N x N cost matrix, where each row must be assigned to exactly one column.
//   • Idea: The Hungarian algorithm finds a minimum weight perfect matching in a bipartite graph, solving the assignment problem for an N x N cost matrix. It iteratively finds augmenting paths in an equality graph and adjusts potentials, achieving O(N^3) time complexity.
//   • Invariants: For all i, j, u[i] + v[j] <= A[i][j] (potential condition).; The current matching is always valid (each row/column used at most once).
//   • Tips: Understand the concept of potentials and their role in maintaining the equality graph.; The algorithm can be adapted for maximum profit problems by negating costs.
//   • Pitfalls: Incorrectly updating potentials can lead to non-optimal solutions or infinite loops.; Handling non-square matrices requires careful padding with dummy values.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minOperations(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < nums1Size; i++) {
        sum1 += nums1[i];
    }
    for (int i = 0; i < nums2Size; i++) {
        sum2 += nums2[i];
    }

    if (sum1 > sum2) {
        // Swap to ensure sum1 <= sum2
        int* tempArr = nums1;
        nums1 = nums2;
        nums2 = tempArr;
        int tempSize = nums1Size;
        nums1Size = nums2Size;
        nums2Size = tempSize;
        int tempSum = sum1;
        sum1 = sum2;
        sum2 = tempSum;
    }

    int diff = sum2 - sum1;
    if (diff == 0) return 0;

    int count[7] = {0}; // Count of numbers from 1 to 6
    for (int i = 0; i < nums1Size; i++) {
        count[6 - nums1[i]]++; // Potential increase from nums1
    }
    for (int i = 0; i < nums2Size; i++) {
        count[nums2[i] - 1]++; // Potential decrease from nums2
    }

    int operations = 0;
    for (int i = 5; i > 0 && diff > 0; i--) {
        while (count[i] > 0 && diff > 0) {
            diff -= i; // Reduce the difference by the potential change
            count[i]--;
            operations++;
        }
    }

    return diff > 0 ? -1 : operations;      
}
