// Source: https://leetcode.com/problems/cherry-pickup-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a rows x cols matrix grid representing a field of cherries where grid[i][j] represents the number of cherries that you can collect from the (i, j) cell.
//
// You have two robots that can collect cherries for you:
//
//
// 	Robot #1 is located at the top-left corner (0, 0), and
// 	Robot #2 is located at the top-right corner (0, cols - 1).
//
//
// Return the maximum number of cherries collection using both robots by following the rules below:
//
//
// 	From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
// 	When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.
// 	When both robots stay in the same cell, only one takes the cherries.
// 	Both robots cannot move outside of the grid at any moment.
// 	Both robots should reach the bottom row in grid.
//
// Example:
// Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
// Output: 24
// Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
// Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
// Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
// Total of cherries: 12 + 12 = 24.
//
// Constraints:
// rows == grid.length
// 	cols == grid[i].length
// 	2 <= rows, cols <= 70
// 	0 <= grid[i][j] <= 100
//

int cherryPickup(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    int dp[cols][cols];
    memset(dp, 0, sizeof(dp));

    dp[0][cols - 1] = grid[0][0] + (cols > 1 ? grid[0][cols - 1] : 0);

    for (int r = 1; r < rows; ++r) {
        int newDp[cols][cols];
        memset(newDp, 0, sizeof(newDp));

        for (int c1 = 0; c1 < cols; ++c1) {
            for (int c2 = 0; c2 < cols; ++c2) {
                if (dp[c1][c2] == 0 && !(r == 1 && c1 == 0 && c2 == cols - 1)) continue;

                for (int dc1 = -1; dc1 <= 1; ++dc1) {
                    int nc1 = c1 + dc1;
                    if (nc1 < 0 || nc1 >= cols) continue;

                    for (int dc2 = -1; dc2 <= 1; ++dc2) {
                        int nc2 = c2 + dc2;
                        if (nc2 < 0 || nc2 >= cols) continue;

                        int cherries = grid[r][nc1];
                        if (nc1 != nc2) cherries += grid[r][nc2];

                        if (newDp[nc1][nc2] < dp[c1][c2] + cherries) {
                            newDp[nc1][nc2] = dp[c1][c2] + cherries;
                        }
                    }
                }
            }
        }

        memcpy(dp, newDp, sizeof(dp));
    }

    int result = 0;
    for (int c1 = 0; c1 < cols; ++c1) {
        for (int c2 = 0; c2 < cols; ++c2) {
            if (dp[c1][c2] > result) {
                result = dp[c1][c2];
            }
        }
    }

    return result;      
}
