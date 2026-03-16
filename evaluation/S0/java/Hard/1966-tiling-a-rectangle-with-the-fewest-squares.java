// Source: https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/   |   Difficulty: Hard
//
// Problem Description:
// Given a rectangle of size n x m, return the minimum number of integer-sided squares that tile the rectangle.
//
// Example:
// Input: n = 2, m = 3
// Output: 3
// Explanation: 3 squares are necessary to cover the rectangle.
// 2 (squares of 1x1)
// 1 (square of 2x2)
//
// Constraints:
// 1 <= n, m <= 13
//

class Solution {
    public int tilingRectangle(int n, int m) {
        int[][] dp = new int[n + 1][m + 1];

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (i == j) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = Integer.MAX_VALUE;

                    for (int k = 1; k <= i / 2; k++) {
                        dp[i][j] = Math.min(dp[i][j], dp[k][j] + dp[i - k][j]);
                    }

                    for (int k = 1; k <= j / 2; k++) {
                        dp[i][j] = Math.min(dp[i][j], dp[i][k] + dp[i][j - k]);
                    }

                    for (int k = 1; k <= Math.min(i, j); k++) {
                        dp[i][j] = Math.min(dp[i][j], 1 + dp[i - k][j - k] + dp[k][j - k] + dp[i - k][k]);
                    }
                }
            }
        }

        return dp[n][m];                    
    }
}
