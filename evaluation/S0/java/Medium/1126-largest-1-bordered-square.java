// Source: https://leetcode.com/problems/largest-1-bordered-square/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D grid of 0s and 1s, return the number of elements in the largest square subgrid that has all 1s on its border, or 0 if such a subgrid doesn't exist in the grid.
//
// Example:
// Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
// Output: 9
//
// Constraints:
// 1 <= grid.length <= 100
// 	1 <= grid[0].length <= 100
// 	grid[i][j] is 0 or 1
//

class Solution {
    public int largest1BorderedSquare(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        int[][] right = new int[m][n];
        int[][] down = new int[m][n];

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (grid[i][j] == 1) {
                    right[i][j] = 1 + (j + 1 < n ? right[i][j + 1] : 0);
                    down[i][j] = 1 + (i + 1 < m ? down[i + 1][j] : 0);
                }
            }
        }

        int maxSide = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int possibleSide = Math.min(right[i][j], down[i][j]);
                while (possibleSide > maxSide) {
                    if (right[i + possibleSide - 1][j] >= possibleSide &&
                        down[i][j + possibleSide - 1] >= possibleSide) {
                        maxSide = possibleSide;
                    }
                    possibleSide--;
                }
            }
        }

        return maxSide * maxSide;           
    }
}
