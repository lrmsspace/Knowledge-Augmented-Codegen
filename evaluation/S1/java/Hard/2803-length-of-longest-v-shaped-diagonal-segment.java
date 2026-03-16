// Source: https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, where each element is either 0, 1, or 2.
//
// A V-shaped diagonal segment is defined as:
//
//
// 	The segment starts with 1.
// 	The subsequent elements follow this infinite sequence: 2, 0, 2, 0, ....
// 	The segment:
// 	
// 		Starts along a diagonal direction (top-left to bottom-right, bottom-right to top-left, top-right to bottom-left, or bottom-left to top-right).
// 		Continues the sequence in the same diagonal direction.
// 		Makes at most one clockwise 90-degree turn to another diagonal direction while maintaining the sequence.
// 	
// 	
//
//
// Return the length of the longest V-shaped diagonal segment. If no valid segment exists, return 0.
//
// Example:
// Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
//
// Output: 5
//
// Explanation:
//
//
//
// The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: (0,2) → (1,3) → (2,4), takes a 90-degree clockwise turn at (2,4), and continues as (3,3) → (4,2).
//
// Constraints:
// n == grid.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	grid[i][j] is either 0, 1 or 2.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int lenOfVDiagonal(int[][] grid) {
        int n = grid.length, m = grid[0].length;
        int[][][] dp = new int[n][m][4];

        int maxLen = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    dp[i][j][0] = 1;
                    dp[i][j][2] = 1;
                } else if (grid[i][j] == 2) {
                    if (i > 0 && j > 0) {
                        dp[i][j][0] = dp[i - 1][j - 1][1] + 1;
                    }
                    if (i > 0 && j < m - 1) {
                        dp[i][j][3] = dp[i - 1][j + 1][2] + 1;
                    }
                } else if (grid[i][j] == 0) {
                    if (i > 0 && j < m - 1) {
                        dp[i][j][1] = dp[i - 1][j + 1][0] + 1;
                    }
                    if (i > 0 && j > 0) {
                        dp[i][j][2] = dp[i - 1][j - 1][3] + 1;
                    }
                }

                maxLen = Math.max(maxLen, Math.max(dp[i][j][0] + dp[i][j][1] - 1,
                                                  dp[i][j][2] + dp[i][j][3] - 1));
            }
        }
        return maxLen;
    }
}
