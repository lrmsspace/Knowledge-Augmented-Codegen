// Source: https://leetcode.com/problems/minimum-path-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.
//
// Note: You can only move either down or right at any point in time.
//
// Example:
// Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
// Output: 7
// Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 200
// 	0 <= grid[i][j] <= 200
//

class Solution {
    public int minPathSum(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        // Create a 2D array to store the minimum path sums
        int[][] dp = new int[m][n];

        // Initialize the starting point
        dp[0][0] = grid[0][0];

        // Fill in the first row (can only come from the left)
        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }

        // Fill in the first column (can only come from above)
        for (int i = 1; i < m; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }

        // Fill in the rest of the dp array
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = Math.min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }

        // The bottom-right cell contains the minimum path sum
        return dp[m - 1][n - 1];            
    }
}
