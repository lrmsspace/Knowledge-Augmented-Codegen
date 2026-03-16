// Source: https://leetcode.com/problems/count-cells-in-overlapping-horizontal-and-vertical-substrings/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix grid consisting of characters and a string pattern.
//
// A horizontal substring is a contiguous sequence of characters read from left to right. If the end of a row is reached before the substring is complete, it wraps to the first column of the next row and continues as needed. You do not wrap from the bottom row back to the top.
//
// A vertical substring is a contiguous sequence of characters read from top to bottom. If the bottom of a column is reached before the substring is complete, it wraps to the first row of the next column and continues as needed. You do not wrap from the last column back to the first.
//
// Count the number of cells in the matrix that satisfy the following condition:
//
//
// 	The cell must be part of at least one horizontal substring and at least one vertical substring, where both substrings are equal to the given pattern.
//
//
// Return the count of these cells.
//
// Example:
// Input: grid = [["a","a","c","c"],["b","b","b","c"],["a","a","b","a"],["c","a","a","c"],["a","a","b","a"]], pattern = "abaca"
//
// Output: 1
//
// Explanation:
//
// The pattern "abaca" appears once as a horizontal substring (colored blue) and once as a vertical substring (colored red), intersecting at one cell (colored purple).
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	1 <= pattern.length <= m * n
// 	grid and pattern consist of only lowercase English letters.
//

class Solution {
    public int countCells(char[][] grid, String pattern) {
        int m = grid.length;
        int n = grid[0].length;
        int pLen = pattern.length();

        boolean[][] horizontal = new boolean[m][n];
        boolean[][] vertical = new boolean[m][n];

        // Check horizontal substrings
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matchesHorizontal(grid, pattern, i, j, m, n, pLen)) {
                    for (int k = 0; k < pLen; k++) {
                        int col = (j + k) % n;
                        int row = i + (j + k) / n;
                        if (row < m) {
                            horizontal[row][col] = true;
                        }
                    }
                }
            }
        }

        // Check vertical substrings
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                if (matchesVertical(grid, pattern, i, j, m, n, pLen)) {
                    for (int k = 0; k < pLen; k++) {
                        int row = (i + k) % m;
                        int col = j + (i + k) / m;
                        if (col < n) {
                            vertical[row][col] = true;
                        }
                    }
                }
            }
        }

        // Count overlapping cells
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (horizontal[i][j] && vertical[i][j]) {
                    count++;
                }
            }
        }

        return count;           
    }
}
