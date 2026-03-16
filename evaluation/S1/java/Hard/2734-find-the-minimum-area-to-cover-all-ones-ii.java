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
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
//   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
//   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
//   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
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
    private int getArea(int[][] preSum, int r1, int c1, int r2, int c2) {
        return preSum[r2 + 1][c2 + 1] - preSum[r1][c2 + 1] - preSum[r2 + 1][c1] + preSum[r1][c1];
    }
    public int minimumSum(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] preSum = new int[m + 1][n + 1];
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                preSum[i][j] = grid[i - 1][j - 1] + preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1];
            }
        }

        int minArea = Integer.MAX_VALUE;
        for (int r1 = 0; r1 < m; r1++) {
            for (int r2 = r1 + 1; r2 < m; r2++) {
                for (int c1 = 0; c1 < n; c1++) {
                    for (int c2 = c1 + 1; c2 < n; c2++) {
                        int area1 = getArea(preSum, 0, 0, r1, c1);
                        int area2 = getArea(preSum, r1 + 1, c1 + 1, r2, c2);
                        int area3 = getArea(preSum, r2 + 1, c2 + 1, m - 1, n - 1);
                        if (area1 > 0 && area2 > 0 && area3 > 0) {
                            minArea = Math.min(minArea, area1 + area2 + area3);
                        }
                    }
                }
            }
        }

        return minArea == Integer.MAX_VALUE ? -1 : minArea;         
    }
}
