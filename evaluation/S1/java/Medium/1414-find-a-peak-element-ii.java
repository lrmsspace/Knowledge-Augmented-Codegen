// Source: https://leetcode.com/problems/find-a-peak-element-ii/   |   Difficulty: Medium
//
// Problem Description:
// A peak element in a 2D grid is an element that is strictly greater than all of its adjacent neighbors to the left, right, top, and bottom.
//
// Given a 0-indexed m x n matrix mat where no two adjacent cells are equal, find any peak element mat[i][j] and return the length 2 array [i,j].
//
// You may assume that the entire matrix is surrounded by an outer perimeter with the value -1 in each cell.
//
// You must write an algorithm that runs in O(m log(n)) or O(n log(m)) time.
//
// Example:
// Input: mat = [[1,4],[3,2]]
// Output: [0,1]
// Explanation: Both 3 and 4 are peak elements so [1,0] and [0,1] are both acceptable answers.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 500
// 	1 <= mat[i][j] <= 105
// 	No two adjacent cells are equal.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Check if point belongs to the convex pol (geometry, array, binary-search)
//   • When to use: This algorithm is used to efficiently determine if a given query point lies inside or on the boundary of a convex polygon, especially when many queries are performed on the same polygon.
//   • Idea: The core idea is to decompose the convex polygon into triangles originating from a reference vertex. Binary search is then used to find the specific triangle that could contain the query point, followed by a point-in-triangle check.
//   • Invariants: The reference point p_0 is the lexicographically smallest vertex of the polygon.; All polygon vertices p_1, ..., p_n are ordered counter-clockwise by polar angle around p_0.
//   • Tips: Choose a consistent reference point, typically the lexicographically smallest vertex, to simplify angular sorting.; Ensure polygon vertices are ordered (e.g., counter-clockwise) relative to the reference point for correct binary search behavior.
//   • Pitfalls: Floating point precision errors can lead to incorrect results for collinear points or boundary checks; prefer integer arithmetic with cross products.; Incorrectly handling boundary conditions (points exactly on an edge or vertex) can lead to false negatives or positives.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] findPeakGrid(int[][] mat) {
        int rows = mat.length;
        int cols = mat[0].length;

        int top = 0;
        int bottom = rows - 1;

        while (top <= bottom) {
            int midRow = top + (bottom - top) / 2;

            // Find the column index of the maximum element in the midRow
            int maxColIndex = 0;
            for (int col = 1; col < cols; col++) {
                if (mat[midRow][col] > mat[midRow][maxColIndex]) {
                    maxColIndex = col;
                }
            }

            boolean isPeak = true;

            // Check the element above
            if (midRow > 0 && mat[midRow - 1][maxColIndex] > mat[midRow][maxColIndex]) {
                isPeak = false;
                bottom = midRow - 1; // Move search to upper half
            }

            // Check the element below
            if (midRow < rows - 1 && mat[midRow + 1][maxColIndex] > mat[midRow][maxColIndex]) {
                isPeak = false;
                top = midRow + 1; // Move search to lower half
            }

            if (isPeak) {
                return new int[]{midRow, maxColIndex};
            }
        }

        return new int[]{-1, -1}; // This line should never be reached due to problem constraints           
    }
}
