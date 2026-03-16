// Source: https://leetcode.com/problems/first-completely-painted-row-or-column/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array arr, and an m x n integer matrix mat. arr and mat both contain all the integers in the range [1, m * n].
//
// Go through each index i in arr starting from index 0 and paint the cell in mat containing the integer arr[i].
//
// Return the smallest index i at which either a row or a column will be completely painted in mat.
//
// Example:
// Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
// Output: 2
// Explanation: The moves are shown in order, and both the first row and second column of the matrix become fully painted at arr[2].
//
// Constraints:
// m == mat.length
// 	n = mat[i].length
// 	arr.length == m * n
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= arr[i], mat[r][c] <= m * n
// 	All the integers of arr are unique.
// 	All the integers of mat are unique.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Intersection Point of Lines (geometry, number, enumeration)
//   • When to use: When you need to find the exact coordinates where two lines meet in a 2D plane, or determine if they are parallel or coincident. This is useful for geometric problems involving line segments or polygons.
//   • Idea: This method calculates the coordinates of the intersection point of two lines, typically represented in general form (Ax + By + C = 0), by solving a system of linear equations. It has a constant time complexity, O(1), for each pair of lines.
//   • Invariants: The coefficients (a, b, c) for each line remain constant throughout the calculation.; If the determinant of the coefficient matrix is non-zero, a unique intersection point exists.
//   • Tips: Represent lines in a consistent form, like general form (Ax + By + C = 0) or slope-intercept (y = mx + b).; Handle edge cases for parallel and coincident lines explicitly to avoid division by zero.
//   • Pitfalls: Division by zero if lines are parallel or coincident without proper checks.; Floating-point precision errors can lead to incorrect intersection points or misidentification of parallel lines.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int firstCompleteIndex(int* arr, int arrSize, int** mat, int matSize, int* matColSize) {
    int m = matSize;
    int n = matColSize[0];
    int pos[m * n + 1][2];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            pos[mat[i][j]][0] = i;
            pos[mat[i][j]][1] = j;
        }
    }

    int rowCount[m];
    int colCount[n];
    for (int i = 0; i < m; ++i) {
        rowCount[i] = 0;
    }
    for (int j = 0; j < n; ++j) {
        colCount[j] = 0;
    }

    for (int i = 0; i < arrSize; ++i) {
        int val = arr[i];
        int r = pos[val][0];
        int c = pos[val][1];

        rowCount[r]++;
        if (rowCount[r] == n) {
            return i;
        }

        colCount[c]++;
        if (colCount[c] == m) {
            return i;
        }
    }

    return -1; // This line should never be reached given the problem constraints.      
}
