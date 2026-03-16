// Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid.
//
// A row or column is considered palindromic if its values read the same forward and backward.
//
// You can flip any number of cells in grid from 0 to 1, or from 1 to 0.
//
// Return the minimum number of cells that need to be flipped to make all rows and columns palindromic, and the total number of 1's in grid divisible by 4.
//
// Example:
// Input: grid = [[1,0,0],[0,1,0],[0,0,1]]
//
// Output: 3
//
// Explanation:
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
        int totalFlips = 0;

        for (int i = 0; i <= (m - 1) / 2; i++) {
            for (int j = 0; j <= (n - 1) / 2; j++) {
                int onesCount = 0;
                int zerosCount = 0;

                // Collect the four symmetric positions
                int[][] positions = {
                    {i, j},
                    {i, n - 1 - j},
                    {m - 1 - i, j},
                    {m - 1 - i, n - 1 - j}
                };

                // Count the number of ones and zeros in these positions
                for (int[] pos : positions) {
                    int x = pos[0];
                    int y = pos[1];
                    if (x >= 0 && x < m && y >= 0 && y < n) {
                        if (grid[x][y] == 1) {
                            onesCount++;
                        } else {
                            zerosCount++;
                        }
                    }
                }

                // Calculate minimum flips needed for this group
                totalFlips += Math.min(onesCount, zerosCount);
            }
        }

        return totalFlips;          
    }
}
