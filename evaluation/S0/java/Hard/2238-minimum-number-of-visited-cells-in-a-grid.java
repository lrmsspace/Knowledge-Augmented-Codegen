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

class Solution {
    public int minimumVisitedCells(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] dp = new int[m][n];
        for (int i = 0; i < m; i++) {
            Arrays.fill(dp[i], Integer.MAX_VALUE);
        }
        dp[0][0] = 1;

        TreeSet<Integer>[] rowSets = new TreeSet[m];
        TreeSet<Integer>[] colSets = new TreeSet[n];
        for (int i = 0; i < m; i++) {
            rowSets[i] = new TreeSet<>();
            for (int j = 0; j < n; j++) {
                rowSets[i].add(j);
            }
        }
        for (int j = 0; j < n; j++) {
            colSets[j] = new TreeSet<>();
            for (int i = 0; i < m; i++) {
                colSets[j].add(i);
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][j] == Integer.MAX_VALUE) continue;

                // Rightward movement
                int maxRight = Math.min(n - 1, j + grid[i][j]);
                Integer col = rowSets[i].ceiling(j + 1);
                while (col != null && col <= maxRight) {
                    dp[i][col] = Math.min(dp[i][col], dp[i][j] + 1);
                    rowSets[i].remove(col);
                    colSets[col].remove(i);
                    col = rowSets[i].ceiling(j + 1);
                }

                // Downward movement
                int maxDown = Math.min(m - 1, i + grid[i][j]);
                Integer row = colSets[j].ceiling(i + 1);
                while (row != null && row <= maxDown) {
                    dp[row][j] = Math.min(dp[row][j], dp[i][j] + 1);
                    rowSets[row].remove(j);
                    colSets[j].remove(row);
                    row = colSets[j].ceiling(i + 1);
                }
            }
        }

        return dp[m - 1][n - 1] == Integer.MAX_VALUE ? -1 : dp[m - 1][n - 1];           
    }
}
