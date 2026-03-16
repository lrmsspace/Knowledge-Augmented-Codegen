// Source: https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D binary array grid. You need to find 3 non-overlapping rectangles having non-zero areas with horizontal and vertical sides such that all the 1's in grid lie inside these rectangles.
//
// Return the minimum possible sum of the area of these rectangles.
//
// Note that the rectangles are allowed to touch.
//
// Example:
// Input: grid = [[1,0,1],[1,1,1]]
//
// Output: 5
//
// Explanation:
//
//
//
//
// 	The 1's at (0, 0) and (1, 0) are covered by a rectangle of area 2.
// 	The 1's at (0, 2) and (1, 2) are covered by a rectangle of area 2.
// 	The 1 at (1, 1) is covered by a rectangle of area 1.
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 30
// 	grid[i][j] is either 0 or 1.
// 	The input is generated such that there are at least three 1's in grid.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumSum(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] dp = new int[m + 1][n + 1];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[i + 1][j + 1] = dp[i][j + 1] + dp[i + 1][j] - dp[i][j] + grid[i][j];
            }
        }

        int ans = Integer.MAX_VALUE;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = i; k <= m; k++) {
                    for (int l = j; l <= n; l++) {
                        if (dp[k][l] - dp[k][j - 1] - dp[i - 1][l] + dp[i - 1][j - 1] == 0) {
                            ans = Math.min(ans, (k - i + 1) * (l - j + 1));
                        }
                    }
                }
            }
        }

        return ans * 3;         
    }
}
