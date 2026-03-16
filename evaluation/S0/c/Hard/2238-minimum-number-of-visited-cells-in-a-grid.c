// Source: https://leetcode.com/problems/minimum-number-of-visited-cells-in-a-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed m x n integer matrix grid. Your initial position is at the top-left cell (0, 0).
//
// Starting from the cell (i, j), you can move to one of the following cells:
//
//
// 	Cells (i, k) with j < k <= grid[i][j] + j (rightward movement), or
// 	Cells (k, j) with i < k <= grid[i][j] + i (downward movement).
//
//
// Return the minimum number of cells you need to visit to reach the bottom-right cell (m - 1, n - 1). If there is no valid path, return -1.
//
// Example:
// Input: grid = [[3,4,2,1],[4,2,3,1],[2,1,0,0],[2,4,0,0]]
// Output: 4
// Explanation: The image above shows one of the paths that visits exactly 4 cells.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	0 <= grid[i][j] < m * n
// 	grid[m - 1][n - 1] == 0
//

int minimumVisitedCells(int** grid, int gridSize, int* gridColSize){
    int m = gridSize;
    int n = gridColSize[0];
    int *dp = (int *)malloc(sizeof(int) * n);
    for (int j = 0; j < n; j++) {
        dp[j] = -1;
    }
    dp[0] = 1;

    for (int i = 0; i < m; i++) {
        int *new_dp = (int *)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            new_dp[j] = -1;
        }
        int max_reach = -1;
        for (int j = 0; j < n; j++) {
            if (dp[j] != -1) {
                if (max_reach < j) {
                    max_reach = j;
                }
                int reach = j + grid[i][j];
                while (max_reach + 1 <= reach && max_reach + 1 < n) {
                    new_dp[max_reach + 1] = dp[j] + 1;
                    max_reach++;
                }
            }
        }
        free(dp);
        dp = new_dp;
    }

    int result = dp[n - 1];
    free(dp);
    return result;
}
