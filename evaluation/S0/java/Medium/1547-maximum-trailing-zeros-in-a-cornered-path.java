// Source: https://leetcode.com/problems/maximum-trailing-zeros-in-a-cornered-path/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array grid of size m x n, where each cell contains a positive integer.
//
// A cornered path is defined as a set of adjacent cells with at most one turn. More specifically, the path should exclusively move either horizontally or vertically up to the turn (if there is one), without returning to a previously visited cell. After the turn, the path will then move exclusively in the alternate direction: move vertically if it moved horizontally, and vice versa, also without returning to a previously visited cell.
//
// The product of a path is defined as the product of all the values in the path.
//
// Return the maximum number of trailing zeros in the product of a cornered path found in grid.
//
// Note:
//
//
// 	Horizontal movement means moving in either the left or right direction.
// 	Vertical movement means moving in either the up or down direction.
//
// Example:
// Input: grid = [[23,17,15,3,20],[8,1,20,27,11],[9,4,6,2,21],[40,9,1,10,6],[22,7,4,5,3]]
// Output: 3
// Explanation: The grid on the left shows a valid cornered path.
// It has a product of 15 * 20 * 6 * 1 * 10 = 18000 which has 3 trailing zeros.
// It can be shown that this is the maximum trailing zeros in the product of a cornered path.
//
// The grid in the middle is not a cornered path as it has more than one turn.
// The grid on the right is not a cornered path as it requires a return to a previously visited cell.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= grid[i][j] <= 1000
//

class Solution {
    public int maxTrailingZeros(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] count2 = new int[m][n];
        int[][] count5 = new int[m][n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int num = grid[i][j];
                while (num % 2 == 0) {
                    count2[i][j]++;
                    num /= 2;
                }
                while (num % 5 == 0) {
                    count5[i][j]++;
                    num /= 5;
                }
            }
        }

        int[][] prefixRow2 = new int[m][n + 1];
        int[][] prefixRow5 = new int[m][n + 1];
        int[][] prefixCol2 = new int[m + 1][n];
        int[][] prefixCol5 = new int[m + 1][n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefixRow2[i][j + 1] = prefixRow2[i][j] + count2[i][j];
                prefixRow5[i][j + 1] = prefixRow5[i][j] + count5[i][j];
                prefixCol2[i + 1][j] = prefixCol2[i][j] + count2[i][j];
                prefixCol5[i + 1][j] = prefixCol5[i][j] + count5[i][j];
            }
        }

        int maxZeros = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int up2 = prefixCol2[i][j];
                int up5 = prefixCol5[i][j];
                int down2 = prefixCol2[m][j] - prefixCol2[i + 1][j];
                int down5 = prefixCol5[m][j] - prefixCol5[i + 1][j];
                int left2 = prefixRow2[i][j];
                int left5 = prefixRow5[i][j];
                int right2 = prefixRow2[i][n] - prefixRow2[i][j + 1];
                int right5 = prefixRow5[i][n] - prefixRow5[i][j + 1];

                int center2 = count2[i][j];
                int center5 = count5[i][j];

                maxZeros = Math.max(maxZeros, Math.min(up2 + left2 + center2, up5 + left5 + center5));
                maxZeros = Math.max(maxZeros, Math.min(up2 + right2 + center2, up5 + right5 + center5));
                maxZeros = Math.max(maxZeros, Math.min(down2 + left2 + center2, down5 + left5 + center5));
                maxZeros = Math.max(maxZeros, Math.min(down2 + right2 + center2, down5 + right5 + center5));
            }
        }
        return maxZeros;
    }
}
