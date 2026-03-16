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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        const int MOD = 1e9 + 7;
        vector<vector<vector<int>>> dp(maxMove + 1, vector<vector<int>>(m, vector<int>(n, 0)));

        for (int move = 1; move <= maxMove; ++move) {
            for (int row = 0; row < m; ++row) {
                for (int col = 0; col < n; ++col) {
                    dp[move][row][col] = ((row == 0 ? 1 : dp[move - 1][row - 1][col]) +
                                           (row == m - 1 ? 1 : dp[move - 1][row + 1][col]) +
                                           (col == 0 ? 1 : dp[move - 1][row][col - 1]) +
                                           (col == n - 1 ? 1 : dp[move - 1][row][col + 1])) % MOD;
                }
            }
        }

        return dp[maxMove][startRow][startColumn];          
    }
};
