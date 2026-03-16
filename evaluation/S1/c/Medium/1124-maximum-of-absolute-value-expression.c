// Source: https://leetcode.com/problems/maximum-of-absolute-value-expression/   |   Difficulty: Medium
//
// Problem Description:
// Given two arrays of integers with equal lengths, return the maximum value of:
//
// |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
//
// where the maximum is taken over all 0 <= i, j < arr1.length.
//
// Example:
// Input: arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
// Output: 13
//
// Constraints:
// 2 <= arr1.length == arr2.length <= 40000
// 	-10^6 <= arr1[i], arr2[i] <= 10^6
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxAbsValExpr(int* arr1, int arr1Size, int* arr2, int arr2Size) {
    int maxVal = 0;
    int signs[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    
    for (int s = 0; s < 4; s++) {
        int sign1 = signs[s][0];
        int sign2 = signs[s][1];
        
        int minExpr = sign1 * arr1[0] + sign2 * arr2[0] + 0;
        int maxExpr = minExpr;
        
        for (int i = 1; i < arr1Size; i++) {
            int currentExpr = sign1 * arr1[i] + sign2 * arr2[i] + i;
            if (currentExpr < minExpr) {
                minExpr = currentExpr;
            }
            if (currentExpr > maxExpr) {
                maxExpr = currentExpr;
            }
        }
        
        int currentMaxVal = maxExpr - minExpr;
        if (currentMaxVal > maxVal) {
            maxVal = currentMaxVal;
        }
    }
    
    return maxVal;      
}
