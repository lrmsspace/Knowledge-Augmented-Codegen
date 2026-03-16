// Source: https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed m x n matrix grid consisting of positive integers.
//
// You can start at any cell in the first column of the matrix, and traverse the grid in the following way:
//
//
// 	From a cell (row, col), you can move to any of the cells: (row - 1, col + 1), (row, col + 1) and (row + 1, col + 1) such that the value of the cell you move to, should be strictly bigger than the value of the current cell.
//
//
// Return the maximum number of moves that you can perform.
//
// Example:
// Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
// Output: 3
// Explanation: We can start at the cell (0, 0) and make the following moves:
// - (0, 0) -> (0, 1).
// - (0, 1) -> (1, 2).
// - (1, 2) -> (2, 3).
// It can be shown that it is the maximum number of moves that can be made.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 1000
// 	4 <= m * n <= 105
// 	1 <= grid[i][j] <= 106
//

int maxMoves(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    int dp[m][n];
    memset(dp, 0, sizeof(dp));
    int max_moves = 0;

    for (int col = 1; col < n; col++) {
        for (int row = 0; row < m; row++) {
            int best_prev = 0;

            // Check the three possible previous positions
            for (int drow = -1; drow <= 1; drow++) {
                int prev_row = row + drow;
                if (prev_row >= 0 && prev_row < m && grid[prev_row][col - 1] < grid[row][col]) {
                    best_prev = fmax(best_prev, dp[prev_row][col - 1] + 1);
                }
            }

            dp[row][col] = best_prev;
            max_moves = fmax(max_moves, dp[row][col]);
        }
    }

    return max_moves;       
}
