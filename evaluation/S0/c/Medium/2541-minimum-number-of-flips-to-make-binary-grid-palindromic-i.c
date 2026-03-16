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

int minFlips(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int rowFlips = 0;
    int colFlips = 0;

    // Calculate flips needed for palindromic rows
    for (int i = 0; i < m / 2; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != grid[m - 1 - i][j]) {
                rowFlips++;
            }
        }
    }

    // Calculate flips needed for palindromic columns
    for (int j = 0; j < n / 2; j++) {
        for (int i = 0; i < m; i++) {
            if (grid[i][j] != grid[i][n - 1 - j]) {
                colFlips++;
            }
        }
    }

    return rowFlips < colFlips ? rowFlips : colFlips;       
}
