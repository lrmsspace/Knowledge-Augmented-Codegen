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

class Solution {
    public int minScoreTriangulation(int[] values) {
        int n = values.length;
        int[][] dp = new int[n][n];

        for (int length = 2; length < n; length++) {
            for (int i = 0; i + length < n; i++) {
                int j = i + length;
                dp[i][j] = Integer.MAX_VALUE;

                for (int k = i + 1; k < j; k++) {
                    dp[i][j] = Math.min(dp[i][j],
                            dp[i][k] + dp[k][j] + values[i] * values[j] * values[k]);
                }
            }
        }

        return dp[0][n - 1];            
    }
}
