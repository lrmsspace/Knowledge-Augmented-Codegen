// Source: https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed m x n integer matrix grid and an integer k. You are currently at position (0, 0) and you want to reach position (m - 1, n - 1) moving only down or right.
//
// Return the number of paths where the sum of the elements on the path is divisible by k. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
// Output: 2
// Explanation: There are two paths where the sum of the elements on the path is divisible by k.
// The first path highlighted in red has a sum of 5 + 2 + 4 + 5 + 2 = 18 which is divisible by 3.
// The second path highlighted in blue has a sum of 5 + 3 + 0 + 5 + 2 = 15 which is divisible by 3.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 5 * 104
// 	1 <= m * n <= 5 * 104
// 	0 <= grid[i][j] <= 100
// 	1 <= k <= 50
//

int numberOfPaths(int** grid, int gridSize, int* gridColSize, int k) {
    const int MOD = 1000000007;
    int m = gridSize, n = gridColSize[0];
    int dp[n][k];
    memset(dp, 0, sizeof(dp));
    dp[0][grid[0][0] % k] = 1;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) continue;
            int currVal = grid[i][j];
            int newDp[k];
            memset(newDp, 0, sizeof(newDp));
            for (int r = 0; r < k; ++r) {
                int newR = (r + currVal) % k;
                if (i > 0) {
                    newDp[newR] = (newDp[newR] + dp[j][r]) % MOD;
                }
                if (j > 0) {
                    newDp[newR] = (newDp[newR] + newDp[r]) % MOD;
                }
            }
            memcpy(dp[j], newDp, sizeof(newDp));
        }
    }

    return dp[n - 1][0];        
}
