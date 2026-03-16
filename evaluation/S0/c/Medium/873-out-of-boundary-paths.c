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

int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
    const int MOD = 1e9 + 7;
    int dp[m][n];
    memset(dp, 0, sizeof(dp));
    dp[startRow][startColumn] = 1;
    int result = 0;

    for (int move = 1; move <= maxMove; move++) {
        int temp[m][n];
        memset(temp, 0, sizeof(temp));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0) result = (result + dp[i][j]) % MOD;
                if (i == m - 1) result = (result + dp[i][j]) % MOD;
                if (j == 0) result = (result + dp[i][j]) % MOD;
                if (j == n - 1) result = (result + dp[i][j]) % MOD;

                if (i > 0) temp[i][j] = (temp[i][j] + dp[i - 1][j]) % MOD;
                if (i < m - 1) temp[i][j] = (temp[i][j] + dp[i + 1][j]) % MOD;
                if (j > 0) temp[i][j] = (temp[i][j] + dp[i][j - 1]) % MOD;
                if (j < n - 1) temp[i][j] = (temp[i][j] + dp[i][j + 1]) % MOD;
            }
        }
        memcpy(dp, temp, sizeof(temp));
    }

    return result;      
}
