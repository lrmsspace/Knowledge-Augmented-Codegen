// Source: https://leetcode.com/problems/out-of-boundary-paths/   |   Difficulty: Medium
//
// Problem Description:
// There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.
//
// Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
// Output: 6
//
// Constraints:
// 1 <= m, n <= 50
// 	0 <= maxMove <= 50
// 	0 <= startRow < m
// 	0 <= startColumn < n
//

class Solution {
    public int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        int MOD = 1_000_000_007;
        int[][][] dp = new int[m][n][maxMove + 1];

        for (int move = 1; move <= maxMove; move++) {
            for (int row = 0; row < m; row++) {
                for (int col = 0; col < n; col++) {
                    dp[row][col][move] = (
                        ((row == 0 ? 1 : dp[row - 1][col][move - 1]) +
                         (row == m - 1 ? 1 : dp[row + 1][col][move - 1])) % MOD +
                        ((col == 0 ? 1 : dp[row][col - 1][move - 1]) +
                         (col == n - 1 ? 1 : dp[row][col + 1][move - 1])) % MOD
                    ) % MOD;
                }
            }
        }

        return dp[startRow][startColumn][maxMove];          
    }
}
