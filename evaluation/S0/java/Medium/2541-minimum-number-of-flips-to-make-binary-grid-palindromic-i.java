// Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid.
//
// A row or column is considered palindromic if its values read the same forward and backward.
//
// You can flip any number of cells in grid from 0 to 1, or from 1 to 0.
//
// Return the minimum number of cells that need to be flipped to make either all rows palindromic or all columns palindromic.
//
// Example:
// Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
//
// Output: 2
//
// Explanation:
//
//
//
// Flipping the highlighted cells makes all the rows palindromic.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m * n <= 2 * 105
// 	0 <= grid[i][j] <= 1
//

class Solution {
    public int minFlips(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int result = 0;

        for (int layer = 0; layer < (m + n - 1) / 2; layer++) {
            int zeros = 0;
            int ones = 0;

            for (int i = 0; i < m; i++) {
                int j = layer - i;
                if (j < 0 || j >= n) {
                    continue;
                }

                int oppI = m - 1 - i;
                int oppJ = n - 1 - j;

                if (i == oppI && j == oppJ) {
                    if (grid[i][j] == 0) {
                        zeros++;
                    } else {
                        ones++;
                    }
                } else if (i == oppI || j == oppJ) {
                    if (grid[i][j] == 0) {
                        zeros++;
                    } else {
                        ones++;
                    }
                } else {
                    if (grid[i][j] == 0) {
                        zeros++;
                    } else {
                        ones++;
                    }

                    if (grid[oppI][oppJ] == 0) {
                        zeros++;
                    } else {
                        ones++;
                    }
                }
            }

            result += Math.min(zeros, ones);
        }

        return result;          
    }
}
