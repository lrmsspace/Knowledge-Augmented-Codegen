// Source: https://leetcode.com/problems/minimum-score-triangulation-of-polygon/   |   Difficulty: Medium
//
// Problem Description:
// You have a convex n-sided polygon where each vertex has an integer value. You are given an integer array values where values[i] is the value of the ith vertex in clockwise order.
//
// Polygon triangulation is a process where you divide a polygon into a set of triangles and the vertices of each triangle must also be vertices of the original polygon. Note that no other shapes other than triangles are allowed in the division. This process will result in n - 2 triangles.
//
// You will triangulate the polygon. For each triangle, the weight of that triangle is the product of the values at its vertices. The total score of the triangulation is the sum of these weights over all n - 2 triangles.
//
// Return the minimum possible score that you can achieve with some triangulation of the polygon.
//
// Example:
// Input: values = [1,2,3]
//
// Output: 6
//
// Explanation: The polygon is already triangulated, and the score of the only triangle is 6.
//
// Constraints:
// n == values.length
// 	3 <= n <= 50
// 	1 <= values[i] <= 100
//
// Helpful references (internal KB):
// - Check if point belongs to the convex pol (geometry, array, binary-search)
//   • When to use: This algorithm is used to efficiently determine if a given query point lies inside or on the boundary of a convex polygon, especially when many queries are performed on the same polygon.
//   • Idea: The core idea is to decompose the convex polygon into triangles originating from a reference vertex. Binary search is then used to find the specific triangle that could contain the query point, followed by a point-in-triangle check.
//   • Invariants: The reference point p_0 is the lexicographically smallest vertex of the polygon.; All polygon vertices p_1, ..., p_n are ordered counter-clockwise by polar angle around p_0.
//   • Tips: Choose a consistent reference point, typically the lexicographically smallest vertex, to simplify angular sorting.; Ensure polygon vertices are ordered (e.g., counter-clockwise) relative to the reference point for correct binary search behavior.
//   • Pitfalls: Floating point precision errors can lead to incorrect results for collinear points or boundary checks; prefer integer arithmetic with cross products.; Incorrectly handling boundary conditions (points exactly on an edge or vertex) can lead to false negatives or positives.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: Used to optimize certain 2D dynamic programming problems, typically interval DP, where the cost function satisfies the quadrangle inequality and the optimal split points exhibit monotonicity.
//   • Idea: Knuth's Optimization reduces the time complexity of certain 2D DP problems from O(N^3) to O(N^2) by restricting the search range for the optimal split point. This is applicable when the cost function satisfies the quadrangle inequality and the optimal split points are monotonic.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for dp[i][j].
//   • Tips: Verify the quadrangle inequality for the cost function C(a,c) + C(b,d) <= C(a,d) + C(b,c).; Ensure the optimal split points opt[i][j] are monotonic: opt[i][j-1] <= opt[i][j] <= opt[i+1][j].
//   • Pitfalls: Incorrectly assuming quadrangle inequality holds for the cost function.; Improper iteration order for DP states, which breaks the opt dependency.
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
    public int minScoreTriangulation(int[] values) {
        int n = values.length;
        int[][] dp = new int[n][n];

        for (int len = 2; len < n; len++) {
            for (int i = 0; i + len < n; i++) {
                int j = i + len;
                dp[i][j] = Integer.MAX_VALUE;

                for (int k = i + 1; k < j; k++) {
                    int score = values[i] * values[j] * values[k] + dp[i][k] + dp[k][j];
                    dp[i][j] = Math.min(dp[i][j], score);
                }
            }
        }

        return dp[0][n - 1];            
    }
}
