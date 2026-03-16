// Source: https://leetcode.com/problems/maximum-number-of-points-with-cost/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix points (0-indexed). Starting with 0 points, you want to maximize the number of points you can get from the matrix.
//
// To gain points, you must pick one cell in each row. Picking the cell at coordinates (r, c) will add points[r][c] to your score.
//
// However, you will lose points if you pick a cell too far from the cell that you picked in the previous row. For every two adjacent rows r and r + 1 (where 0 <= r < m - 1), picking cells at coordinates (r, c1) and (r + 1, c2) will subtract abs(c1 - c2) from your score.
//
// Return the maximum number of points you can achieve.
//
// abs(x) is defined as:
//
//
// 	x for x >= 0.
// 	-x for x < 0.
//
// Example:
// Input: points = [[1,2,3],[1,5,1],[3,1,1]]
// Output: 9
// Explanation:
// The blue cells denote the optimal cells to pick, which have coordinates (0, 2), (1, 1), and (2, 0).
// You add 3 + 5 + 3 = 11 to your score.
// However, you must subtract abs(2 - 1) + abs(1 - 0) = 2 from your score.
// Your final score is 11 - 2 = 9.
//
// Constraints:
// m == points.length
// 	n == points[r].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	0 <= points[r][c] <= 105
//

class Solution {
    public long maxPoints(int[][] points) {
        int m = points.length;
        int n = points[0].length;

        long[] dp = new long[n];
        for (int c = 0; c < n; c++) {
            dp[c] = points[0][c];
        }

        for (int r = 1; r < m; r++) {
            long[] leftMax = new long[n];
            long[] rightMax = new long[n];

            leftMax[0] = dp[0];
            for (int c = 1; c < n; c++) {
                leftMax[c] = Math.max(leftMax[c - 1] - 1, dp[c]);
            }

            rightMax[n - 1] = dp[n - 1];
            for (int c = n - 2; c >= 0; c--) {
                rightMax[c] = Math.max(rightMax[c + 1] - 1, dp[c]);
            }

            for (int c = 0; c < n; c++) {
                dp[c] = points[r][c] + Math.max(leftMax[c], rightMax[c]);
            }
        }

        long maxPoints = 0;
        for (long point : dp) {
            maxPoints = Math.max(maxPoints, point);
        }

        return maxPoints;           
    }
}
