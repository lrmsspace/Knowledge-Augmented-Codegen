// Source: https://leetcode.com/problems/cherry-pickup/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n grid representing a field of cherries, each cell is one of three possible integers.
//
//
// 	0 means the cell is empty, so you can pass through,
// 	1 means the cell contains a cherry that you can pick up and pass through, or
// 	-1 means the cell contains a thorn that blocks your way.
//
//
// Return the maximum number of cherries you can collect by following the rules below:
//
//
// 	Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through valid path cells (cells with value 0 or 1).
// 	After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path cells.
// 	When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.
// 	If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.
//
// Example:
// Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
// Output: 5
// Explanation: The player started at (0, 0) and went down, down, right right to reach (2, 2).
// 4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
// Then, the player went left, up, up, left to return home, picking up one more cherry.
// The total number of cherries picked up is 5, and this is the maximum possible.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 50
// 	grid[i][j] is -1, 0, or 1.
// 	grid[0][0] != -1
// 	grid[n - 1][n - 1] != -1
//

int cherryPickup(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    int dp[2*n-1][n][n];
    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = grid[0][0];

    for (int t = 1; t <= 2*(n-1); ++t) {
        for (int x1 = 0; x1 < n; ++x1) {
            int y1 = t - x1;
            if (y1 < 0 || y1 >= n) continue;
            for (int x2 = 0; x2 < n; ++x2) {
                int y2 = t - x2;
                if (y2 < 0 || y2 >= n) continue;
                if (grid[x1][y1] == -1 || grid[x2][y2] == -1) continue;

                int val = grid[x1][y1];
                if (x1 != x2) val += grid[x2][y2];

                int maxPrev = -1;
                for (int dx1 = -1; dx1 <= 0; ++dx1) {
                    for (int dx2 = -1; dx2 <= 0; ++dx2) {
                        int px1 = x1 + dx1;
                        int py1 = y1 - (dx1 == 0 ? 1 : 0);
                        int px2 = x2 + dx2;
                        int py2 = y2 - (dx2 == 0 ? 1 : 0);
                        if (px1 >= 0 && py1 >= 0 && px2 >= 0 && py2 >= 0 && dp[t-1][px1][px2] != -1) {
                            if (dp[t-1][px1][px2] > maxPrev) {
                                maxPrev = dp[t-1][px1][px2];
                            }
                        }
                    }
                }
                if (maxPrev != -1) {
                    dp[t][x1][x2] = maxPrev + val;
                }
            }
        }
    }

    return dp[2*(n-1)][n-1][n-1] < 0 ? 0 : dp[2*(n-1)][n-1][n-1];       
}
