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

class Solution {
    public int cherryPickup(int[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;
        int[][][] dp = new int[rows][cols][cols];

        for (int r = rows - 1; r >= 0; r--) {
            for (int c1 = 0; c1 < cols; c1++) {
                for (int c2 = 0; c2 < cols; c2++) {
                    int cherries = grid[r][c1];
                    if (c1 != c2) {
                        cherries += grid[r][c2];
                    }

                    if (r != rows - 1) {
                        int maxCherries = 0;
                        for (int dc1 = -1; dc1 <= 1; dc1++) {
                            for (int dc2 = -1; dc2 <= 1; dc2++) {
                                int newC1 = c1 + dc1;
                                int newC2 = c2 + dc2;
                                if (newC1 >= 0 && newC1 < cols && newC2 >= 0 && newC2 < cols) {
                                    maxCherries = Math.max(maxCherries, dp[r + 1][newC1][newC2]);
                                }
                            }
                        }
                        cherries += maxCherries;
                    }

                    dp[r][c1][c2] = cherries;
                }
            }
        }

        return dp[0][0][cols - 1];                  
    }
}
