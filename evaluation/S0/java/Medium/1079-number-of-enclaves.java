// Source: https://leetcode.com/problems/number-of-enclaves/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.
//
// A move consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.
//
// Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.
//
// Example:
// Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
// Output: 3
// Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 500
// 	grid[i][j] is either 0 or 1.
//

class Solution {
    public int numEnclaves(int[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;

        // Eliminate land cells connected to the boundary
        for (int r = 0; r < rows; r++) {
            if (grid[r][0] == 1) {
                dfs(grid, r, 0);
            }
            if (grid[r][cols - 1] == 1) {
                dfs(grid, r, cols - 1);
            }
        }

        for (int c = 0; c < cols; c++) {
            if (grid[0][c] == 1) {
                dfs(grid, 0, c);
            }
            if (grid[rows - 1][c] == 1) {
                dfs(grid, rows - 1, c);
            }
        }

        // Count remaining land cells
        int enclaveCount = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1) {
                    enclaveCount++;
                }
            }
        }

        return enclaveCount;            
    }
}
