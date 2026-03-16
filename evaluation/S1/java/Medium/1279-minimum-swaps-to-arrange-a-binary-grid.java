// Source: https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.
//
// A grid is said to be valid if all the cells above the main diagonal are zeros.
//
// Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.
//
// The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).
//
// Example:
// Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
// Output: 3
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 200
// 	grid[i][j] is either 0 or 1
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Calculating the determinant of a matrix by Gauss (matrix, number, simulation, counting)
//   • When to use: When needing to compute the determinant of a square matrix, especially when Gaussian elimination is a familiar or efficient approach. It is suitable for matrices where direct cofactor expansion is computationally too expensive.
//   • Idea: This algorithm computes the determinant of a square matrix by transforming it into an upper triangular form using Gaussian elimination. The determinant is the product of diagonal elements, adjusted by a sign factor from row swaps, with O(N^3) complexity.
//   • Invariants: Before processing column 'k', all elements A[i][j] where i > j and j < k are zero.; The determinant of the current matrix, multiplied by (-1)^swaps, equals the original matrix's determinant.
//   • Tips: Track the number of row swaps to correctly determine the determinant's sign.; Pivot selection can improve numerical stability, especially with floating-point numbers.
//   • Pitfalls: Forgetting to adjust the sign after row exchanges.; Division by zero if a pivot element is zero, requiring a row swap.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minSwaps(int[][] grid) {
        int n = grid.length;
        int[] trailingZeros = new int[n];

        // Calculate trailing zeros for each row
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = n - 1; j >= 0 && grid[i][j] == 0; j--) {
                count++;
            }
            trailingZeros[i] = count;
        }

        int swaps = 0;

        // For each row, ensure it has enough trailing zeros
        for (int i = 0; i < n; i++) {
            int requiredZeros = n - 1 - i;
            int rowIndex = -1;

            // Find a row with enough trailing zeros
            for (int j = i; j < n; j++) {
                if (trailingZeros[j] >= requiredZeros) {
                    rowIndex = j;
                    break;
                }
            }

            // If no such row exists, return -1
            if (rowIndex == -1) {
                return -1;
            }

            // Move the found row to the current position
            while (rowIndex > i) {
                // Swap rows in trailingZeros array
                int temp = trailingZeros[rowIndex];
                trailingZeros[rowIndex] = trailingZeros[rowIndex - 1];
                trailingZeros[rowIndex - 1] = temp;
                rowIndex--;
                swaps++;
            }
        }

        return swaps;           
    }
}
