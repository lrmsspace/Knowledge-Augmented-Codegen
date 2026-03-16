// Source: https://leetcode.com/problems/count-paths-with-the-given-xor-value/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array grid with size m x n. You are also given an integer k.
//
// Your task is to calculate the number of paths you can take from the top-left cell (0, 0) to the bottom-right cell (m - 1, n - 1) satisfying the following constraints:
//
//
// 	You can either move to the right or down. Formally, from the cell (i, j) you may move to the cell (i, j + 1) or to the cell (i + 1, j) if the target cell exists.
// 	The XOR of all the numbers on the path must be equal to k.
//
//
// Return the total number of such paths.
//
// Since the answer can be very large, return the result modulo 109 + 7.
//
// Example:
// Input: grid = [[2, 1, 5], [7, 10, 0], [12, 6, 4]], k = 11
//
// Output: 3
//
// Explanation: 
//
// The 3 paths are:
//
//
// 	(0, 0) → (1, 0) → (2, 0) → (2, 1) → (2, 2)
// 	(0, 0) → (1, 0) → (1, 1) → (1, 2) → (2, 2)
// 	(0, 0) → (0, 1) → (1, 1) → (2, 1) → (2, 2)
//
// Constraints:
// 1 <= m == grid.length <= 300
// 	1 <= n == grid[r].length <= 300
// 	0 <= grid[r][c] < 16
// 	0 <= k < 16
//

int countPathsWithXorValue(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize, n = gridColSize[0];
    int MOD = 1e9 + 7;

    // dp[i][j][x] := number of paths to (i, j) with XOR value x
    int*** dp = (int***)malloc(m * sizeof(int**));
    for (int i = 0; i < m; i++) {
        dp[i] = (int**)malloc(n * sizeof(int*));
        for (int j = 0; j < n; j++) {
            dp[i][j] = (int*)calloc(16, sizeof(int));
        }
    }

    dp[0][0][grid[0][0]] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int x = 0; x < 16; x++) {
                if (i > 0) {
                    int newXor = x ^ grid[i][j];
                    dp[i][j][newXor] = (dp[i][j][newXor] + dp[i - 1][j][x]) % MOD;
                }
                if (j > 0) {
                    int newXor = x ^ grid[i][j];
                    dp[i][j][newXor] = (dp[i][j][newXor] + dp[i][j - 1][x]) % MOD;
                }
            }
        }
    }

    int result = dp[m - 1][n - 1][k];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);

    return result;      
}
