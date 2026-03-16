// Source: https://leetcode.com/problems/disconnect-path-in-a-binary-matrix-by-at-most-one-flip/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed m x n binary matrix grid. You can move from a cell (row, col) to any of the cells (row + 1, col) or (row, col + 1) that has the value 1. The matrix is disconnected if there is no path from (0, 0) to (m - 1, n - 1).
//
// You can flip the value of at most one (possibly none) cell. You cannot flip the cells (0, 0) and (m - 1, n - 1).
//
// Return true if it is possible to make the matrix disconnect or false otherwise.
//
// Note that flipping a cell changes its value from 0 to 1 or from 1 to 0.
//
// Example:
// Input: grid = [[1,1,1],[1,0,0],[1,1,1]]
// Output: true
// Explanation: We can change the cell shown in the diagram above. There is no path from (0, 0) to (2, 2) in the resulting grid.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	grid[i][j] is either 0 or 1.
// 	grid[0][0] == grid[m - 1][n - 1] == 1
//

class Solution {
    public boolean isPossibleToCutPath(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        if (m == 1 && n == 1) return false;

        int[][] dp1 = new int[m][n];
        int[][] dp2 = new int[m][n];

        dp1[0][0] = grid[0][0];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;
                if (grid[i][j] == 0) {
                    dp1[i][j] = 0;
                } else {
                    dp1[i][j] = (i > 0 ? dp1[i - 1][j] : 0) + (j > 0 ? dp1[i][j - 1] : 0);
                }
            }
        }

        dp2[m - 1][n - 1] = grid[m - 1][n - 1];
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i == m - 1 && j == n - 1) continue;
                if (grid[i][j] == 0) {
                    dp2[i][j] = 0;
                } else {
                    dp2[i][j] = (i < m - 1 ? dp2[i + 1][j] : 0) + (j < n - 1 ? dp2[i][j + 1] : 0);
                }
            }
        }

        int totalPaths = dp1[m - 1][n - 1];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if ((i == 0 && j == 0) || (i == m - 1 && j == n - 1)) continue;
                if (grid[i][j] == 1 && dp1[i][j] * dp2[i][j] == totalPaths) {
                    return true;
                }
            }
        }

        return false;           
    }
}
