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
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        const int MOD = 1e9 + 7;
        vector<vector<vector<int>>> dp(maxMove + 1, vector<vector<int>>(m, vector<int>(n, 0)));

        for (int move = 1; move <= maxMove; ++move) {
            for (int row = 0; row < m; ++row) {
                for (int col = 0; col < n; ++col) {
                    // Up
                    if (row == 0) {
                        dp[move][row][col] = (dp[move][row][col] + 1) % MOD;
                    } else {
                        dp[move][row][col] = (dp[move][row][col] + dp[move - 1][row - 1][col]) % MOD;
                    }

                    // Down
                    if (row == m - 1) {
                        dp[move][row][col] = (dp[move][row][col] + 1) % MOD;
                    } else {
                        dp[move][row][col] = (dp[move][row][col] + dp[move - 1][row + 1][col]) % MOD;
                    }

                    // Left
                    if (col == 0) {
                        dp[move][row][col] = (dp[move][row][col] + 1) % MOD;
                    } else {
                        dp[move][row][col] = (dp[move][row][col] + dp[move - 1][row][col - 1]) % MOD;
                    }

                    // Right
                    if (col == n - 1) {
                        dp[move][row][col] = (dp[move][row][col] + 1) % MOD;
                    } else {
                        dp[move][row][col] = (dp[move][row][col] + dp[move - 1][row][col + 1]) % MOD;
                    }
                }
            }
        }

        return dp[maxMove][startRow][startColumn];          
    }
};
