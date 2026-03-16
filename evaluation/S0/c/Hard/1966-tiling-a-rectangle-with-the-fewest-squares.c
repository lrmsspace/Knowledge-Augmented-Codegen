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

int tilingRectangle(int n, int m) {
    int maxSide = n > m ? n : m;
    int dp[14][14];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == j) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = maxSide * maxSide; /* large initial value */
                for (int h = 1; h <= i / 2; h++) {
                    int cand = dp[h][j] + dp[i - h][j];
                    if (cand < dp[i][j]) dp[i][j] = cand;
                }
                for (int w = 1; w <= j / 2; w++) {
                    int cand = dp[i][w] + dp[i][j - w];
                    if (cand < dp[i][j]) dp[i][j] = cand;
                }
                for (int k = 1; k < (i < j ? i : j); k++) {
                    int cand = dp[i - k][j - k] + 1;
                    for (int x = 0; x < k; x++) {
                        cand += dp[k][j - k];
                    }
                    for (int y = 0; y < k; y++) {
                        cand += dp[i - k][k];
                    }
                    if (cand < dp[i][j]) dp[i][j] = cand;
                }
            }
        }
    }
    return dp[n][m];        
}
